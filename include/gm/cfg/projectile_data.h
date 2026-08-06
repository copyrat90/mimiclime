#pragma once

#include "gm/direction.h"
#include "gm/projectile_kind.h"

#include <bn_fixed.h>

#include <cstdint>

namespace mc::gm::cfg
{

struct projectile_data final
{
    projectile_kind kind;
    std::int8_t x;
    std::int8_t y;
    gm::direction direction;
    bn::fixed speed;
};

} // namespace mc::gm::cfg
