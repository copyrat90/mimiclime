#pragma once

#include <bn_optional.h>

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

    bn::optional<ldtk::gen::game_flag> broken_flag;

    state_t state = state_t::IDLE;
};

} // namespace mc::gm::ecs::cpn
