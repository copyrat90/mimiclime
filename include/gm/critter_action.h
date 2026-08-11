#pragma once

#include <cstdint>
#include <limits>
#include <type_traits>

namespace mc::gm
{

enum class critter_action : std::uint8_t
{
    NONE,

    DEAD,

    ATTACK,
    PREPARE_DEVOUR,

    DEVOURING,
    CHANGING_SPECIES,
};

} // namespace mc::gm
