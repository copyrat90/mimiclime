#include "gm/ecs/sys/impl/critter_act_slime.h"

namespace mc::gm::ecs::sys::impl
{

namespace
{

constexpr bn::fixed ATTACK_MOVE_SPEED_MULTIPLIER = 0.5f;
constexpr decltype(cpn::critter_states::attack_countdown) ATTACK_COOLDOWN = 10;

} // namespace

void critter_act_slime(const gba::entity critter, actor_registry& actor_reg)
{
    auto& states = actor_reg.get<cpn::critter_states>(critter);
    [[maybe_unused]] auto& substates = states.substates<cpn::impl::critter_substates_slime>();

    auto* velocity = actor_reg.try_get<cpn::velocity>(critter);
    BN_ASSERT(velocity);

    switch (states.executing_action)
    {
    case critter_action::NONE: {
        if (states.input_direction != direction::NONE)
            states.facing_direction = to_direction_5(states.input_direction, states.facing_direction);

        switch (states.input_action)
        {
        case critter_action::NONE:
            velocity->velocity = states.input_velocity;
            break;

        case critter_action::ATTACK:
            states.executing_action = states.input_action;
            states.attack_countdown = ATTACK_COOLDOWN;
            velocity->velocity = states.input_velocity * ATTACK_MOVE_SPEED_MULTIPLIER;
            break;

        case critter_action::PREPARE_DEVOUR:
            // TODO
            break;

        default:
            break;
        }
    }
    break;

    case critter_action::ATTACK:
        // Doesn't change facing direction while attacking, only velocity
        velocity->velocity = states.input_velocity * ATTACK_MOVE_SPEED_MULTIPLIER;
        break;

    case critter_action::PREPARE_DEVOUR:
        // TODO
        break;

    case critter_action::CHANGING_SPECIES:
        // TODO
        break;

    default:
        break;
    }
}

} // namespace mc::gm::ecs::sys::impl
