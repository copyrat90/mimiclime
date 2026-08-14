#pragma once

#include "gm/ecs/actor_registry.h"
#include "gm/ecs/singleton_registry.h"

namespace mc::gm
{
struct game_save;
}

namespace mc::gm::ecs::sys
{

void player_dead_respawn(actor_registry&, singleton_registry&, const gba::entity singleton_entity, const game_save&);

}
