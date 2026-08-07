#pragma once

#include "gm/ecs/cpn/breakable_states.h"
#include "gm/ecs/cpn/camera_target.h"
#include "gm/ecs/cpn/collision_events.h"
#include "gm/ecs/cpn/critter_states.h"
#include "gm/ecs/cpn/projectile_states.h"
#include "gm/ecs/cpn/sprite_animation.h"
#include "gm/ecs/cpn/velocity.h"
#include <bn_sprite_ptr.h>

#include <gba/ecs>

namespace mc::gm::ecs
{

inline constexpr int MAX_ACTORS_COUNT = 64;

using actor_registry =
    gba::ecs::registry<MAX_ACTORS_COUNT, bn::sprite_ptr, cpn::sprite_animation, cpn::velocity, cpn::camera_target,
                       cpn::collision_events, cpn::critter_states, cpn::projectile_states, cpn::breakable_states>;

} // namespace mc::gm::ecs
