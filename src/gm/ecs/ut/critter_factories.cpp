#include "gm/ecs/ut/critter_factories.h"

#include "gm/cfg/critter_animation_infos.h"
#include "gm/cfg/species_infos.h"
#include "gm/cfg/sprite_datas.h"
#include "ut/enum_utils.h"

#include <bn_sprite_builder.h>

#include "gen/sprite_kind.h"

namespace mc::gm::ecs::ut
{

namespace
{

auto create_critter_base(ldtk::gen::species_kind species, const bn::fixed_point& position, actor_registry& actor_reg,
                         singleton_registry& singleton_reg, const gba::entity singleton_entity) -> const gba::entity
{
    const auto* camera = singleton_reg.try_get<bn::camera_ptr>(singleton_entity);
    BN_ASSERT(camera);

    const auto& anim_infos = cfg::critter_animation_infos::get(species);
    const auto& spr_datas = cfg::sprite_datas::get(mc::ut::enum_to_enum<cfg::gen::sprite_kind>(species));
    const auto& spr_item = spr_datas.sprite_item();
    const bn::fixed_point pos_diff(spr_item.shape_size().width() / 2, spr_item.shape_size().height() / 2);
    const auto& anim_info = anim_infos.get_info(critter_animation_kind::IDLE, direction::DOWN);

    const gba::entity critter = actor_reg.create();

    bn::sprite_builder spr_builder(spr_item, anim_info.graphics_indexes[0]);
    spr_builder.set_top_left_position(position - pos_diff)
        .set_horizontal_flip(anim_info.horizontal_flip)
        .set_vertical_flip(anim_info.vertical_flip)
        .set_blending_enabled(true)
        .set_camera(*camera);
    auto& spr = actor_reg.emplace<bn::sprite_ptr>(critter, spr_builder

                                                               .release_build());
    actor_reg.emplace<cpn::sprite_animation>(critter, spr, spr_item.tiles_item(), anim_info);

    actor_reg.emplace<cpn::velocity>(critter);
    actor_reg.emplace<cpn::collision_events>(critter);

    return critter;
}

} // namespace

auto create_player_critter(ldtk::gen::species_kind species, const bn::fixed_point& position, actor_registry& actor_reg,
                           singleton_registry& singleton_reg, const gba::entity singleton_entity) -> const gba::entity
{
    const gba::entity player = create_critter_base(species, position, actor_reg, singleton_reg, singleton_entity);
    actor_reg.emplace<cpn::critter_states>(player, true, species);
    actor_reg.emplace<cpn::camera_target>(player, gm::ecs::cpn::camera_target::tracking_priority::LOW, position);

    return player;
}

auto create_mob_critter(ldtk::gen::species_kind species, const bn::fixed_point& position, actor_registry& actor_reg,
                        singleton_registry& singleton_reg, const gba::entity singleton_entity) -> const gba::entity
{
    const gba::entity mob = create_critter_base(species, position, actor_reg, singleton_reg, singleton_entity);
    actor_reg.emplace<cpn::critter_states>(mob, false, species);

    return mob;
}

} // namespace mc::gm::ecs::ut
