#pragma once

#include <cstdint>

namespace mc::gm
{

enum class direction : std::int8_t;

enum class critter_animation_kind : std::int8_t
{
    IDLE = 0,
    WALK,
    ATTACK,
};

enum class critter_animation_id : std::int8_t
{
    NONE = -1,

    IDLE_UP = 4 * (int)critter_animation_kind::IDLE,
    IDLE_RIGHT,
    IDLE_DOWN,
    IDLE_LEFT,

    WALK_UP = 4 * (int)critter_animation_kind::WALK,
    WALK_RIGHT,
    WALK_DOWN,
    WALK_LEFT,

    ATTACK_UP = 4 * (int)critter_animation_kind::ATTACK,
    ATTACK_RIGHT,
    ATTACK_DOWN,
    ATTACK_LEFT
};

auto get_critter_animation_id(critter_animation_kind, direction dir_4) -> critter_animation_id;

} // namespace mc::gm
