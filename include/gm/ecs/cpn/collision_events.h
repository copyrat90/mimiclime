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

    struct entity_collision_event final
    {
        const gba::entity entity;
        bool hurt; // the owner of this component, not the above one
    };

    bn::vector<entity_collision_event, 6> collided_entities;
};

} // namespace mc::gm::ecs::cpn
