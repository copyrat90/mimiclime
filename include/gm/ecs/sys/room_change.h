#pragma once

#include "gm/ecs/actor_registry.h"
#include "gm/ecs/singleton_registry.h"

namespace ibn
{
class transitions;
}

namespace mc::gm
{
struct game_save;
}

namespace mc::gm::ecs::sys
{

void room_change(singleton_registry&, const gba::entity singleton_entity, ibn::transitions&, actor_registry&,
                 const game_save&);

}
