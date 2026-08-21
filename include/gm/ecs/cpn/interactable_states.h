#pragma once

#include "gm/cfg/room_entrance.h"
#include "gm/interactable_kind.h"

namespace mc::gm::ecs::cpn
{

struct interactable_states final
{
    interactable_kind kind;

    union {
        cfg::room_entrance entrance;
    };

    interactable_states(interactable_kind);
    interactable_states(interactable_kind, const cfg::room_entrance&);
};

} // namespace mc::gm::ecs::cpn
