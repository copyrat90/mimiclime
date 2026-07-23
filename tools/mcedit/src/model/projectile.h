#pragma once

#include "model/direction_t.h"

#include <cstdint>

namespace mcedit::model
{

struct projectile final
{
    enum class kind_t : std::uint8_t
    {
        FIREBALL,
    };

    kind_t kind;
    std::int8_t x;
    std::int8_t y;
    direction_t direction;
    float speed;
};

} // namespace mcedit::model
