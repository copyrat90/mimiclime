#include "gm/ecs/sys/clear_critter_input.h"

namespace mc::gm::ecs::sys
{

void clear_critter_input(actor_registry& actor_reg)
{
    actor_reg.view<cpn::critter_states>().each([](cpn::critter_states& states) {
        states.input_action = critter_action::NONE;
        states.input_direction = direction::NONE;
        states.input_velocity = bn::fixed_point(0, 0);
    });
}

} // namespace mc::gm::ecs::sys
