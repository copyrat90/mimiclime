#include "gm/ecs/sys/projectile_hit.h"

#include "gm/cfg/sprite_animation_info.h"

namespace mc::gm::ecs::sys
{

void projectile_hit(actor_registry& actor_reg)
{
    actor_reg.view<cpn::projectile_states>().each(
        [&](const gba::entity projectile, cpn::projectile_states& proj_states) {
            const auto* coll_evs = actor_reg.try_get<cpn::collision_events>(projectile);
            BN_ASSERT(coll_evs);

            switch (proj_states.state)
            {
                using state_t = cpn::projectile_states::state_t;

            case state_t::FLY: {
                auto vanish = [&] {
                    if (proj_states.state != state_t::VANISH)
                    {
                        proj_states.state = state_t::VANISH;
                        // TODO: Start vanish animation
                    }
                };

                // Hit to critter
                for (const auto [entity, hurt] : coll_evs->collided_entities)
                {
                    bool ever_hit = false;
                    if (auto* critter_states = actor_reg.try_get<cpn::critter_states>(entity); critter_states)
                    {
                        // TODO: Proper hurt registration w/ critter hurt animation, knockback, etc.
                        critter_states->change_hp(-1);

                        ever_hit = true;
                    }

                    if (ever_hit)
                    {
                        vanish();
                        break;
                    }
                }

                // Hit by wall
                if (coll_evs->collided_wall)
                {
                    vanish();
                    break;
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
