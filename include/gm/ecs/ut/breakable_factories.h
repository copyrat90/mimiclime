#pragma once

#include "gm/ecs/actor_registry.h"
#include "gm/ecs/singleton_registry.h"

#include <bn_fixed_point_fwd.h>

#include "ldtk_gen_enums.h"

namespace mc::gm::ecs::ut
{

auto create_breakable(ldtk::gen::breakable_kind, bn::optional<ldtk::gen::game_flag> broken,
                      const bn::fixed_point& position, actor_registry&, singleton_registry&,
                      const gba::entity singleton_entity) -> const gba::entity;

}
