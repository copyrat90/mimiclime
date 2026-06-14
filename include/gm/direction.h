#pragma once

#include <bn_fixed_point.h>

#include <cstdint>

namespace mc::gm
{

enum class direction : std::int8_t
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

auto get_direction_from_held_keypad() -> direction;

auto to_fixed_point(direction dir) -> bn::fixed_point;

} // namespace mc::gm
