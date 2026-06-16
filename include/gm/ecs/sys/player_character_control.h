#pragma once

#include "gm/ecs/actor_registry.h"
#include "gm/ecs/singleton_registry.h"

namespace mc::gm::ecs::sys
{

void player_character_control(actor_registry&, const singleton_registry&, const gba::entity singleton_entity);

}
