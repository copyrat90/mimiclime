#pragma once

#include <cstdint>

namespace mc::gm::ecs::cpn::impl
{

struct critter_substates_butterfly final
{
    enum class strategy_t : std::uint8_t
    {
        MOVE,
        ATTACK,
        REST,
    };

    strategy_t strategy = strategy_t::MOVE;

    std::uint8_t rest_ticks;
};

} // namespace mc::gm::ecs::cpn::impl
