#pragma once

#include <bn_span.h>

#include <cstdint>

namespace mc::gm::cfg
{

struct sprite_animate_action_info final
{
    bool forever;

    bool horizontal_flip;
    bool vertical_flip;

    std::uint16_t wait_updates;
    bn::span<const std::uint16_t> graphics_indexes;
};

} // namespace mc::gm::cfg
