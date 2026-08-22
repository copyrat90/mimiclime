#include "gm/ecs/sys/save_game.h"

#include "gm/ecs/ut/find_entity.h"
#include "gm/game_save.h"

namespace mc::gm::ecs::sys
{

void save_game(game_save& save, singleton_registry& singleton_reg, const gba::entity singleton_entity,
               actor_registry& actor_reg)
{
    auto* reserved_commands = singleton_reg.try_get<cpn::reserved_commands>(singleton_entity);
    BN_ASSERT(reserved_commands);

    if (reserved_commands->save_game.has_value())
    {
        const gba::entity player_critter = ut::find_player_critter(actor_reg);
        const auto* player_critter_states = actor_reg.try_get<cpn::critter_states>(player_critter);
        BN_ASSERT(player_critter_states);

        save.player_species = player_critter_states->species();
        save.room_entrance = reserved_commands->save_game.value();
        save.save();

        auto* ui_states = singleton_reg.try_get<cpn::ui_states>(singleton_entity);
        BN_ASSERT(ui_states);

        ui_states->reserved_interactable_tooltip = ldtk::gen::ingame_text_kind::tooltip_save_completed;

        reserved_commands->save_game.reset();
    }
}

} // namespace mc::gm::ecs::sys
