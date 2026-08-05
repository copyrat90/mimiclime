#pragma once

#include "gm/ecs/actor_registry.h"

namespace mc::gm::ecs::sys
{

// Wall collision is detected/resolved on the `sys::velocity_movement` instead!
void collision_detect(actor_registry&);

void collision_detect_clear(actor_registry&);

} // namespace mc::gm::ecs::sys
