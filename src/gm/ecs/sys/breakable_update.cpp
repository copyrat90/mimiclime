#include "gm/ecs/sys/breakable_update.h"

#include "gm/cfg/breakable_infos.h"
#include "gm/cfg/sprite_animation_info.h"
#include "gm/game_save.h"

namespace mc::gm::ecs::sys
{

void breakable_update(actor_registry& actor_reg, game_save& save)
{
    actor_reg.view<cpn::breakable_states>().each([&](const gba::entity breakable, cpn::breakable_states& states) {
        switch (states.state)
        {
            using state_t = cpn::breakable_states::state_t;

        case state_t::IDLE: {
            if (auto* coll_evs = actor_reg.try_get<cpn::collision_events>(breakable); coll_evs)
            {
                auto vanish = [&] {
                    if (states.state != state_t::VANISH)
                    {
                        states.state = state_t::VANISH;

                        if (states.broken_flag.has_value())
                            save.set_game_flag(*states.broken_flag, true);

                        actor_reg.remove_unchecked(*coll_evs);

                        // TODO: Start vanish animation
                    }
                };

                for (const auto [entity, hurt] : coll_evs->collided_entities)
                {
                    if (const auto* proj_states = actor_reg.try_get<cpn::projectile_states>(entity); proj_states)
                    {
                        const auto& breakable_infos = cfg::breakable_infos::get(states.kind);

                        if (breakable_infos.broken_by(proj_states->kind))
                        {
                            vanish();
                            break;
                        }
                    }
                }
            }
        }
        break;

        case state_t::VANISH: {
            if (auto* spr_anim = actor_reg.try_get<cpn::sprite_animation>(breakable); spr_anim)
            {
                BN_ASSERT(spr_anim->info);
                if (spr_anim->info->forever || spr_anim->done())
                    actor_reg.destroy(breakable);
            }
            else
            {
                actor_reg.destroy(breakable);
            }
        }
        break;

        default:
            BN_ERROR("Invalid breakable state_t: ", static_cast<int>(states.state));
        }
    });
}

} // namespace mc::gm::ecs::sys
