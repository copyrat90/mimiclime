#include "gm/ecs/sys/velocity_movement.h"

#include "gm/cfg/sprite_datas.h"

#include <bn_sprite_shape_size.h>

#include "ldtk_gen_project.h"

namespace mc::gm::ecs::sys
{

void velocity_movement(actor_registry& actor_reg, singleton_registry& singleton_reg, const gba::entity singleton_entity)
{
    actor_reg.view<cpn::velocity, bn::sprite_ptr>().each(
        [&](const gba::entity entity, cpn::velocity& velocity, bn::sprite_ptr& sprite) {
            const auto* room = singleton_reg.try_get<cpn::room>(singleton_entity);
            BN_ASSERT(room);
            auto* coll_events = actor_reg.try_get<cpn::collision_events>(entity);

            const bn::fixed_point sprite_size_diff(sprite.shape_size().width() / 2, sprite.shape_size().height() / 2);
            bn::fixed_point moved_pos = sprite.top_left_position() + sprite_size_diff;

            if (velocity.velocity != bn::fixed_point(0, 0))
            {
                auto* spr_anim = actor_reg.try_get<cpn::sprite_animation>(entity);
                if (spr_anim == nullptr)
                    goto NO_WALL_COLLISIONS;

                const auto& spr_datas = cfg::sprite_datas::get(spr_anim->sprite_kind);
                const auto& spr_frame_datas = spr_datas.frame(spr_anim->current_graphics_index());

                if (spr_frame_datas.wallboxes.empty())
                    goto NO_WALL_COLLISIONS;

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
                        if (room->collide_with_wall({box.right(), box.center_y()}) ||
                            room->collide_with_wall(box.top_right()) || room->collide_with_wall(box.bottom_right()))
                        {
                            revert_x = true;
                            break;
                        }
                    }
                    // If moving left,
                    else if (velocity.velocity.x() < 0)
                    {
                        if (room->collide_with_wall({box.left(), box.center_y()}) ||
                            room->collide_with_wall(box.top_left()) || room->collide_with_wall(box.bottom_left()))
                        {
                            revert_x = true;
                            break;
                        }
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
                        if (room->collide_with_wall({box.center_x(), box.bottom()}) ||
                            room->collide_with_wall(box.bottom_left()) || room->collide_with_wall(box.bottom_right()))
                        {
                            revert_y = true;
                            break;
                        }
                    }
                    // If moving up,
                    else if (velocity.velocity.y() < 0)
                    {
                        if (room->collide_with_wall({box.center_x(), box.top()}) ||
                            room->collide_with_wall(box.top_left()) || room->collide_with_wall(box.top_right()))
                        {
                            revert_y = true;
                            break;
                        }
                    }
                }

                if (revert_y)
                    moved_pos.set_y(prev_y);

                if (coll_events)
                    coll_events->collided_wall = revert_x || revert_y;
            }
            else
            {
            NO_WALL_COLLISIONS:
                moved_pos += velocity.velocity;
            }

            sprite.set_top_left_position(moved_pos - sprite_size_diff);
        });
}

} // namespace mc::gm::ecs::sys
