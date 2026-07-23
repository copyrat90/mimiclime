#pragma once

#include "model/collision_box.h"
#include "model/projectile.h"

#include <vector>

namespace mcedit::model
{

struct sprite_frame final
{
    std::vector<collision_box> wallboxes;
    std::vector<collision_box> hurtboxes;
    std::vector<collision_box> hitboxes;
    std::vector<projectile> projectiles;
};

} // namespace mcedit::model
