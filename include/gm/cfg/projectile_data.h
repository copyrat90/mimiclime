#pragma once

#include "gm/direction.h"

#include <bn_fixed.h>

#include <cstdint>

namespace mc::gm::cfg
{

struct projectile_data final
{
    enum class kind_t : std::uint8_t
    {
#include "projectile_kind.txt"
    };

    kind_t kind;
    std::int8_t x;
    std::int8_t y;
    gm::direction direction;
    bn::fixed speed;
};

} // namespace mc::gm::cfg
