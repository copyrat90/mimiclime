#pragma once

#include "scn/scene.h"

#include <bn_sprite_ptr.h>
#include <bn_vector.h>

namespace mc::scn
{

class title_credits final : public scene
{
public:
    title_credits(scene_context&);

public:
    bool update() override;

private:
    bn::vector<bn::sprite_ptr, 128> _text_sprites;
};

} // namespace mc::scn
