#pragma once

#include "gm/ecs/cpn/actors_of_interest.h"
#include "gm/ecs/cpn/camera_shaker.h"
#include "gm/ecs/cpn/reserved_commands.h"
#include "gm/ecs/cpn/room.h"
#include "gm/ecs/cpn/room_change_states.h"
#include "gm/ecs/cpn/ui_states.h"
#include <bn_camera_ptr.h>
#include <bn_random.h>

#include <gba/ecs>

namespace mc::gm::ecs
{

using singleton_registry =
    gba::ecs::registry<1, cpn::reserved_commands, bn::random, bn::camera_ptr, cpn::camera_shaker, cpn::room,
                       cpn::room_change_states, cpn::actors_of_interest, cpn::ui_states>;

}
