#pragma once

#include "gm/projectile_kind.h"

#include <bn_span.h>

#include "ldtk_gen_enums.h"

namespace mc::gm::cfg
{

struct triggerable_infos final
{
    ldtk::gen::triggerable_kind kind;

    // Projectiles that can trigger this triggerable
    bn::span<const projectile_kind> projectiles;

    static auto get(ldtk::gen::triggerable_kind) -> const triggerable_infos&;

    bool triggered_by(projectile_kind) const;
};

} // namespace mc::gm::cfg
