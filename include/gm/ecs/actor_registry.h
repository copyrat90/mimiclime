#pragma once

#include "gm/ecs/cpn/auto_destroyer.h"
#include "gm/ecs/cpn/camera_target.h"
#include "gm/ecs/cpn/character_proxy.h"
#include "gm/ecs/cpn/collision_events.h"
#include "gm/ecs/cpn/critter_states.h"
#include "gm/ecs/cpn/velocity.h"

#include <gba/ecs>

namespace mc::gm::ecs
{

inline constexpr int MAX_ACTORS_COUNT = 64;

using actor_registry = gba::ecs::registry<MAX_ACTORS_COUNT, cpn::character_proxy, cpn::velocity, cpn::camera_target,
                                          cpn::critter_states, cpn::auto_destroyer, cpn::collision_events>;

} // namespace mc::gm::ecs
