#pragma once

#include "gm/interactable_kind.h"

#include "ldtk_gen_enums.h"

namespace mc::gm::cfg
{

struct interactable_infos final
{
    interactable_kind kind;
    ldtk::gen::ingame_text_kind text;

    static auto get(interactable_kind) -> const interactable_infos&;
};

} // namespace mc::gm::cfg
