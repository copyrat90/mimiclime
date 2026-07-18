#include "model/direction_t.h"

#include <numbers>
#include <utility>

namespace mcedit::model
{

auto to_normal_vector(direction_t dir) -> ImVec2
{
    static constexpr float DIAGONAL_MULTIPLIER = 1 / std::numbers::sqrt2_v<float>;

    switch (dir)
    {
    case direction_t::NONE:
        return {0, 0};

    case direction_t::UP:
        return {0, -1};
    case direction_t::UP_RIGHT:
        return {DIAGONAL_MULTIPLIER, -DIAGONAL_MULTIPLIER};
    case direction_t::RIGHT:
        return {+1, 0};
    case direction_t::DOWN_RIGHT:
        return {DIAGONAL_MULTIPLIER, DIAGONAL_MULTIPLIER};
    case direction_t::DOWN:
        return {0, +1};
    case direction_t::DOWN_LEFT:
        return {-DIAGONAL_MULTIPLIER, DIAGONAL_MULTIPLIER};
    case direction_t::LEFT:
        return {-1, 0};
    case direction_t::UP_LEFT:
        return {-DIAGONAL_MULTIPLIER, -DIAGONAL_MULTIPLIER};

    default:
        IM_ASSERT(false && "Invalid direction");
    }

    std::unreachable();
}

} // namespace mcedit::model
