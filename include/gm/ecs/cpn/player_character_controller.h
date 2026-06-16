#pragma once

#include "gm/direction.h"

namespace mc::gm::ecs::cpn
{

struct player_character_controller final
{
    direction held_direction = direction::NONE;
};

} // namespace mc::gm::ecs::cpn
