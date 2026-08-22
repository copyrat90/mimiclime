#pragma once

#include "gm/ecs/actor_registry.h"

namespace mc::gm::ecs::sys
{

// Terrain collision is detected/resolved on the `sys::terrain_collide` instead!
void hitbox_to_hurtbox_collision_detect(actor_registry&);

} // namespace mc::gm::ecs::sys
