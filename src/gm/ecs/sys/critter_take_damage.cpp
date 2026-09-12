#include "gm/ecs/sys/critter_take_damage.h"

#include "gm/ecs/ut/find_entity.h"

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
            if (states.invincible() || !states.alive())
                return;

            for (const auto [collided_entity, hurt] : coll_events.collided_entities)
            {
                if (!hurt)
                    continue;

                if (const auto* collided_projectile_states = actor_reg.try_get<cpn::projectile_states>(collided_entity);
                    collided_projectile_states)
                {
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
                }
                else if (const auto* attacked_critter_states = actor_reg.try_get<cpn::critter_states>(collided_entity);
                         attacked_critter_states)
                {
                    states.knockback_velocity =
                        to_normal_vector(attacked_critter_states->facing_direction) * KNOCKBACK_SPEED;

                    // Show status of the mob that attacked the player critter.
                    if (critter == player)
                        actors_of_interest->status_mob = collided_entity;
                    // Show status of the mob that's attacked by the player critter.
                    else if (collided_entity == player)
                        actors_of_interest->status_mob = critter;
                }

                states.knockback_countdown = KNOCKBACK_DURATION;

                states.change_hp(-1);
                if (!states.alive() && !states.is_player())
                    actor_reg.emplace<cpn::interactable_states>(critter, interactable_kind::devourable_mob);

                // Hurt palette while knockback
                ++states.invincible_shared_counter;
                auto* critter_sprite = actor_reg.try_get<bn::sprite_ptr>(critter);
                BN_ASSERT(critter_sprite);
                critter_sprite->set_palette(bn::sprite_palette_items::pal_hurt);

                // Start camera shake on player hurt
                if (states.is_player())
                {
                    static constexpr cpn::camera_shaker CAM_SHAKER{.amplitude = 2.5f, .lerp_to_zero_ratio = 0.2f};
                    singleton_reg.emplace_or_replace<cpn::camera_shaker>(singleton_entity, CAM_SHAKER);
                }

                break;
            }
        });
}

} // namespace mc::gm::ecs::sys
