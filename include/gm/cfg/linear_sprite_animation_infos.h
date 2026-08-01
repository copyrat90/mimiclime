#pragma once

#include "gm/cfg/sprite_animation_info.h"

namespace mc::gm::cfg::gen
{
enum class sprite_kind;
}

namespace mc::gm::cfg
{

class linear_sprite_animation_infos final
{
public:
    static auto get(gen::sprite_kind) -> const sprite_animation_info&;
};

} // namespace mc::gm::cfg
