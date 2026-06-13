#pragma once

#include "gm/cfg/room_entrance.h"

#include <cstdint>

namespace ibn
{
class transitions;
}

namespace mc::gm::ecs::cpn
{

struct room_change_states final
{
    enum class fade_state : std::uint8_t
    {
        FADE_OUT,
        FADE_IN,
    };

    cfg::room_entrance entrance;

    ibn::transitions& transitions;
    fade_state fade;
    std::int8_t countdown;
};

} // namespace mc::gm::ecs::cpn
