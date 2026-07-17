#pragma once

#include <cstdint>

namespace mcedit::model
{

struct collision_box final
{
    std::int8_t x;
    std::int8_t y;
    std::uint8_t width;
    std::uint8_t height;
};

} // namespace mcedit::model
