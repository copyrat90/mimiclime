#pragma once

#include "gm/ecs/actor_registry.h"
#include "gm/ecs/singleton_registry.h"

#include "ldtk_gen_enums.h"

namespace mc::gm
{
struct game_save;
}

namespace mc::gm::ecs::ut
{

auto create_triggerable(ldtk::gen::triggerable_kind, ldtk::gen::game_flag triggered, const bn::fixed_point& position,
                        actor_registry&, singleton_registry&, const gba::entity singleton_entity, const game_save&)
    -> const gba::entity;

}
