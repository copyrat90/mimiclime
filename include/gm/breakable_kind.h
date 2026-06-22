#pragma once

#include <cstdint>
#include <limits>
#include <type_traits>

namespace mc::gm
{

enum class breakable_kind : std::uint8_t
{
    WOOD_FENCE,

    INVALID = std::numeric_limits<std::underlying_type_t<breakable_kind>>::max(),
};

} // namespace mc::gm
