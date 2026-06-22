#include "gm/ecs/sys/impl/critter_input_mob.h"

#include "gm/ecs/sys/impl/critter_input_mob_lizard.h"

namespace mc::gm::ecs::sys::impl
{

void critter_input_mob(const gba::entity critter, actor_registry& actor_reg)
{
    cpn::critter_states& states = actor_reg.get<cpn::critter_states>(critter);

    switch (states.species())
    {
        using species_kind = ldtk::gen::species_kind;

    case species_kind::fire_lizard:
        critter_input_mob_lizard(critter, actor_reg);
        break;

    default:
        BN_ERROR("Invalid critter species: ", static_cast<int>(states.species()));
        break;
    }
}

} // namespace mc::gm::ecs::sys::impl
