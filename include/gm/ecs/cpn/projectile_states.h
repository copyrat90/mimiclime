#pragma once

#include "gm/projectile_kind.h"

#include <cstdint>

namespace mc::gm::ecs::cpn
{

struct projectile_states final
{
    enum class state_t : std::uint8_t
    {
        FLY,
        VANISH,
    };

    projectile_kind kind;

    state_t state;

    std::uint8_t timeout;

    projectile_states(projectile_kind);
};

} // namespace mc::gm::ecs::cpn
