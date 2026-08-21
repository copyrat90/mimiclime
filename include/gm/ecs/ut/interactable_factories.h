#pragma once

#include "gm/ecs/actor_registry.h"
#include "gm/ecs/singleton_registry.h"

#include <bn_fixed_point_fwd.h>

namespace mc::gm::cfg
{
struct room_entrance;
}

namespace mc::gm::ecs::ut
{

void create_save_point(const bn::fixed_point& position, const cfg::room_entrance&, actor_registry&, singleton_registry&,
                       const gba::entity singleton_entity);

}
