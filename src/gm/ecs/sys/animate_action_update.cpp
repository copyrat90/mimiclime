#include "gm/ecs/sys/animate_action_update.h"

namespace mc::gm::ecs::sys
{

void animate_action_update(actor_registry& actor_reg)
{
    actor_reg.view<sprite_animate_action_t>().each([&](sprite_animate_action_t& anim_action) {
        if (!anim_action.done())
            anim_action.update();
    });
}

} // namespace mc::gm::ecs::sys
