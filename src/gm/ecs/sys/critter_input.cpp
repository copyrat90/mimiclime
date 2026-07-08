#include "gm/ecs/sys/critter_input.h"

#include "gm/ecs/sys/impl/critter_input_mob.h"
#include "gm/ecs/sys/impl/critter_input_player.h"

namespace mc::gm::ecs::sys
{

void critter_input(actor_registry& actor_reg, const singleton_registry& singleton_reg,
                   const gba::entity singleton_entity)
{
    // No input received when room is changing
    if (singleton_reg.all_of<cpn::room_change_states>(singleton_entity))
        return;

    actor_reg.view<cpn::critter_states>().each([&](const gba::entity critter, cpn::critter_states& states) {
        if (states.is_player())
            impl::critter_input_player(critter, actor_reg);
        else
            impl::critter_input_mob(critter, actor_reg);
    });
}

} // namespace mc::gm::ecs::sys
