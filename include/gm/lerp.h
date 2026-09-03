#pragma once

#include <bn_fixed_point.h>
#include <bn_math.h>

namespace mc::gm
{

constexpr auto lerp(const bn::fixed_point& src, const bn::fixed_point& dest, const bn::fixed ratio,
                    const bn::fixed epsilon_squared = bn::fixed(0.5f)) -> bn::fixed_point
{
    if (src == dest)
        return src;

    bn::fixed_point result = src + (dest - src) * ratio;

    // Snap to dest if not greater than `epsilon_squared`
    const auto diff = dest - result;
    if (diff.x() * diff.x() + diff.y() * diff.y() <= epsilon_squared)
        result = dest;

    return result;
}

constexpr auto lerp(bn::fixed src, bn::fixed dest, const bn::fixed ratio, const bn::fixed epsilon = bn::fixed(0.5f))
    -> bn::fixed
{
    if (src == dest)
        return src;

    bn::fixed result = src + (dest - src) * ratio;

    // Snap to dest if not greater than `epsilon`
    const auto diff = bn::abs(dest - result);
    if (diff <= epsilon)
        result = dest;

    return result;
}

} // namespace mc::gm
