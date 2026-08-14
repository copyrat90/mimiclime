#include "gm/ecs/sys/impl/critter_input_player.h"

#include <bn_keypad.h>

namespace mc::gm::ecs::sys::impl
{

void critter_input_player(const gba::entity critter, actor_registry& actor_reg)
{
    cpn::critter_states& states = actor_reg.get<cpn::critter_states>(critter);

    if (states.can_move())
    {
        states.input_direction = get_direction_from_held_keypad();
        states.input_velocity = to_normal_vector(states.input_direction);
    }

    if (bn::keypad::a_pressed() && states.can_attack())
        states.input_action = critter_action::ATTACK;

    if (bn::keypad::b_held() && states.can_devour())
    {
        // TODO: Set devour action & species:

        // if (/* There is a nearby dead body of a mob */)
        // {
        //     states.devour_species = /* species of the dead body */;
        //     states.input_action = critter_action::PREPARE_DEVOUR;
        // }
    }
}

} // namespace mc::gm::ecs::sys::impl
