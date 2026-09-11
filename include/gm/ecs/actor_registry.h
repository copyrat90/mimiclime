#pragma once

#include "gm/ecs/cpn/breakable_states.h"
#include "gm/ecs/cpn/camera_target.h"
#include "gm/ecs/cpn/collision_events.h"
#include "gm/ecs/cpn/critter_states.h"
#include "gm/ecs/cpn/interactable_states.h"
#include "gm/ecs/cpn/openable_states.h"
#include "gm/ecs/cpn/projectile_states.h"
#include "gm/ecs/cpn/sign_states.h"
#include "gm/ecs/cpn/sprite_animation.h"
#include "gm/ecs/cpn/sprite_flicker.h"
#include "gm/ecs/cpn/triggerable_states.h"
#include "gm/ecs/cpn/velocity.h"
#include "gm/ecs/cpn/wall.h"
#include <bn_sprite_ptr.h>

#include <gba/ecs>

namespace mc::gm::ecs
{

inline constexpr int MAX_ACTORS_COUNT = 64;

using actor_registry =
    gba::ecs::registry<MAX_ACTORS_COUNT, bn::sprite_ptr, cpn::sprite_animation, cpn::sprite_flicker, cpn::velocity,
                       cpn::camera_target, cpn::collision_events, cpn::wall, cpn::critter_states,
                       cpn::projectile_states, cpn::breakable_states, cpn::sign_states, cpn::interactable_states,
                       cpn::triggerable_states, cpn::openable_states>;

} // namespace mc::gm::ecs
