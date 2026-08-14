#include "gm/ecs/sys/player_dead_respawn.h"

#include "gm/game_save.h"

#include "ibn_transitions.h"

namespace mc::gm::ecs::sys
{

namespace
{
constexpr decltype(cpn::room_change_states::countdown) FADE_OUT_START_DELAY = 120;
}

void player_dead_respawn(actor_registry& actor_reg, singleton_registry& singleton_reg,
                         const gba::entity singleton_entity, const game_save& save)
{
    // Don't deal with respawn when room is already changing
    if (singleton_reg.all_of<cpn::room_change_states>(singleton_entity))
        return;

    actor_reg.view<cpn::critter_states>().each([&](const gba::entity player, cpn::critter_states& critter_states) {
        if (critter_states.is_player() && !critter_states.alive())
        {
            // Hide everything except player (pitch black)
            actor_reg.view<bn::sprite_ptr>().each([&](const gba::entity entity, bn::sprite_ptr spr) {
                if (entity != player)
                    spr.set_visible(false);
            });

            auto* room = singleton_reg.try_get<cpn::room>(singleton_entity);
            BN_ASSERT(room);
            room->level_bgs().set_visible(false);

            // Unfocus actor
            auto* focused_actor = singleton_reg.try_get<cpn::focused_actor>(singleton_entity);
            BN_ASSERT(focused_actor);
            focused_actor->actor = gba::entity_null;

            // Reserve change room with delay
            singleton_reg.emplace<cpn::room_change_states>(singleton_entity, save.room_entrance, true,
                                                           cpn::room_change_states::fade_state::INIT,
                                                           FADE_OUT_START_DELAY);
        }
    });
}

} // namespace mc::gm::ecs::sys
