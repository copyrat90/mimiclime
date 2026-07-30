#pragma once

#include <bn_fixed_point.h>

#include <cstdint>

namespace mc::gm
{

enum class direction : std::int8_t
{
#include "direction.txt"
};

auto get_direction_from_held_keypad() -> direction;

auto to_normal_vector(direction dir) -> bn::fixed_point;
auto to_normal_vector(const bn::fixed_point& vector) -> bn::fixed_point;
auto to_direction_9(const bn::fixed_point& vector) -> direction;
auto to_direction_5(const bn::fixed_point& vector, direction hint) -> direction;
auto to_direction_5(direction raw, direction hint) -> direction;

} // namespace mc::gm
