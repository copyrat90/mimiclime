#pragma once

#include <cstdint>
#include <limits>
#include <type_traits>

namespace mc::gm
{

enum class projectile_kind : std::uint8_t
{
    FIREBALL,

    INVALID = std::numeric_limits<std::underlying_type_t<projectile_kind>>::max(),
};

} // namespace mc::gm
