#include "gm/ecs/sys/collision_detect_clear.h"

namespace mc::gm::ecs::sys
{

void collision_detect_clear(actor_registry& actor_reg)
{
    actor_reg.view<cpn::collision_events>().each([&](cpn::collision_events& coll_evs) {
        coll_evs.collided_wall = false;
        coll_evs.collided_entities.clear();
    });
}

} // namespace mc::gm::ecs::sys
