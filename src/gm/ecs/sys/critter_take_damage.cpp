#include "gm/ecs/sys/critter_take_damage.h"

#include "bn_sprite_palette_items_pal_hurt.h"

namespace mc::gm::ecs::sys
{

namespace
{

constexpr bn::fixed KNOCKBACK_SPEED = 2.0f;
constexpr decltype(cpn::critter_states::knockback_countdown) KNOCKBACK_DURATION = 10;

} // namespace

void critter_take_damage(actor_registry& actor_reg)
{
    actor_reg.view<cpn::critter_states, cpn::collision_events>().each(
        [&](const gba::entity critter, cpn::critter_states& states, cpn::collision_events& coll_events) {
            // Invincible while knockback
            if (states.knockback_countdown > 0)
                return;

            for (const auto [collided_entity, hurt] : coll_events.collided_entities)
            {
                if (states.alive() && hurt)
                {
                    states.change_hp(-1);

                    // Knockback
                    states.knockback_countdown = KNOCKBACK_DURATION;
                    actor_reg.match<cpn::projectile_states, cpn::critter_states>(
                        collided_entity,
                        [&](cpn::projectile_states&) {
                            auto* proj_velocity = actor_reg.try_get<cpn::velocity>(collided_entity);
                            BN_ASSERT(proj_velocity);

                            states.knockback_velocity = to_normal_vector(proj_velocity->velocity) * KNOCKBACK_SPEED;
                        },
                        [&](cpn::critter_states& atk_critter_states) {
                            states.knockback_velocity =
                                to_normal_vector(atk_critter_states.facing_direction) * KNOCKBACK_SPEED;
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
