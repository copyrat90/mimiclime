#include "gm/ecs/ut/openable_factories.h"

#include "gm/cfg/linear_sprite_animation_infos.h"
#include "gm/cfg/sprite_datas.h"
#include "gm/ecs/cpn/openable_states.h"
#include "gm/game_save.h"

#include <bn_sprite_builder.h>

namespace mc::gm::ecs::ut
{

auto create_openable(ldtk::gen::openable_kind kind, ldtk::gen::game_flag opened, const bn::fixed_point& position,
                     actor_registry& actor_reg, singleton_registry& singleton_reg, const gba::entity singleton_entity,
                     const game_save& save) -> const gba::entity
{
    const auto* camera = singleton_reg.try_get<bn::camera_ptr>(singleton_entity);
    BN_ASSERT(camera);

    const auto spr_kind = mc::ut::enum_to_enum<cfg::gen::sprite_kind>(kind);
    const auto& spr_datas = cfg::sprite_datas::get(spr_kind);
    const auto& spr_item = spr_datas.sprite_item();
    const bn::fixed_point pos_diff(spr_item.shape_size().width() / 2, spr_item.shape_size().height() / 2);
    const auto& anim_info = cfg::linear_sprite_animation_infos::get(spr_kind);

    const bool is_opened = save.game_flag(opened);
    const std::uint16_t gfx_idx = is_opened ? anim_info.graphics_indexes.back() : anim_info.graphics_indexes.front();

    const gba::entity openable = actor_reg.create();

    bn::sprite_builder spr_builder(spr_item, gfx_idx);
    spr_builder.set_top_left_position(position - pos_diff)
        .set_horizontal_flip(anim_info.horizontal_flip)
        .set_vertical_flip(anim_info.vertical_flip)
        .set_blending_enabled(true)
        .set_camera(*camera);
    auto& spr = actor_reg.emplace<bn::sprite_ptr>(openable, spr_builder.release_build());
    actor_reg.emplace<cpn::sprite_animation>(openable, spr, spr_kind, anim_info, is_opened, !is_opened);

    actor_reg.emplace<cpn::collision_events>(openable, gba::entity_null, true);
    actor_reg.emplace<cpn::wall>(openable);
    actor_reg.emplace<cpn::openable_states>(openable, kind, opened, is_opened);

    return openable;
}

} // namespace mc::gm::ecs::ut
