#include "gm/ecs/ut/find_critter.h"

namespace mc::gm::ecs::ut
{

auto find_player_critter(actor_registry& actor_reg) -> const gba::entity
{
    gba::entity player_critter;

    actor_reg.view<cpn::critter_states>().each(
        [&player_critter](const gba::entity entity, const cpn::critter_states& states) {
            if (states.is_player())
                player_critter = entity;
        });

    return player_critter;
}

} // namespace mc::gm::ecs::ut
