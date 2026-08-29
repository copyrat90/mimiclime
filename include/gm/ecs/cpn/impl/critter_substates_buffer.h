#pragma once

#include "gm/ecs/cpn/impl/critter_substates_butterfly.h"
#include "gm/ecs/cpn/impl/critter_substates_eel.h"
#include "gm/ecs/cpn/impl/critter_substates_lizard.h"
#include "gm/ecs/cpn/impl/critter_substates_slime.h"

#include <algorithm>
#include <cstddef>

namespace mc::gm::ecs::cpn::impl
{

inline constexpr auto MAX_CRIT_SUBST_SIZE = std::max({
    sizeof(critter_substates_slime),
    sizeof(critter_substates_lizard),
    sizeof(critter_substates_eel),
    sizeof(critter_substates_butterfly),
});

inline constexpr auto MAX_CRIT_SUBST_ALIGN = std::max({
    alignof(critter_substates_slime),
    alignof(critter_substates_lizard),
    alignof(critter_substates_eel),
    alignof(critter_substates_butterfly),
});

struct critter_substates_buffer final
{
    alignas(MAX_CRIT_SUBST_ALIGN) std::byte buffer[MAX_CRIT_SUBST_SIZE];
};

} // namespace mc::gm::ecs::cpn::impl
