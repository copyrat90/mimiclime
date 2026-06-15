#pragma once

#include "gm/ecs/cpn/camera_target.h"
#include "gm/ecs/cpn/character_proxy.h"
#include "gm/ecs/cpn/player_character_controller.h"
#include "gm/ecs/cpn/velocity.h"

#include <gba/ecs>

#include "ldtk_gen_project.h"

namespace mc::gm::ecs
{

inline constexpr int MAX_ACTORS_COUNT =
    1 + ldtk::gen::gen_project.defs().get_entity_def(ldtk::gen::entity_ident::mob).max_count();

using actor_registry = gba::ecs::registry<MAX_ACTORS_COUNT, cpn::character_proxy, cpn::velocity,
                                          cpn::player_character_controller, cpn::camera_target>;

} // namespace mc::gm::ecs
