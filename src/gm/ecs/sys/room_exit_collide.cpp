#include "gm/ecs/sys/room_exit_collide.h"

namespace mc::gm::ecs::sys
{

void room_exit_collide(actor_registry& actor_reg, singleton_registry& singleton_reg, const gba::entity singleton_entity)
{
    // Don't deal with exit collision when room is already changing
    if (singleton_reg.all_of<cpn::room_change_states>(singleton_entity))
        return;

    actor_reg.view<cpn::character_proxy, cpn::critter_states>().each(
        [&](cpn::character_proxy& chara_proxy, cpn::critter_states& critter_states) {
            if (!critter_states.is_player())
                return;

            const auto* room = singleton_reg.try_get<cpn::room>(singleton_entity);
            BN_ASSERT(room);

            gbatool::Character& character = chara_proxy.character();
            const auto& character_relative_collisions =
                character.current_frame_collisions().get_rects_with_mask(gbatool::Character::Mask::CUSTOM_0);

            for (const auto& character_relative_collision : character_relative_collisions)
            {
                const bn::top_left_fixed_rect character_collision =
                    character_relative_collision.get_absolute_rect(character);

                const bn::optional<cfg::room_entrance> entrance = room->collide_with_exit(character_collision);
                if (entrance.has_value())
                {
                    singleton_reg.emplace<cpn::room_change_states>(singleton_entity, entrance.value(),
                                                                   cpn::room_change_states::fade_state::INIT);
                    break;
                }
            }
        });
}

} // namespace mc::gm::ecs::sys
