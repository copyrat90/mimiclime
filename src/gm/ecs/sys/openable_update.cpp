#include "gm/ecs/sys/openable_update.h"

#include "gm/game_save.h"

namespace mc::gm::ecs::sys
{

void openable_update(actor_registry& actor_reg, game_save& save)
{
    actor_reg.view<cpn::openable_states>().each([&](const gba::entity openable, cpn::openable_states& states) {
        // Does nothing if previously opened
        if (states.prev_opened)
            return;

        const bool is_opened = save.game_flag(states.opened);
        if (is_opened)
        {
            auto* openable_anim = actor_reg.try_get<cpn::sprite_animation>(openable);
            BN_ASSERT(openable_anim);
            openable_anim->paused = false;

            states.prev_opened = is_opened;
        }
    });
}

} // namespace mc::gm::ecs::sys
