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

auto to_normal_vector(direction dir) -> bn::fixed_point;
auto to_direction_8(const bn::fixed_point& vector) -> direction;
auto to_direction_4(const bn::fixed_point& vector, direction hint) -> direction;
auto to_non_diagonal_direction(direction raw, direction hint) -> direction;

} // namespace mc::gm
