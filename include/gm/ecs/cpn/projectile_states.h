#pragma once

#include <cstdint>

namespace mc::gm::ecs::cpn
{

struct projectile_states final
{
    enum class state_t : std::uint8_t
    {
        FLY,
        VANISH,
    };

    state_t state = state_t::FLY;

    std::uint8_t timeout = 180;
};

} // namespace mc::gm::ecs::cpn
