#pragma once

#include "gm/ecs/actor_registry.h"
#include "gm/ecs/singleton_registry.h"

namespace mc::gm::ecs::sys
{

void nearby_update(singleton_registry&, const gba::entity singleton_entity, actor_registry&);

}
