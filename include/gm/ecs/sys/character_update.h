#pragma once

#include "gm/ecs/actor_registry.h"
#include "gm/ecs/singleton_registry.h"

namespace mc::gm::ecs::sys
{

/// @brief Updates the `character_proxy`.
///
/// Specifically, this system is responsible for:
/// 1. Updating character animations.
/// 2. Updating positions by applying velocity, considering wall collisions.
/// 3. Y-Sort after updating positions.
void character_update(actor_registry&, singleton_registry&, const gba::entity singleton_entity);

} // namespace mc::gm::ecs::sys
