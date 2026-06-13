#pragma once

#include "scn/scene.h"

namespace mc::scn
{

class game final : public scene
{
public:
    game(scene_context&);

public:
    bool update() override;
};

} // namespace mc::scn
