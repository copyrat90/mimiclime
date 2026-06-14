#pragma once

#include "gm/ecs/singleton_registry.h"

namespace mc::gm::ecs::sys
{

void room_change(singleton_registry&, const gba::entity singleton_entity, ibn::transitions&);

}
