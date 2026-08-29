#pragma once

#include "gm/ecs/actor_registry.h"

namespace mc::gm
{
struct game_save;
}

namespace mc::gm::ecs::sys
{

void openable_update(actor_registry&, game_save&);

}
