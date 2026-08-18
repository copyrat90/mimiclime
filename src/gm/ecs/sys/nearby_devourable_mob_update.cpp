#include "gm/ecs/sys/nearby_devourable_mob_update.h"

#include "gm/ecs/ut/find_critter.h"

namespace mc::gm::ecs::sys
{

void nearby_devourable_mob_update(singleton_registry& singleton_reg, const gba::entity singleton_entity,
                                  actor_registry& actor_reg)
{
    const gba::entity player_critter = ut::find_player_critter(actor_reg);
    BN_ASSERT(actor_reg.valid(player_critter));

    auto* actors_of_interest = singleton_reg.try_get<cpn::actors_of_interest>(singleton_entity);
    BN_ASSERT(actors_of_interest);

    actors_of_interest->nearby_devourable_mob = ut::find_nearby_dead_critter(player_critter, actor_reg);
}

} // namespace mc::gm::ecs::sys
