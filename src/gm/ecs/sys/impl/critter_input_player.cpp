#include "gm/ecs/sys/impl/critter_input_player.h"

#include <bn_keypad.h>
#include <bn_sprite_shape_size.h>

namespace mc::gm::ecs::sys::impl
{

void critter_input_player(const gba::entity critter, actor_registry& actor_reg, singleton_registry& singleton_reg,
                          const gba::entity singleton_entity)
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
        auto* actors_of_interest = singleton_reg.try_get<cpn::actors_of_interest>(singleton_entity);
        BN_ASSERT(actors_of_interest);

        if (actor_reg.valid(actors_of_interest->nearby_devourable_mob))
        {
            const auto* devourable_mob_states =
                actor_reg.try_get<cpn::critter_states>(actors_of_interest->nearby_devourable_mob);
            BN_ASSERT(devourable_mob_states);

            const auto* devourable_mob_spr =
                actor_reg.try_get<bn::sprite_ptr>(actors_of_interest->nearby_devourable_mob);
            BN_ASSERT(devourable_mob_spr);
            const bn::fixed_point devourable_mob_pos = devourable_mob_spr->top_left_position() +
                                                       bn::fixed_point(devourable_mob_spr->shape_size().width() / 2,
                                                                       devourable_mob_spr->shape_size().height() / 2);

            static constexpr bn::fixed_point POS_DIFF(0, 1);
            states.target_position = devourable_mob_pos + POS_DIFF;
            states.devour_critter = actors_of_interest->nearby_devourable_mob;
            actors_of_interest->status_mob = actors_of_interest->nearby_devourable_mob;
            states.input_action = critter_action::WANT_TO_DEVOUR;
            states.input_velocity = bn::fixed_point(0, 0);
            states.input_direction = direction::NONE;
        }
    }
}

} // namespace mc::gm::ecs::sys::impl
