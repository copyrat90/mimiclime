#include "gm/direction.h"

#include <bn_keypad.h>
#include <bn_math.h>

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

auto to_normal_vector(direction dir) -> bn::fixed_point
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

auto to_normal_vector(const bn::fixed_point& vector) -> bn::fixed_point
{
    const bn::fixed x = vector.x();
    const bn::fixed y = vector.y();
    const bn::fixed dist_sq = x * x + y * y;
    const bn::fixed dist = bn::sqrt(dist_sq);

    return vector / dist;
}

auto to_direction_9(const bn::fixed_point& vector) -> direction
{
    const bn::fixed x = vector.x();
    const bn::fixed y = vector.y();

    if (x == 0 && y == 0)
        return direction::NONE;

    static constexpr bn::fixed SQRT2 = 1.41421356;

    if (x > 0)
    {
        if (y > 0)
        {
            const bn::fixed yx_d2 = bn::abs(y - x); // y = x, sqrt2 multiplied distance
            if (y - x > 0)
            {
                const bn::fixed x0_d2 = SQRT2 * bn::abs(x); // x = 0, sqrt2 multiplied distance
                return x0_d2 < yx_d2 ? direction::DOWN : direction::DOWN_RIGHT;
            }
            else
            {
                const bn::fixed y0_d2 = SQRT2 * bn::abs(y); // y = 0, sqrt2 multiplied distance
                return y0_d2 < yx_d2 ? direction::RIGHT : direction::DOWN_RIGHT;
            }
        }
        else
        {
            const bn::fixed ymx_d2 = bn::abs(y + x); // y = -x, sqrt2 multiplied distance
            if (y + x < 0)
            {
                const bn::fixed x0_d2 = SQRT2 * bn::abs(x); // x = 0, sqrt2 multiplied distance
                return x0_d2 < ymx_d2 ? direction::UP : direction::UP_RIGHT;
            }
            else
            {
                const bn::fixed y0_d2 = SQRT2 * bn::abs(y); // y = 0, sqrt2 multiplied distance
                return y0_d2 < ymx_d2 ? direction::RIGHT : direction::UP_RIGHT;
            }
        }
    }
    else
    {
        if (y > 0)
        {
            const bn::fixed ymx_d2 = bn::abs(y + x); // y = -x, sqrt2 multiplied distance
            if (y + x < 0)
            {
                const bn::fixed y0_d2 = SQRT2 * bn::abs(y); // y = 0, sqrt2 multiplied distance
                return y0_d2 < ymx_d2 ? direction::LEFT : direction::DOWN_LEFT;
            }
            else
            {
                const bn::fixed x0_d2 = SQRT2 * bn::abs(x); // x = 0, sqrt2 multiplied distance
                return x0_d2 < ymx_d2 ? direction::DOWN : direction::DOWN_LEFT;
            }
        }
        else
        {
            const bn::fixed yx_d2 = bn::abs(y - x); // y = x, sqrt2 multiplied distance
            if (y - x > 0)
            {
                const bn::fixed y0_d2 = SQRT2 * bn::abs(y); // y = 0, sqrt2 multiplied distance
                return y0_d2 < yx_d2 ? direction::LEFT : direction::UP_LEFT;
            }
            else
            {
                const bn::fixed x0_d2 = SQRT2 * bn::abs(x); // x = 0, sqrt2 multiplied distance
                return x0_d2 < yx_d2 ? direction::UP : direction::UP_LEFT;
            }
        }
    }
}

auto to_direction_5(const bn::fixed_point& vector, const direction hint) -> direction
{
    const bn::fixed x = vector.x();
    const bn::fixed y = vector.y();

    if (y > x)
    {
        if (y > -x)
            return direction::DOWN;
        else if (y < -x)
            return direction::LEFT;
        else if (hint == direction::DOWN || hint == direction::LEFT)
            return hint;
        else
            return direction::LEFT;
    }
    else if (y < x)
    {
        if (y > -x)
            return direction::RIGHT;
        else if (y < -x)
            return direction::UP;
        else if (hint == direction::RIGHT || hint == direction::UP)
            return hint;
        else
            return direction::RIGHT;
    }
    else // y == x
    {
        if (y > -x)
        {
            if (hint == direction::RIGHT || hint == direction::DOWN)
                return hint;
            else
                return direction::RIGHT;
        }
        else if (y < -x)
        {
            if (hint == direction::UP || hint == direction::LEFT)
                return hint;
            else
                return direction::LEFT;
        }
        else // y == 0 && x == 0
            return direction::NONE;
    }
}

auto to_direction_5(direction raw, const direction hint) -> direction
{
    direction result = raw;

    switch (raw)
    {
    case direction::UP_RIGHT:
        if (hint == direction::UP || hint == direction::RIGHT)
            result = hint;
        else
            result = direction::RIGHT;
        break;

    case direction::UP_LEFT:
        if (hint == direction::UP || hint == direction::LEFT)
            result = hint;
        else
            result = direction::LEFT;
        break;

    case direction::DOWN_RIGHT:
        if (hint == direction::DOWN || hint == direction::RIGHT)
            result = hint;
        else
            result = direction::RIGHT;
        break;

    case direction::DOWN_LEFT:
        if (hint == direction::DOWN || hint == direction::LEFT)
            result = hint;
        else
            result = direction::LEFT;
        break;

    default:
        break;
    }

    return result;
}

} // namespace mc::gm
