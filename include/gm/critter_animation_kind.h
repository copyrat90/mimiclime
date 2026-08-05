#pragma once

#include <cstdint>

namespace mc::gm
{

enum class critter_animation_kind : std::uint8_t
{
    IDLE = 0,
    WALK,
    ATTACK,
};

} // namespace mc::gm
