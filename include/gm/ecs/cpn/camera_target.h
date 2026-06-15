#pragma once

#include <bn_fixed_point.h>

#include <cstdint>

namespace mc::gm::ecs::cpn
{

struct camera_target final
{
    enum class tracking_priority : std::uint8_t
    {
        LOW,
        HIGH,
    };

    tracking_priority priority;

    bn::fixed_point position;
};

} // namespace mc::gm::ecs::cpn
