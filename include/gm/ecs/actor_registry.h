#pragma once

#include "gm/cfg/game_configs.h"

#include "gm/ecs/cpn/auto_destroyer.h"
#include "gm/ecs/cpn/camera_target.h"
#include "gm/ecs/cpn/collision_events.h"
#include "gm/ecs/cpn/critter_states.h"
#include "gm/ecs/cpn/velocity.h"
#include <bn_sprite_animate_actions.h>
#include <bn_sprite_ptr.h>

#include <gba/ecs>

namespace mc::gm::ecs
{

inline constexpr int MAX_ACTORS_COUNT = 64;

using sprite_animate_action_t = bn::sprite_animate_action<cfg::MAX_ANIM_FRAMES>;
using sprite_animate_action_factory_t = sprite_animate_action_t (*)(const bn::sprite_ptr&, int,
                                                                    const bn::sprite_tiles_item&,
                                                                    const bn::span<const std::uint16_t>&);

using actor_registry =
    gba::ecs::registry<MAX_ACTORS_COUNT, bn::sprite_ptr, sprite_animate_action_t, cpn::velocity, cpn::camera_target,
                       cpn::critter_states, cpn::auto_destroyer, cpn::collision_events>;

} // namespace mc::gm::ecs
