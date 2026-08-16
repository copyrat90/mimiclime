#include "gm/ecs/sys/impl/critter_input_player.h"

#include "gm/ecs/ut/find_critter.h"

#include <bn_keypad.h>
#include <bn_sprite_shape_size.h>

namespace mc::gm::ecs::sys::impl
{

void critter_input_player(const gba::entity critter, actor_registry& actor_reg)
{
    cpn::critter_states& states = actor_reg.get<cpn::critter_states>(critter);

    if (states.can_move())
    {
        states.input_direction = get_direction_from_held_keypad();
        states.input_velocity = to_normal_vector(states.input_direction);
    }

    if (bn::keypad::a_pressed() && states.can_attack())
    {
        states.input_action = critter_action::ATTACK;
    }
    else if (bn::keypad::b_held() && states.can_devour())
    {
        const gba::entity nearby_dead_critter = ut::find_nearby_dead_critter(critter, actor_reg);

        if (nearby_dead_critter != gba::entity_null)
        {
            const auto* dead_critter_states = actor_reg.try_get<cpn::critter_states>(nearby_dead_critter);
            BN_ASSERT(dead_critter_states);

            const auto* dead_critter_spr = actor_reg.try_get<bn::sprite_ptr>(nearby_dead_critter);
            BN_ASSERT(dead_critter_spr);
            const bn::fixed_point dead_critter_pos =
                dead_critter_spr->top_left_position() + bn::fixed_point(dead_critter_spr->shape_size().width() / 2,
                                                                        dead_critter_spr->shape_size().height() / 2);

            static constexpr bn::fixed_point POS_DIFF(0, 1);
            states.target_position = dead_critter_pos + POS_DIFF;
            states.devour_critter = nearby_dead_critter;
            states.input_action = critter_action::WANT_TO_DEVOUR;
            states.input_velocity = bn::fixed_point(0, 0);
            states.input_direction = direction::NONE;
        }
    }
}

} // namespace mc::gm::ecs::sys::impl
