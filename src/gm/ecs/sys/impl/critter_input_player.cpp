#include "gm/ecs/sys/impl/critter_input_player.h"

#include <bn_keypad.h>

namespace mc::gm::ecs::sys::impl
{

void critter_input_player(const gba::entity critter, actor_registry& actor_reg)
{
    cpn::critter_states& states = actor_reg.get<cpn::critter_states>(critter);

    states.input_direction = get_direction_from_held_keypad();
    states.input_velocity = to_normal_vector(states.input_direction);

    if (bn::keypad::a_pressed())
        states.input_action = critter_action::ATTACK;
}

} // namespace mc::gm::ecs::sys::impl
