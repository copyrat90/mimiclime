#pragma once

#include "gm/ecs/actor_registry.h"
#include "gm/ecs/singleton_registry.h"

#include <bn_fixed_point_fwd.h>

#include "ldtk_gen_enums.h"

namespace mc::gm::ecs::ut
{

auto create_player_critter(ldtk::gen::species_kind, const bn::fixed_point& position, actor_registry&,
                           singleton_registry&, const gba::entity singleton_entity) -> const gba::entity;
auto create_mob_critter(ldtk::gen::species_kind, const bn::fixed_point& position, actor_registry&, singleton_registry&,
                        const gba::entity singleton_entity) -> const gba::entity;

} // namespace mc::gm::ecs::ut
