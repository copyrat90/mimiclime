#pragma once

#include "gm/ecs/cpn/impl/critter_substates_slime.h"
#include "gm/ecs/cpn/impl/critter_substates_lizard.h"

#include <algorithm>
#include <cstddef>

namespace mc::gm::ecs::cpn::impl
{

inline constexpr auto MAX_CRIT_SUBST_SIZE = std::max({sizeof(critter_substates_slime), sizeof(critter_substates_lizard)});

inline constexpr auto MAX_CRIT_SUBST_ALIGN = std::max({alignof(critter_substates_slime), alignof(critter_substates_lizard)});

struct critter_substates_buffer final
{
    alignas(MAX_CRIT_SUBST_ALIGN) std::byte buffer[MAX_CRIT_SUBST_SIZE];
};

} // namespace mc::gm::ecs::cpn::impl
