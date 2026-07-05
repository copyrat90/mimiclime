#include "gm/ecs/sys/camera_target_update.h"

namespace mc::gm::ecs::sys
{

namespace
{

constexpr bn::fixed LOOKAHEAD_LENGTH = 60;

}

void camera_target_update(actor_registry& actor_reg)
{
    // If camera target entity also has a character
    actor_reg.view<cpn::camera_target, cpn::character_proxy>().each(
        [&](const gba::entity entity, cpn::camera_target& target, cpn::character_proxy& chara_proxy) {
            target.position = chara_proxy.character().top_left_position();

            // For player, apply "lookahead" to forward direction
            if (auto* critter_states = actor_reg.try_get<cpn::critter_states>(entity);
                critter_states != nullptr && critter_states->is_player())
            {
                if (critter_states->input_direction != direction::NONE)
                    target.position += to_normal_vector(critter_states->input_direction) * LOOKAHEAD_LENGTH;
            }
        });
}

} // namespace mc::gm::ecs::sys
