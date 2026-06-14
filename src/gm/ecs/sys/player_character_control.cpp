#include "gm/ecs/sys/player_character_control.h"

#include "gm/ecs/cpn/player_character_controller.h"
#include "gm/ecs/cpn/velocity.h"

#include "gm/cfg/species_infos.h"
#include "gm/direction.h"

namespace mc::gm::ecs::sys
{

void player_character_control(actor_registry& registry)
{
    registry.view<cpn::player_character_controller>().each(
        [&](const gba::entity entity, cpn::player_character_controller& controller) {
            cpn::character_proxy* chara_proxy = registry.try_get<cpn::character_proxy>(entity);
            BN_ASSERT(chara_proxy);
            const auto& species_infos = cfg::species_infos::get(chara_proxy->species());

            cpn::velocity* velocity = registry.try_get<cpn::velocity>(entity);
            if (!velocity)
                velocity = &registry.emplace<cpn::velocity>(entity);

            controller.held_direction = get_direction_from_held_keypad();

            velocity->velocity = to_fixed_point(controller.held_direction) * species_infos.speed();
        });
}

} // namespace mc::gm::ecs::sys
