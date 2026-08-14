#include "gm/ecs/sys/critter_knockback.h"

#include "bn_sprite_items_slime.h"
#include "bn_sprite_palette_items_pal_dead.h"

namespace mc::gm::ecs::sys
{

void critter_knockback(actor_registry& actor_reg)
{
    actor_reg.view<cpn::critter_states>().each([&](const gba::entity critter, cpn::critter_states& states) {
        if (states.knockback_countdown > 0)
        {
            if (--states.knockback_countdown == 0)
            {
                states.knockback_velocity = bn::fixed_point(0, 0);

                auto* sprite = actor_reg.try_get<bn::sprite_ptr>(critter);
                BN_ASSERT(sprite);

                // Revert to non-hurt palette after knockback is done
                const auto next_palette =
                    states.alive() ? bn::sprite_items::slime.palette_item() : bn::sprite_palette_items::pal_dead;
                sprite->set_palette(next_palette);
            }

            auto* velocity = actor_reg.try_get<cpn::velocity>(critter);
            BN_ASSERT(velocity);

            velocity->velocity = states.knockback_velocity;
        }
    });
}

} // namespace mc::gm::ecs::sys
