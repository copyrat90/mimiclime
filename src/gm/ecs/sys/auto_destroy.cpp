#include "gm/ecs/sys/auto_destroy.h"

namespace mc::gm::ecs::sys
{

void auto_destroy(actor_registry& actor_reg)
{
    actor_reg.view<cpn::auto_destroyer>().each([&](const gba::entity entity, cpn::auto_destroyer& destroyer) {
        if (destroyer.delay == 0)
            actor_reg.destroy(entity);
        else
            --destroyer.delay;
    });
}

} // namespace mc::gm::ecs::sys
