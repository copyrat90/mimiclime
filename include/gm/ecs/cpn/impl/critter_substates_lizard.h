#pragma once

#include "gm/direction.h"

#include <cstdint>

namespace mc::gm::ecs::cpn::impl
{

struct critter_substates_lizard final
{
    enum class strategy_t : std::uint8_t
    {
        MOVE,
        ATTACK_IN_A_ROW,
        REST,
    };

    strategy_t strategy = strategy_t::MOVE;

    direction attack_direction;
    std::uint8_t remaining_attacks;

    std::uint8_t rest_ticks;
};

} // namespace mc::gm::ecs::cpn::impl
