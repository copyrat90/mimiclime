#pragma once

#include "gm/ecs/actor_registry.h"
#include "gm/ecs/singleton_registry.h"

namespace mc::gm
{
struct game_save;
}

namespace mc::gm::ecs::sys
{

void save_game(game_save&, singleton_registry&, const gba::entity singleton_entity, actor_registry& actor_reg);

}
