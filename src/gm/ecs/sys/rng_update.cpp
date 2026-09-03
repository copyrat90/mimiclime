#include "gm/ecs/sys/rng_update.h"

namespace mc::gm::ecs::sys
{

void rng_update(singleton_registry& singleton_reg, const gba::entity singleton_entity)
{
    auto* rng = singleton_reg.try_get<bn::random>(singleton_entity);
    BN_ASSERT(rng);

    rng->update();
}

} // namespace mc::gm::ecs::sys
