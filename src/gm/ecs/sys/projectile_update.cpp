#include "gm/ecs/sys/projectile_update.h"

#include "gm/cfg/sprite_animation_info.h"

namespace mc::gm::ecs::sys
{

void projectile_update(actor_registry& actor_reg)
{
    actor_reg.view<cpn::projectile_states>().each(
        [&](const gba::entity projectile, cpn::projectile_states& proj_states) {
            switch (proj_states.state)
            {
                using state_t = cpn::projectile_states::state_t;

            case state_t::FLY: {
                auto vanish = [&] {
                    if (proj_states.state != state_t::VANISH)
                    {
                        proj_states.state = state_t::VANISH;

                        if (auto* coll_evs = actor_reg.try_get<cpn::collision_events>(projectile); coll_evs)
                            actor_reg.remove_unchecked(*coll_evs);

                        // TODO: Start vanish animation
                    }
                };

                if (const auto* coll_evs = actor_reg.try_get<cpn::collision_events>(projectile); coll_evs)
                {
                    bool hit_to_entity = false;
                    for (const auto [entity, hurt] : coll_evs->collided_entities)
                    {
                        if (actor_reg.any_of<cpn::critter_states, cpn::breakable_states>(entity))
                        {
                            hit_to_entity = true;
                            break;
                        }
                    }

                    if (hit_to_entity || coll_evs->collided_wall)
                    {
                        vanish();
                        break;
                    }
                }

                // Timeout
                if (proj_states.timeout == 0)
                {
                    vanish();
                    break;
                }
                else
                    --proj_states.timeout;
            }
            break;

            case state_t::VANISH:
                if (auto* spr_anim = actor_reg.try_get<cpn::sprite_animation>(projectile); spr_anim)
                {
                    BN_ASSERT(spr_anim->info);
                    if (spr_anim->info->forever || spr_anim->done())
                        actor_reg.destroy(projectile);
                }
                else
                {
                    actor_reg.destroy(projectile);
                }
                break;

            default:
                BN_ERROR("Invalid projectile state_t: ", static_cast<int>(proj_states.state));
            }
        });
}

} // namespace mc::gm::ecs::sys
