#pragma once

#include <cstdint>

#include "ldtk_gen_enums.h"

namespace mc::gm::ecs::cpn
{

struct breakable_states final
{
    enum class state_t : std::uint8_t
    {
        IDLE,
        VANISH,
    };

    ldtk::gen::breakable_kind kind;

    state_t state = state_t::IDLE;
};

} // namespace mc::gm::ecs::cpn
