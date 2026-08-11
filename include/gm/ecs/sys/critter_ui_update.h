#pragma once

#include "gm/ecs/actor_registry.h"
#include "gm/ecs/singleton_registry.h"

namespace mc::ut
{
class text_generators;
}

namespace mc::gm::ecs::sys
{

void critter_ui_update(singleton_registry&, const gba::entity singleton_entity, actor_registry&, mc::ut::text_generators&);

}
