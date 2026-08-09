#include "gm/ecs/sys/terrain_collide.h"

#include "gm/cfg/sprite_datas.h"

#include <bn_sprite_shape_size.h>

namespace mc::gm::ecs::sys
{

namespace
{

bool blocking_entity_collide(const bn::top_left_fixed_rect& box, actor_registry& actor_reg)
{
    bool collided = false;

    // Breakable
    actor_reg.view<cpn::breakable_states>().each([&](const gba::entity breakable,
                                                     cpn::breakable_states& breakable_states) {
        // Ignore already vanishing breakable
        if (breakable_states.state == cpn::breakable_states::state_t::VANISH)
            return;

        auto* breakable_spr = actor_reg.try_get<bn::sprite_ptr>(breakable);
        BN_ASSERT(breakable_spr);
        const auto breakable_pos =
            breakable_spr->top_left_position() +
            bn::fixed_point(breakable_spr->shape_size().width() / 2, breakable_spr->shape_size().height() / 2);
        auto* breakable_anim = actor_reg.try_get<cpn::sprite_animation>(breakable);
        BN_ASSERT(breakable_anim);
        const auto breakable_gfx_idx = breakable_anim->current_graphics_index();
        const auto breakable_spr_kind = ut::enum_to_enum<cfg::gen::sprite_kind>(breakable_states.kind);
        const auto& breakable_spr_frame_datas = cfg::sprite_datas::get(breakable_spr_kind).frame(breakable_gfx_idx);
        auto* breakable_coll_evs = actor_reg.try_get<cpn::collision_events>(breakable);
        BN_ASSERT(breakable_coll_evs);

        // Breakable wallbox
        for (const auto& rel_breakable_wallbox : breakable_spr_frame_datas.wallboxes)
        {
            const bn::top_left_fixed_rect breakable_wallbox(breakable_pos.x() + rel_breakable_wallbox.x,
                                                            breakable_pos.y() + rel_breakable_wallbox.y,
                                                            rel_breakable_wallbox.width, rel_breakable_wallbox.height);

            if (box.intersects(breakable_wallbox))
            {
                collided = true;
                break;
            }
        }
    });

    return collided;
}

void terrain_bounce_off(const cpn::room& room, const cfg::sprite_frame_datas& spr_frame_datas, cpn::velocity& velocity,
                        bn::sprite_ptr& sprite, cpn::collision_events& coll_events, actor_registry& actor_reg)
{
    const bn::fixed_point sprite_size_diff(sprite.shape_size().width() / 2, sprite.shape_size().height() / 2);
    bn::fixed_point moved_pos = sprite.top_left_position() + sprite_size_diff;

    // Force revert the position first for "move and slide" behavior.
    moved_pos -= velocity.velocity;

    // Move to X-axis w/ reverting when collide with walls.
    bool revert_x = false;
    const bn::fixed prev_x = moved_pos.x();

    moved_pos.set_x(moved_pos.x() + velocity.velocity.x());
    for (const auto& relative_box : spr_frame_datas.wallboxes)
    {
        const bn::top_left_fixed_rect box(moved_pos.x() + relative_box.x, moved_pos.y() + relative_box.y,
                                          relative_box.width, relative_box.height);

        // If moving right,
        if (velocity.velocity.x() > 0)
        {
            if (room.collide_with_wall({box.right(), box.center_y()}) || room.collide_with_wall(box.top_right()) ||
                room.collide_with_wall(box.bottom_right()))
            {
                revert_x = true;
                break;
            }
        }
        // If moving left,
        else if (velocity.velocity.x() < 0)
        {
            if (room.collide_with_wall({box.left(), box.center_y()}) || room.collide_with_wall(box.top_left()) ||
                room.collide_with_wall(box.bottom_left()))
            {
                revert_x = true;
                break;
            }
        }

        if (blocking_entity_collide(box, actor_reg))
        {
            revert_x = true;
            break;
        }
    }

    if (revert_x)
        moved_pos.set_x(prev_x);

    // Move to Y-axis w/ reverting when collide with walls.
    bool revert_y = false;
    const bn::fixed prev_y = moved_pos.y();

    moved_pos.set_y(moved_pos.y() + velocity.velocity.y());
    for (const auto& relative_box : spr_frame_datas.wallboxes)
    {
        const bn::top_left_fixed_rect box(moved_pos.x() + relative_box.x, moved_pos.y() + relative_box.y,
                                          relative_box.width, relative_box.height);

        // If moving down,
        if (velocity.velocity.y() > 0)
        {
            if (room.collide_with_wall({box.center_x(), box.bottom()}) || room.collide_with_wall(box.bottom_left()) ||
                room.collide_with_wall(box.bottom_right()))
            {
                revert_y = true;
                break;
            }
        }
        // If moving up,
        else if (velocity.velocity.y() < 0)
        {
            if (room.collide_with_wall({box.center_x(), box.top()}) || room.collide_with_wall(box.top_left()) ||
                room.collide_with_wall(box.top_right()))
            {
                revert_y = true;
                break;
            }
        }

        if (blocking_entity_collide(box, actor_reg))
        {
            revert_y = true;
            break;
        }
    }

    if (revert_y)
        moved_pos.set_y(prev_y);

    coll_events.collided_wall = revert_x || revert_y;

    sprite.set_top_left_position(moved_pos - sprite_size_diff);
}

void terrain_detect_only(const cpn::room& room, const cfg::sprite_frame_datas& spr_frame_datas, cpn::velocity& velocity,
                         bn::sprite_ptr& sprite, cpn::collision_events& coll_events, actor_registry& actor_reg)
{
    const bn::fixed_point sprite_size_diff(sprite.shape_size().width() / 2, sprite.shape_size().height() / 2);
    bn::fixed_point spr_position = sprite.top_left_position() + sprite_size_diff;

    bool collided = false;
    for (const auto& relative_box : spr_frame_datas.wallboxes)
    {
        const bn::top_left_fixed_rect box(spr_position.x() + relative_box.x, spr_position.y() + relative_box.y,
                                          relative_box.width, relative_box.height);

        // If moving right,
        if (velocity.velocity.x() > 0)
        {
            if (room.collide_with_wall({box.right(), box.center_y()}) || room.collide_with_wall(box.top_right()) ||
                room.collide_with_wall(box.bottom_right()))
            {
                collided = true;
                break;
            }
        }
        // If moving left,
        else if (velocity.velocity.x() < 0)
        {
            if (room.collide_with_wall({box.left(), box.center_y()}) || room.collide_with_wall(box.top_left()) ||
                room.collide_with_wall(box.bottom_left()))
            {
                collided = true;
                break;
            }
        }

        // If moving down,
        if (velocity.velocity.y() > 0)
        {
            if (room.collide_with_wall({box.center_x(), box.bottom()}) || room.collide_with_wall(box.bottom_left()) ||
                room.collide_with_wall(box.bottom_right()))
            {
                collided = true;
                break;
            }
        }
        // If moving up,
        else if (velocity.velocity.y() < 0)
        {
            if (room.collide_with_wall({box.center_x(), box.top()}) || room.collide_with_wall(box.top_left()) ||
                room.collide_with_wall(box.top_right()))
            {
                collided = true;
                break;
            }
        }

        if (blocking_entity_collide(box, actor_reg))
        {
            collided = true;
            break;
        }
    }

    coll_events.collided_wall = collided;
}

} // namespace

void terrain_collide(actor_registry& actor_reg, singleton_registry& singleton_reg, const gba::entity singleton_entity)
{
    actor_reg.view<cpn::velocity, bn::sprite_ptr, cpn::collision_events>().each(
        [&](const gba::entity entity, cpn::velocity& velocity, bn::sprite_ptr& sprite,
            cpn::collision_events& coll_events) {
            const auto* room = singleton_reg.try_get<cpn::room>(singleton_entity);
            BN_ASSERT(room);

            if (velocity.velocity == bn::fixed_point(0, 0))
                return;

            auto* spr_anim = actor_reg.try_get<cpn::sprite_animation>(entity);
            if (spr_anim == nullptr)
                return;

            const auto& spr_datas = cfg::sprite_datas::get(spr_anim->sprite_kind);
            const auto& spr_frame_datas = spr_datas.frame(spr_anim->current_graphics_index());

            if (spr_frame_datas.wallboxes.empty())
                return;

            if (coll_events.terrain_bounce_off)
                terrain_bounce_off(*room, spr_frame_datas, velocity, sprite, coll_events, actor_reg);
            else
                terrain_detect_only(*room, spr_frame_datas, velocity, sprite, coll_events, actor_reg);
        });
}

} // namespace mc::gm::ecs::sys
