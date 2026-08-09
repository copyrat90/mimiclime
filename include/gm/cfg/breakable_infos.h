#pragma once

#include "gm/projectile_kind.h"

#include <bn_span.h>

#include "ldtk_gen_enums.h"

namespace mc::gm::cfg
{

struct breakable_infos final
{
    ldtk::gen::breakable_kind kind;

    // Projectiles that can break this breakable
    bn::span<const projectile_kind> projectiles;

    static auto get(ldtk::gen::breakable_kind) -> const breakable_infos&;

    bool broken_by(projectile_kind) const;
};

} // namespace mc::gm::cfg
