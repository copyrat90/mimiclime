#pragma once

#include "ldtk_gen_enums.h"

namespace mc::gm::ecs::cpn
{

struct openable_states final
{
    ldtk::gen::openable_kind kind;

    ldtk::gen::game_flag opened;
    bool prev_opened;
};

} // namespace mc::gm::ecs::cpn
