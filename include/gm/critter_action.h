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

    WANT_TO_DEVOUR,
    MOVE_TO_DEVOUR,
    PRE_CHANGE_SPECIES,
    POST_CHANGE_SPECIES,
};

} // namespace mc::gm
