#include "gm/ecs/sys/impl/critter_input_mob_lizard.h"

#include "gm/cfg/species_infos.h"
#include "gm/ecs/ut/find_critter.h"

namespace mc::gm::ecs::sys::impl
{

void critter_input_mob_lizard(const gba::entity critter, actor_registry& actor_reg)
{
    auto& states = actor_reg.get<cpn::critter_states>(critter);
    [[maybe_unused]] auto& substates = states.substates<cpn::impl::critter_substates_lizard>();

    switch (states.executing_action)
    {
    case critter_action::ATTACK:
        // Can't do anything new while attacking
        break;

    case critter_action::NONE: {
        auto* chara_proxy = actor_reg.try_get<cpn::character_proxy>(critter);
        BN_ASSERT(chara_proxy);

        const gba::entity player = ut::find_player_critter(actor_reg);
        auto* player_chara_proxy = actor_reg.try_get<cpn::character_proxy>(player);
        BN_ASSERT(player_chara_proxy);

        const bn::fixed_point& critter_pos = chara_proxy->character().position();
        const bn::fixed_point& player_pos = player_chara_proxy->character().position();
        const bn::fixed_point diff = player_pos - critter_pos;

        auto* coll_events = actor_reg.try_get<cpn::collision_events>(critter);
        BN_ASSERT(coll_events);

        auto attack = [&] {
            // Skip if already attacking, or in attack cooldown
            if (states.executing_action == critter_action::ATTACK || states.attack_countdown > 0)
                return;

            // Reserve stop moving
            states.input_velocity = bn::fixed_point(0, 0);

            // Reserve attack towards player
            states.input_direction = to_direction_5(diff, states.facing_direction);
            states.input_action = critter_action::ATTACK;
        };

        // Attack when bumped into walls
        if (coll_events->collided_wall)
            attack();
        else
        {
            static constexpr bn::fixed MIN_ATTACK_DIST = 85;
            static constexpr bn::fixed MAX_ATTACK_DIST = 120;
            static constexpr bn::fixed MIN_ATTACK_DIST_SQ = MIN_ATTACK_DIST * MIN_ATTACK_DIST;
            static constexpr bn::fixed MAX_ATTACK_DIST_SQ = MAX_ATTACK_DIST * MAX_ATTACK_DIST;

            const bn::fixed distance_squared = diff.x() * diff.x() + diff.y() * diff.y();

            // Too close: stayaway from player
            // Too far away: approach to player
            if (distance_squared < MIN_ATTACK_DIST_SQ || distance_squared > MAX_ATTACK_DIST_SQ)
            {
                states.input_direction = to_direction_9(diff);
                states.input_velocity = to_normal_vector(diff);
                if (distance_squared < MIN_ATTACK_DIST_SQ)
                    states.input_velocity = -states.input_velocity;
            }
            else // Attack on in-between distances
                attack();
        }
    }
    break;

    default:
        BN_ERROR("Invalid mob critter action: ", static_cast<int>(states.executing_action));
        break;
    }
}

} // namespace mc::gm::ecs::sys::impl
