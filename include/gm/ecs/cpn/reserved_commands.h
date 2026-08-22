#pragma once

#include "gm/cfg/room_entrance.h"

#include <bn_optional.h>

namespace mc::gm::ecs::cpn
{

struct reserved_commands final
{
    bn::optional<cfg::room_entrance> save_game;
};

} // namespace mc::gm::ecs::cpn
