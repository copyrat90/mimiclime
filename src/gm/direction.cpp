#include "gm/direction.h"

#include <bn_keypad.h>

#include <utility>

namespace mc::gm
{

auto get_direction_from_held_keypad() -> direction
{
    const int x = (!bn::keypad::left_held() && !bn::keypad::right_held()) ? 0
                  : (bn::keypad::left_held() && bn::keypad::right_held()) ? 0
                  : (bn::keypad::left_held())                             ? -1
                                                                          : +1;
    const int y = (!bn::keypad::up_held() && !bn::keypad::down_held()) ? 0
                  : (bn::keypad::up_held() && bn::keypad::down_held()) ? 0
                  : (bn::keypad::up_held())                            ? -1
                                                                       : +1;

    switch (x)
    {
    case -1:
        switch (y)
        {
        case -1:
            return direction::UP_LEFT;
        case 0:
            return direction::LEFT;
        case +1:
            return direction::DOWN_LEFT;
        default:
            std::unreachable();
        }
        break;

    case 0:
        switch (y)
        {
        case -1:
            return direction::UP;
        case 0:
            return direction::NONE;
        case +1:
            return direction::DOWN;
        default:
            std::unreachable();
        }
        break;

    case +1:
        switch (y)
        {
        case -1:
            return direction::UP_RIGHT;
        case 0:
            return direction::RIGHT;
        case +1:
            return direction::DOWN_RIGHT;
        default:
            std::unreachable();
        }
        break;

    default:
        std::unreachable();
    }

    std::unreachable();
}

auto to_fixed_point(direction dir) -> bn::fixed_point
{
    static constexpr bn::fixed DIAGONAL_MULTIPLIER = bn::fixed(0.7071067811865475244);

    switch (dir)
    {
    case direction::NONE:
        return {0, 0};

    case direction::UP:
        return {0, -1};
    case direction::UP_RIGHT:
        return {DIAGONAL_MULTIPLIER, -DIAGONAL_MULTIPLIER};
    case direction::RIGHT:
        return {+1, 0};
    case direction::DOWN_RIGHT:
        return {DIAGONAL_MULTIPLIER, DIAGONAL_MULTIPLIER};
    case direction::DOWN:
        return {0, +1};
    case direction::DOWN_LEFT:
        return {-DIAGONAL_MULTIPLIER, DIAGONAL_MULTIPLIER};
    case direction::LEFT:
        return {-1, 0};
    case direction::UP_LEFT:
        return {-DIAGONAL_MULTIPLIER, -DIAGONAL_MULTIPLIER};

    default:
        BN_ERROR("Invalid direction: ", (int)dir);
    }

    std::unreachable();
}

} // namespace mc::gm
