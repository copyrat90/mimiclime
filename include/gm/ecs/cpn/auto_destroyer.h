#pragma once

#include "gm/breakable_kind.h"
#include "gm/projectile_kind.h"

#include <bn_vector.h>

#include <cstdint>

#include "ldtk_gen_enums.h"

namespace mc::gm::ecs::cpn
{

struct auto_destroyer final
{
    bool destroyed : 1 = false;

    bool destroy_on_timeout : 1 = false;
    bool destroy_on_collide_wall : 1 = false;
    bool destroy_on_collide_critter : 1 = false;
    bool destroy_on_collide_projectile : 1 = false;
    bool destroy_on_collide_breakable : 1 = false;

    std::uint16_t timeout_ticks = 0;

    bn::vector<projectile_kind, 4> detect_projectiles;
};

} // namespace mc::gm::ecs::cpn
