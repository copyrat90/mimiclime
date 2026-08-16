#pragma once

#include <cstdint>

namespace mc::gm::ecs::cpn
{

struct sprite_flicker final
{
    std::uint16_t destroy_countdown;
    std::uint8_t toggle_ticks;
    std::uint8_t toggle_countdown;

    sprite_flicker(decltype(destroy_countdown), decltype(toggle_ticks));
};

} // namespace mc::gm::ecs::cpn
