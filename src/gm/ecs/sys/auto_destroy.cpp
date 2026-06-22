#include "gm/ecs/sys/auto_destroy.h"

namespace mc::gm::ecs::sys
{

void auto_destroy(actor_registry& actor_reg)
{
    // Phase 1: "Flag" destructions.
    // (Not actually destroys anything here, as you might need the other entities' info before their destructions.)
    actor_reg.view<cpn::auto_destroyer>().each([&](const gba::entity entity, cpn::auto_destroyer& destroyer) {
        if (destroyer.destroy_on_timeout)
        {
            if (destroyer.timeout_ticks == 0 || --destroyer.timeout_ticks == 0)
                goto DESTROYED;
        }

        if (destroyer.destroy_on_collide_wall || destroyer.destroy_on_collide_breakable ||
            destroyer.destroy_on_collide_projectile)
        {
            if (auto* collision_events = actor_reg.try_get<cpn::collision_events>(entity); collision_events != nullptr)
            {
                if (destroyer.destroy_on_collide_wall)
                {
                    if (collision_events->collided_wall)
                        goto DESTROYED;
                }

                if (destroyer.destroy_on_collide_critter || destroyer.destroy_on_collide_projectile ||
                    destroyer.destroy_on_collide_breakable)
                {
                    for (const gba::entity coll_entity : collision_events->collided_entities)
                    {
                        auto* coll_chara_proxy = actor_reg.try_get<cpn::character_proxy>(coll_entity);
                        if (!coll_chara_proxy)
                            continue;

                        switch (coll_chara_proxy->meta())
                        {
                            using meta_kind = cpn::character_proxy::meta_kind;

                        case meta_kind::critter:
                            if (destroyer.destroy_on_collide_critter)
                                goto DESTROYED;
                            break;

                        case meta_kind::breakable:
                            if (destroyer.destroy_on_collide_breakable)
                                goto DESTROYED;
                            break;

                        case meta_kind::projectile:
                            if (destroyer.destroy_on_collide_projectile)
                            {
                                for (const projectile_kind detect_projectile : destroyer.detect_projectiles)
                                {
                                    if (coll_chara_proxy->projectile() == detect_projectile)
                                        goto DESTROYED;
                                }
                            }
                            break;

                        default:
                            BN_ERROR("Invalid coll_chara_proxy meta: ", static_cast<int>(coll_chara_proxy->meta()));
                        }
                    }
                }
            }
        }

        return;

    DESTROYED:
        destroyer.destroyed = true;
        return;
    });

    // Phase 2: Actually destroy flagged entities.
    actor_reg.view<cpn::auto_destroyer>().each([&](const gba::entity entity, cpn::auto_destroyer& destroyer) {
        if (destroyer.destroyed)
            actor_reg.destroy(entity);
    });
}

} // namespace mc::gm::ecs::sys
