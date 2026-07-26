#include "gm/cfg/linear_sprite_animation_infos.h"

#include "gm/cfg/game_configs.h"
#include "gm/cfg/sprite_datas.h"
#include "ut/enum_utils.h"

#include <bn_array.h>

#include "gen/sprite_kind.h"

namespace mc::gm::cfg
{

namespace
{

constexpr bn::array<std::uint16_t, MAX_ANIM_FRAMES> LINEAR_GRAPHICS_INDEXES = [] {
    bn::array<std::uint16_t, MAX_ANIM_FRAMES> result;
    for (std::uint16_t idx = 0; idx < MAX_ANIM_FRAMES; ++idx)
        result[idx] = idx;
    return result;
}();

constexpr bn::array<sprite_animate_action_info, ut::size_of_enum<gen::sprite_kind>()> INFOS = [] {
    bn::array<sprite_animate_action_info, ut::size_of_enum<gen::sprite_kind>()> result;
    // Set default settings
    for (int idx = 0; idx < ut::size_of_enum<gen::sprite_kind>(); ++idx)
    {
        auto& info = result[idx];
        const auto spr_kind = static_cast<gen::sprite_kind>(idx);

        info.forever = true;
        info.horizontal_flip = false;
        info.vertical_flip = false;
        info.wait_updates = 0;

        int gfx_count = sprite_datas::get(spr_kind).sprite_item().tiles_item().graphics_count();
        if (gfx_count > LINEAR_GRAPHICS_INDEXES.size())
            gfx_count = LINEAR_GRAPHICS_INDEXES.size();

        info.graphics_indexes = bn::span<const std::uint16_t>(LINEAR_GRAPHICS_INDEXES.cbegin(),
                                                              LINEAR_GRAPHICS_INDEXES.cbegin() + gfx_count);
    }

    result[static_cast<int>(gen::sprite_kind::fireball)].wait_updates = 3;

    return result;
}();

} // namespace

auto linear_sprite_animation_infos::get(gen::sprite_kind spr_kind) -> const sprite_animate_action_info&
{
    const int idx = static_cast<int>(spr_kind);
    BN_ASSERT(0 <= idx && idx < ut::size_of_enum<decltype(spr_kind)>(), "Invalid sprite kind: ", idx);

    return INFOS[idx];
}

} // namespace mc::gm::cfg
