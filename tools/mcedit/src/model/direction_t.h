#pragma once

#include <cstdint>

namespace mcedit::model
{

enum class direction_t : std::int8_t
{
    NONE = -1,

    UP = 0,
    UP_RIGHT,
    RIGHT,
    DOWN_RIGHT,
    DOWN,
    DOWN_LEFT,
    LEFT,
    UP_LEFT,
};

} // namespace mcedit::model
