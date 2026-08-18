#pragma once

#include "gm/ecs/actor_registry.h"
#include "gm/ecs/singleton_registry.h"

namespace mc::gm::ecs::sys
{

void critter_input(actor_registry&, singleton_registry&, const gba::entity singleton_entity);
void critter_input_clear(actor_registry&);

} // namespace mc::gm::ecs::sys
