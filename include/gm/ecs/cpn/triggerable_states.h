#pragma once

#include "ldtk_gen_enums.h"

namespace mc::gm::ecs::cpn
{

struct triggerable_states final
{
    ldtk::gen::triggerable_kind kind;

    ldtk::gen::game_flag triggered;
};

} // namespace mc::gm::ecs::cpn
