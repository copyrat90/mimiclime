#pragma once

#include "gm/projectile_kind.h"

namespace mc::gm::cfg
{

struct projectile_infos final
{
    projectile_kind kind;
    std::uint8_t timeout;

    static auto get(projectile_kind) -> const projectile_infos&;
};

} // namespace mc::gm::cfg
