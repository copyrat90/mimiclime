#pragma once

#include <gba/bits/ecs/entity.hpp>

namespace mc::gm::ecs::cpn
{

struct actors_of_interest final
{
    gba::entity status_mob;
    gba::entity nearby_interactable;
    gba::entity nearby_sign;
};

} // namespace mc::gm::ecs::cpn
