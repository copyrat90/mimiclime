#include "gm/ecs/sys/hitbox_to_hurtbox_collision_detect.h"

#include "gm/cfg/sprite_datas.h"

#include "dev/devbuild.h"
#if MC_DEVBUILD
#include <bn_log.h>
#endif

#include <bn_top_left_fixed_rect.h>

namespace mc::gm::ecs::sys
{

void hitbox_to_hurtbox_collision_detect(actor_registry& actor_reg)
{
    // `ent_0`: Hitbox
    actor_reg.view<cpn::collision_events, cpn::sprite_animation, bn::sprite_ptr>().each(
        [&](const gba::entity ent_0, cpn::collision_events& coll_evs_0, cpn::sprite_animation& spr_anim_0,
            bn::sprite_ptr& spr_0) {
            const auto gfx_idx_0 = spr_anim_0.current_graphics_index();
            const auto& spr_datas_0 = cfg::sprite_datas::get(spr_anim_0.sprite_kind);
            const auto& spr_frame_datas_0 = spr_datas_0.frame(gfx_idx_0);

            if (spr_frame_datas_0.hitboxes.empty())
                return;

            const auto pos_0 = spr_0.top_left_position() +
                               bn::fixed_point(spr_0.shape_size().width() / 2, spr_0.shape_size().height() / 2);

            // `ent_1`: Hurtbox
            actor_reg.view<cpn::collision_events, cpn::sprite_animation, bn::sprite_ptr>().each(
                [&](const gba::entity ent_1, cpn::collision_events& coll_evs_1, cpn::sprite_animation& spr_anim_1,
                    bn::sprite_ptr& spr_1) {
                    // Ignore self
                    if (ent_0 == ent_1)
                        return;
                    // Ignore pre-config ignore entity
                    if (coll_evs_0.ignore_entity == ent_1 || coll_evs_1.ignore_entity == ent_0)
                        return;

                    const auto gfx_idx_1 = spr_anim_1.current_graphics_index();
                    const auto& spr_datas_1 = cfg::sprite_datas::get(spr_anim_1.sprite_kind);
                    const auto& spr_frame_datas_1 = spr_datas_1.frame(gfx_idx_1);

                    if (spr_frame_datas_1.hurtboxes.empty())
                        return;

                    const auto pos_1 = spr_1.top_left_position() +
                                       bn::fixed_point(spr_1.shape_size().width() / 2, spr_1.shape_size().height() / 2);

                    for (const auto& rel_hitbox_0 : spr_frame_datas_0.hitboxes)
                    {
                        const auto hitbox_0 =
                            rel_hitbox_0.absolute_rect(pos_0, spr_0.horizontal_flip(), spr_0.vertical_flip());

                        for (const auto& rel_hurtbox_1 : spr_frame_datas_1.hurtboxes)
                        {
                            const auto hurtbox_1 =
                                rel_hurtbox_1.absolute_rect(pos_1, spr_1.horizontal_flip(), spr_1.vertical_flip());

                            if (hitbox_0.intersects(hurtbox_1))
                            {
                                if (!coll_evs_0.collided_entities.full())
                                    coll_evs_0.collided_entities.push_back({.entity = ent_1, .hurt = false});
#if MC_DEVBUILD
                                else
                                    BN_LOG("Hit #", static_cast<int>(ent_0.slot), " -> Hurt #",
                                           static_cast<int>(ent_1.slot), " ignored");
#endif
                                if (!coll_evs_1.collided_entities.full())
                                    coll_evs_1.collided_entities.push_back({.entity = ent_0, .hurt = true});
#if MC_DEVBUILD
                                else
                                    BN_LOG("Hurt #", static_cast<int>(ent_1.slot), " <- Hit #",
                                           static_cast<int>(ent_0.slot), " ignored");
#endif
                                return;
                            }
                        }
                    }
                });
        });
}

} // namespace mc::gm::ecs::sys
