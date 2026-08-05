#include "gm/ecs/sys/camera_target_update.h"

#include <bn_sprite_shape_size.h>

namespace mc::gm::ecs::sys
{

namespace
{

constexpr bn::fixed LOOKAHEAD_LENGTH = 60;

}

void camera_target_update(actor_registry& actor_reg)
{
    // If camera target entity also has a sprite
    actor_reg.view<cpn::camera_target, bn::sprite_ptr>().each(
        [&](const gba::entity entity, cpn::camera_target& target, bn::sprite_ptr& sprite) {
            // Sync the camera target position with sprite position
            const bn::fixed_point pos_diff(sprite.shape_size().width() / 2, sprite.shape_size().height() / 2);
            target.position = sprite.top_left_position() + pos_diff;

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
