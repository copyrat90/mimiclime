#pragma once

#include <bn_vector.h>

#include <gba/ecs>

namespace mc::gm::ecs::cpn
{

struct collision_events final
{
    // Do not detect collisions with this entity
    gba::entity ignore_entity;

    bool collided_wall = false;
    bn::vector<const gba::entity, 6> collided_entities;
};

} // namespace mc::gm::ecs::cpn
