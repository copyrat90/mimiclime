#pragma once

#include <cstdint>

namespace mc::gm::cfg
{

struct box_data final
{
    std::int8_t x;
    std::int8_t y;
    std::uint8_t width;
    std::uint8_t height;
};

} // namespace mc::gm::cfg
