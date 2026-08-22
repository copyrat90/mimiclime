#pragma once

#include "gm/ecs/actor_registry.h"

namespace mc::gm::ecs::ut
{

auto find_player_critter(actor_registry&) -> const gba::entity;

auto find_nearby_interactable(const gba::entity critter, actor_registry&) -> const gba::entity;

} // namespace mc::gm::ecs::ut
