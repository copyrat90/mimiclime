#pragma once

#include <bn_fixed.h>

namespace mc::gm::ecs::cpn
{

struct camera_shaker final
{
    bn::fixed amplitude;
    bn::fixed lerp_to_zero_ratio;
};

} // namespace mc::gm::ecs::cpn
