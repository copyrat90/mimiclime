#include "gm/ecs/sys/sprite_flicker_update.h"

namespace mc::gm::ecs::sys
{

void sprite_flicker_update(actor_registry& actor_reg)
{
    actor_reg.view<cpn::sprite_flicker, bn::sprite_ptr>().each(
        [&](const gba::entity entity, cpn::sprite_flicker& flicker, bn::sprite_ptr& sprite) {
            if (flicker.destroy_countdown == 0 || --flicker.destroy_countdown == 0)
            {
                sprite.set_visible(true);
                actor_reg.remove_unchecked(flicker);
            }
            else if (flicker.toggle_countdown == 0 || --flicker.toggle_countdown == 0)
            {
                sprite.set_visible(!sprite.visible());
                flicker.toggle_countdown = flicker.toggle_ticks;
            }
        });
}

} // namespace mc::gm::ecs::sys
