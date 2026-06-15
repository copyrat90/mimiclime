#pragma once

#include "gm/ecs/singleton_registry.h"
#include "gm/ecs/actor_registry.h"

namespace mc::gm::ecs::sys
{

void camera_update(singleton_registry&, const gba::entity singleton_entity, actor_registry&);

}
