#pragma once

#include <bn_top_left_fixed_rect.h>

#include <cstdint>

namespace mc::gm::cfg
{

struct box_data final
{
    std::int8_t x;
    std::int8_t y;
    std::uint8_t width;
    std::uint8_t height;

    auto absolute_rect(const bn::fixed_point& origin, bool horizontal_flip, bool vertical_flip) const
        -> bn::top_left_fixed_rect;
};

} // namespace mc::gm::cfg
