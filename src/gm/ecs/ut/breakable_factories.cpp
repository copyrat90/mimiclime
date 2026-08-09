#include "gm/ecs/ut/breakable_factories.h"

#include "gm/cfg/linear_sprite_animation_infos.h"
#include "gm/cfg/sprite_datas.h"
#include "gm/ecs/cpn/breakable_states.h"
#include "ut/enum_utils.h"

#include <bn_sprite_builder.h>

namespace mc::gm::ecs::ut
{

auto create_breakable(ldtk::gen::breakable_kind kind, const bn::fixed_point& position, actor_registry& actor_reg,
                      singleton_registry& singleton_reg, const gba::entity singleton_entity) -> const gba::entity
{
    const auto* camera = singleton_reg.try_get<bn::camera_ptr>(singleton_entity);
    BN_ASSERT(camera);

    const auto spr_kind = mc::ut::enum_to_enum<cfg::gen::sprite_kind>(kind);
    const auto& spr_datas = cfg::sprite_datas::get(spr_kind);
    const auto& spr_item = spr_datas.sprite_item();
    const bn::fixed_point pos_diff(spr_item.shape_size().width() / 2, spr_item.shape_size().height() / 2);
    const auto& anim_info = cfg::linear_sprite_animation_infos::get(spr_kind);

    const gba::entity breakable = actor_reg.create();

    bn::sprite_builder spr_builder(spr_item, anim_info.graphics_indexes[0]);
    spr_builder.set_top_left_position(position - pos_diff)
        .set_horizontal_flip(anim_info.horizontal_flip)
        .set_vertical_flip(anim_info.vertical_flip)
        .set_blending_enabled(true)
        .set_camera(*camera);
    auto& spr = actor_reg.emplace<bn::sprite_ptr>(breakable, spr_builder.release_build());
    actor_reg.emplace<cpn::sprite_animation>(breakable, spr, spr_kind, anim_info);

    actor_reg.emplace<cpn::collision_events>(breakable, gba::entity_null, true);
    actor_reg.emplace<cpn::breakable_states>(breakable, kind);

    return breakable;
}

} // namespace mc::gm::ecs::ut
