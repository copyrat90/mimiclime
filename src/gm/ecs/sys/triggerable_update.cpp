#include "gm/ecs/sys/triggerable_update.h"

#include "gm/cfg/triggerable_infos.h"
#include "gm/game_save.h"

namespace mc::gm::ecs::sys
{

void triggerable_update(actor_registry& actor_reg, game_save& save)
{
    actor_reg.view<cpn::triggerable_states>().each([&](const gba::entity triggerable, cpn::triggerable_states& states) {
        // Does nothing if already triggered
        if (save.game_flag(states.triggered))
            return;

        const auto& infos = cfg::triggerable_infos::get(states.kind);

        if (const auto* coll_evs = actor_reg.try_get<cpn::collision_events>(triggerable); coll_evs)
        {
            for (auto&& [collided_entity, hurt] : coll_evs->collided_entities)
            {
                if (const auto* collided_proj_states = actor_reg.try_get<cpn::projectile_states>(collided_entity);
                    collided_proj_states)
                {
                    // Trigger this triggerable when the projectile hit which can trigger it
                    if (infos.triggered_by(collided_proj_states->kind))
                    {
                        save.set_game_flag(states.triggered, true);

                        if (auto* trig_anim = actor_reg.try_get<cpn::sprite_animation>(triggerable); trig_anim)
                            trig_anim->paused = false;

                        break;
                    }
                }
            }
        }
    });
}

} // namespace mc::gm::ecs::sys
