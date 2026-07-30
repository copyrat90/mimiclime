#pragma once

#include "model/direction_t.h"

#include <cstdint>
#include <string_view>

namespace mcedit::model
{

struct projectile final
{
    std::string_view kind;
    std::int8_t x;
    std::int8_t y;
    direction_t direction;
    float speed;
};

} // namespace mcedit::model
