#include "gm/ecs/sys/critter_take_damage.h"

#include "gm/ecs/ut/find_critter.h"

#include "bn_sprite_palette_items_pal_hurt.h"

namespace mc::gm::ecs::sys
{

namespace
{

constexpr bn::fixed KNOCKBACK_SPEED = 2.0f;
constexpr decltype(cpn::critter_states::knockback_countdown) KNOCKBACK_DURATION = 10;

} // namespace

void critter_take_damage(actor_registry& actor_reg, singleton_registry& singleton_reg,
                         const gba::entity singleton_entity)
{
    const gba::entity player = ut::find_player_critter(actor_reg);

    auto* actors_of_interest = singleton_reg.try_get<cpn::actors_of_interest>(singleton_entity);
    BN_ASSERT(actors_of_interest);

    actor_reg.view<cpn::critter_states, cpn::collision_events>().each(
        [&](const gba::entity critter, cpn::critter_states& states, cpn::collision_events& coll_events) {
            if (states.invincible())
                return;

            for (const auto [collided_entity, hurt] : coll_events.collided_entities)
            {
                if (states.alive() && hurt)
                {
                    states.change_hp(-1);
                    ++states.invincible_shared_counter;

                    states.knockback_countdown = KNOCKBACK_DURATION;
                    actor_reg.match<cpn::projectile_states, cpn::critter_states>(
                        collided_entity,
                        [&](cpn::projectile_states&) {
                            auto* proj_velocity = actor_reg.try_get<cpn::velocity>(collided_entity);
                            BN_ASSERT(proj_velocity);
                            auto* proj_coll_evs = actor_reg.try_get<cpn::collision_events>(collided_entity);
                            BN_ASSERT(proj_coll_evs);

                            states.knockback_velocity = to_normal_vector(proj_velocity->velocity) * KNOCKBACK_SPEED;

                            // Show status of the mob that shot the player critter.
                            if (critter == player)
                                actors_of_interest->status_mob = proj_coll_evs->ignore_entity;
                            // Show status of the mob that the player critter shot.
                            else if (proj_coll_evs->ignore_entity == player)
                                actors_of_interest->status_mob = critter;
                        },
                        [&](cpn::critter_states& atk_critter_states) {
                            states.knockback_velocity =
                                to_normal_vector(atk_critter_states.facing_direction) * KNOCKBACK_SPEED;

                            // Show status of the mob that attacked the player critter.
                            if (critter == player)
                                actors_of_interest->status_mob = collided_entity;
                            // Show status of the mob that's attacked by the player critter.
                            else if (collided_entity == player)
                                actors_of_interest->status_mob = critter;
                        });

                    // Hurt palette while knockback
                    auto* critter_sprite = actor_reg.try_get<bn::sprite_ptr>(critter);
                    BN_ASSERT(critter_sprite);
                    critter_sprite->set_palette(bn::sprite_palette_items::pal_hurt);

                    break;
                }
            }
        });
}

} // namespace mc::gm::ecs::sys
