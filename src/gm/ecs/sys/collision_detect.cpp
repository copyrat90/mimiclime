#include "gm/ecs/sys/collision_detect.h"

#include "gm/cfg/breakable_infos.h"
#include "gm/cfg/sprite_animation_info.h"
#include "gm/cfg/sprite_datas.h"

#include "ut/enum_utils.h"

#include <bn_top_left_fixed_rect.h>

namespace mc::gm::ecs::sys
{

void collision_detect(actor_registry& actor_reg)
{
    // Critter
    actor_reg.view<cpn::critter_states>().each([&](const gba::entity critter, cpn::critter_states& critter_states) {
        // Ignore already dead critter
        if (!critter_states.alive())
            return;

        auto* critter_spr = actor_reg.try_get<bn::sprite_ptr>(critter);
        BN_ASSERT(critter_spr);
        const auto critter_pos =
            critter_spr->top_left_position() +
            bn::fixed_point(critter_spr->shape_size().width() / 2, critter_spr->shape_size().height() / 2);
        auto* critter_anim = actor_reg.try_get<cpn::sprite_animation>(critter);
        BN_ASSERT(critter_anim);
        const auto critter_gfx_idx = critter_anim->current_graphics_index();
        const auto& critter_spr_frame_datas = critter_states.sprite_datas().frame(critter_gfx_idx);
        auto* critter_coll_evs = actor_reg.try_get<cpn::collision_events>(critter);
        BN_ASSERT(critter_coll_evs);

        // Critter hurtbox
        for (const auto& rel_critter_hurtbox : critter_spr_frame_datas.hurtboxes)
        {
            const auto critter_hurtbox = rel_critter_hurtbox.absolute_rect(critter_pos, critter_spr->horizontal_flip(),
                                                                           critter_spr->vertical_flip());

            // Critter hurtbox <- Projectile hitbox
            actor_reg.view<cpn::projectile_states>().each([&](const gba::entity projectile,
                                                              cpn::projectile_states& proj_states) {
                // Ignore vanishing projectile
                if (proj_states.state == cpn::projectile_states::state_t::VANISH)
                    return;
                // Ignore owner (critter is shooter)
                if (projectile == critter_coll_evs->ignore_entity)
                    return;

                auto* proj_spr = actor_reg.try_get<bn::sprite_ptr>(projectile);
                BN_ASSERT(proj_spr);
                const auto proj_pos =
                    proj_spr->top_left_position() +
                    bn::fixed_point(proj_spr->shape_size().width() / 2, proj_spr->shape_size().height() / 2);
                auto* proj_anim = actor_reg.try_get<cpn::sprite_animation>(projectile);
                BN_ASSERT(proj_anim);
                const auto proj_gfx_idx = proj_anim->current_graphics_index();
                const auto& proj_spr_datas = cfg::sprite_datas::get(proj_anim->sprite_kind);
                const auto& proj_spr_frame_datas = proj_spr_datas.frame(proj_gfx_idx);
                auto* proj_coll_evs = actor_reg.try_get<cpn::collision_events>(projectile);
                BN_ASSERT(proj_coll_evs);

                for (const auto& rel_proj_hitbox : proj_spr_frame_datas.hitboxes)
                {
                    const auto proj_hitbox =
                        rel_proj_hitbox.absolute_rect(proj_pos, proj_spr->horizontal_flip(), proj_spr->vertical_flip());

                    if (proj_hitbox.intersects(critter_hurtbox))
                    {
                        if (!critter_coll_evs->collided_entities.full())
                            critter_coll_evs->collided_entities.push_back({.entity = projectile, .hurt = true});
                        if (!proj_coll_evs->collided_entities.full())
                            proj_coll_evs->collided_entities.push_back({.entity = critter, .hurt = false});
                        break;
                    }
                }
            });

            // Critter hurtbox <- Critter hitbox
            actor_reg.view<cpn::critter_states>().each([&](const gba::entity other_critter,
                                                           cpn::critter_states& other_critter_states) {
                // Ignore self
                if (other_critter == critter)
                    return;

                auto* other_critter_spr = actor_reg.try_get<bn::sprite_ptr>(other_critter);
                BN_ASSERT(other_critter_spr);
                const auto other_critter_pos = other_critter_spr->top_left_position() +
                                               bn::fixed_point(other_critter_spr->shape_size().width() / 2,
                                                               other_critter_spr->shape_size().height() / 2);
                auto* other_critter_anim = actor_reg.try_get<cpn::sprite_animation>(other_critter);
                BN_ASSERT(other_critter_anim);
                const auto other_critter_gfx_idx = other_critter_anim->current_graphics_index();
                const auto& other_critter_spr_frame_datas =
                    other_critter_states.sprite_datas().frame(other_critter_gfx_idx);
                auto* other_critter_coll_evs = actor_reg.try_get<cpn::collision_events>(other_critter);
                BN_ASSERT(other_critter_coll_evs);

                for (const auto& rel_other_critter_hitbox : other_critter_spr_frame_datas.hitboxes)
                {
                    const auto other_critter_hitbox = rel_other_critter_hitbox.absolute_rect(
                        other_critter_pos, other_critter_spr->horizontal_flip(), other_critter_spr->vertical_flip());

                    if (other_critter_hitbox.intersects(critter_hurtbox))
                    {
                        if (!critter_coll_evs->collided_entities.full())
                            critter_coll_evs->collided_entities.push_back({.entity = other_critter, .hurt = true});
                        if (!other_critter_coll_evs->collided_entities.full())
                            other_critter_coll_evs->collided_entities.push_back({.entity = critter, .hurt = false});
                        break;
                    }
                }
            });
        }
    });

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
        const auto& breakable_infos = cfg::breakable_infos::get(breakable_states.kind);

        // Breakable hurtbox
        for (const auto& rel_breakable_hurtbox : breakable_spr_frame_datas.hurtboxes)
        {
            const auto breakable_hurtbox = rel_breakable_hurtbox.absolute_rect(
                breakable_pos, breakable_spr->horizontal_flip(), breakable_spr->vertical_flip());

            // Breakable hurtbox <- Projectile hitbox
            actor_reg.view<cpn::projectile_states>().each([&](const gba::entity projectile,
                                                              cpn::projectile_states& proj_states) {
                // Ignore vanishing projectile
                if (proj_states.state == cpn::projectile_states::state_t::VANISH)
                    return;
                // Ignore projectile which can't break this breakable
                if (!breakable_infos.broken_by(proj_states.kind))
                    return;

                auto* proj_spr = actor_reg.try_get<bn::sprite_ptr>(projectile);
                BN_ASSERT(proj_spr);
                const auto proj_pos =
                    proj_spr->top_left_position() +
                    bn::fixed_point(proj_spr->shape_size().width() / 2, proj_spr->shape_size().height() / 2);
                auto* proj_anim = actor_reg.try_get<cpn::sprite_animation>(projectile);
                BN_ASSERT(proj_anim);
                const auto proj_gfx_idx = proj_anim->current_graphics_index();
                const auto& proj_spr_datas = cfg::sprite_datas::get(proj_anim->sprite_kind);
                const auto& proj_spr_frame_datas = proj_spr_datas.frame(proj_gfx_idx);
                auto* proj_coll_evs = actor_reg.try_get<cpn::collision_events>(projectile);
                BN_ASSERT(proj_coll_evs);

                for (const auto& rel_proj_hitbox : proj_spr_frame_datas.hitboxes)
                {
                    const auto proj_hitbox =
                        rel_proj_hitbox.absolute_rect(proj_pos, proj_spr->horizontal_flip(), proj_spr->vertical_flip());

                    if (proj_hitbox.intersects(breakable_hurtbox))
                    {
                        if (!breakable_coll_evs->collided_entities.full())
                            breakable_coll_evs->collided_entities.push_back({.entity = projectile, .hurt = true});
                        if (!proj_coll_evs->collided_entities.full())
                            proj_coll_evs->collided_entities.push_back({.entity = breakable, .hurt = false});
                        break;
                    }
                }
            });
        }
    });
}

void collision_detect_clear(actor_registry& actor_reg)
{
    actor_reg.view<cpn::collision_events>().each([&](cpn::collision_events& coll_evs) {
        coll_evs.collided_wall = false;
        coll_evs.collided_entities.clear();
    });
}

} // namespace mc::gm::ecs::sys
