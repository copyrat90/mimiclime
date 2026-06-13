#pragma once

#include "gm/ecs/cpn/room.h"
#include "gm/ecs/cpn/room_change_states.h"
#include <bn_camera_ptr.h>

#include <gba/ecs>

namespace mc::gm::ecs
{

using singleton_registry = gba::ecs::registry<1, bn::camera_ptr, cpn::room, cpn::room_change_states>;

}
