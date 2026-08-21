#include "gm/ecs/ut/interactable_factories.h"

#include "gm/cfg/room_entrance.h"
#include "gm/cfg/sprite_datas.h"

#include <bn_sprite_builder.h>

namespace mc::gm::ecs::ut
{

void create_save_point(const bn::fixed_point& position, const cfg::room_entrance& entrance, actor_registry& actor_reg,
                       singleton_registry& singleton_reg, const gba::entity singleton_entity)
{
    const auto* camera = singleton_reg.try_get<bn::camera_ptr>(singleton_entity);
    BN_ASSERT(camera);

    const auto& spr_datas = cfg::sprite_datas::get(cfg::gen::sprite_kind::save_point);
    const auto& spr_item = spr_datas.sprite_item();
    const bn::fixed_point pos_diff(spr_item.shape_size().width() / 2, spr_item.shape_size().height() / 2);

    const gba::entity interactable = actor_reg.create();

    bn::sprite_builder spr_builder(spr_item);
    spr_builder.set_top_left_position(position - pos_diff).set_blending_enabled(true).set_camera(*camera);
    actor_reg.emplace<bn::sprite_ptr>(interactable, spr_builder.release_build());

    actor_reg.emplace<cpn::interactable_states>(interactable, interactable_kind::save_point, entrance);
}

} // namespace mc::gm::ecs::ut
