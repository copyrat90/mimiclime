#pragma once

#include "scn/scene.h"

#include "gm/ecs/actor_registry.h"
#include "gm/ecs/singleton_registry.h"

#include "ldtk_gen_idents_fwd.h"

namespace mc::scn
{

class game final : public scene
{
public:
    game(scene_context&);

public:
    bool update() override;

private:
    gm::ecs::singleton_registry _singleton_registry;
    gm::ecs::actor_registry _actor_registry;

    const gba::entity _singleton_entity;
};

} // namespace mc::scn
