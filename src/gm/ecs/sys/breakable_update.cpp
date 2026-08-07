#include "gm/ecs/sys/breakable_update.h"

#include "gm/cfg/sprite_animation_info.h"

namespace mc::gm::ecs::sys
{

void breakable_update(actor_registry& actor_reg)
{
    actor_reg.view<cpn::breakable_states>().each([&](const gba::entity breakable, cpn::breakable_states& states) {
        const auto* coll_evs = actor_reg.try_get<cpn::collision_events>(breakable);
        BN_ASSERT(coll_evs);

        switch (states.state)
        {
            using state_t = cpn::breakable_states::state_t;

        case state_t::IDLE: {
            auto vanish = [&] {
                if (states.state != state_t::VANISH)
                {
                    states.state = state_t::VANISH;
                    // TODO: Start vanish animation
                }
            };

            for (const auto [entity, hurt] : coll_evs->collided_entities)
            {
                if (actor_reg.all_of<cpn::projectile_states>(entity))
                {
                    vanish();
                    break;
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
