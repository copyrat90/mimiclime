#include "gm/ecs/sys/room_exit_collide.h"

#include "gm/cfg/sprite_datas.h"

namespace mc::gm::ecs::sys
{

void room_exit_collide(actor_registry& actor_reg, singleton_registry& singleton_reg, const gba::entity singleton_entity)
{
    // Don't deal with exit collision when room is already changing
    if (singleton_reg.all_of<cpn::room_change_states>(singleton_entity))
        return;

    actor_reg.view<cpn::critter_states>().each([&](const gba::entity player, cpn::critter_states& critter_states) {
        if (!critter_states.is_player() || !critter_states.alive())
            return;

        const auto* spr = actor_reg.try_get<bn::sprite_ptr>(player);
        BN_ASSERT(spr);
        const auto* spr_anim = actor_reg.try_get<cpn::sprite_animation>(player);
        BN_ASSERT(spr_anim);

        const auto* room = singleton_reg.try_get<cpn::room>(singleton_entity);
        BN_ASSERT(room);

        const auto player_pos =
            spr->top_left_position() + bn::fixed_point(spr->shape_size().width() / 2, spr->shape_size().height() / 2);
        const auto& frame_datas = critter_states.sprite_datas().frame(spr_anim->current_graphics_index());
        for (const auto& relative_box : frame_datas.wallboxes)
        {
            const auto box = relative_box.absolute_rect(player_pos, spr->horizontal_flip(), spr->vertical_flip());

            const bn::optional<cfg::room_entrance> entrance = room->collide_with_exit(box);
            if (entrance.has_value())
            {
                singleton_reg.emplace<cpn::room_change_states>(singleton_entity, entrance.value(), false,
                                                               cpn::room_change_states::fade_state::INIT);
                break;
            }
        }
    });
}

} // namespace mc::gm::ecs::sys
