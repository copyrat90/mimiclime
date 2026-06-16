#include "gm/ecs/sys/player_character_control.h"

#include "gm/ecs/cpn/player_character_controller.h"
#include "gm/ecs/cpn/velocity.h"

#include "gm/cfg/species_infos.h"
#include "gm/direction.h"

namespace mc::gm::ecs::sys
{

void player_character_control(actor_registry& actor_reg, const singleton_registry& singleton_reg,
                              const gba::entity singleton_entity)
{
    // Can't control player character when room is changing
    if (singleton_reg.all_of<cpn::room_change_states>(singleton_entity))
        return;

    actor_reg.view<cpn::player_character_controller>().each(
        [&](const gba::entity player, cpn::player_character_controller& controller) {
            cpn::character_proxy* chara_proxy = actor_reg.try_get<cpn::character_proxy>(player);
            BN_ASSERT(chara_proxy);
            const auto& species_infos = cfg::species_infos::get(chara_proxy->species());

            cpn::velocity* velocity = actor_reg.try_get<cpn::velocity>(player);
            if (!velocity)
                velocity = &actor_reg.emplace<cpn::velocity>(player);

            controller.held_direction = get_direction_from_held_keypad();

            velocity->velocity = to_normal_vector(controller.held_direction) * species_infos.speed();
        });
}

} // namespace mc::gm::ecs::sys
