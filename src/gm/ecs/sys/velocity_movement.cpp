#include "gm/ecs/sys/velocity_movement.h"

namespace mc::gm::ecs::sys
{

void velocity_movement(actor_registry& actor_reg)
{
    actor_reg.view<cpn::velocity, bn::sprite_ptr>().each([&](cpn::velocity& velocity, bn::sprite_ptr& sprite) {
        sprite.set_position(sprite.position() + velocity.velocity);
    });
}

} // namespace mc::gm::ecs::sys
