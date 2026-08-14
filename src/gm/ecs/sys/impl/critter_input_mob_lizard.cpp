#include "gm/ecs/sys/impl/critter_input_mob_lizard.h"

#include "gm/cfg/species_infos.h"
#include "gm/ecs/ut/find_critter.h"

#include <bn_sprite_shape_size.h>

namespace mc::gm::ecs::sys::impl
{

namespace
{

enum class attack_range_result_t
{
    VALID,
    TOO_FAR,
    TOO_CLOSE,
};

auto calc_attack_range(const bn::fixed_point& diff) -> attack_range_result_t
{
    static constexpr bn::fixed MIN_ATTACK_DIST = 85;
    static constexpr bn::fixed MAX_ATTACK_DIST = 120;
    static constexpr bn::fixed MIN_ATTACK_DIST_SQ = MIN_ATTACK_DIST * MIN_ATTACK_DIST;
    static constexpr bn::fixed MAX_ATTACK_DIST_SQ = MAX_ATTACK_DIST * MAX_ATTACK_DIST;

    const bn::fixed distance_squared = diff.x() * diff.x() + diff.y() * diff.y();

    if (distance_squared > MAX_ATTACK_DIST_SQ)
        return attack_range_result_t::TOO_FAR;
    else if (distance_squared < MIN_ATTACK_DIST_SQ)
        return attack_range_result_t::TOO_CLOSE;
    else
        return attack_range_result_t::VALID;
}

} // namespace

void critter_input_mob_lizard(const gba::entity critter, actor_registry& actor_reg)
{
    auto& states = actor_reg.get<cpn::critter_states>(critter);
    auto& substates = states.substates<cpn::impl::critter_substates_lizard>();

    // Can't do anything new while attacking
    if (states.executing_action == critter_action::ATTACK)
        return;

    switch (substates.strategy)
    {
        using strategy_t = cpn::impl::critter_substates_lizard::strategy_t;

    case strategy_t::MOVE: {
        auto* critter_spr = actor_reg.try_get<bn::sprite_ptr>(critter);
        BN_ASSERT(critter_spr);

        const gba::entity player = ut::find_player_critter(actor_reg);
        auto* player_spr = actor_reg.try_get<bn::sprite_ptr>(player);
        BN_ASSERT(player_spr);

        const bn::fixed_point critter_pos =
            critter_spr->top_left_position() +
            bn::fixed_point(critter_spr->shape_size().width() / 2, critter_spr->shape_size().height() / 2);
        const bn::fixed_point player_pos =
            player_spr->top_left_position() +
            bn::fixed_point(player_spr->shape_size().width() / 2, player_spr->shape_size().height() / 2);
        const bn::fixed_point diff = player_pos - critter_pos;

        const auto attack_range_result = calc_attack_range(diff);

        auto* coll_events = actor_reg.try_get<cpn::collision_events>(critter);
        BN_ASSERT(coll_events);

        // Start attacking in a row if in the attack range, or bumped into wall while running away
        if ((coll_events->collided_wall && attack_range_result == attack_range_result_t::TOO_CLOSE) ||
            (states.can_attack() && attack_range_result == attack_range_result_t::VALID))
        {
            substates.strategy = strategy_t::ATTACK_IN_A_ROW;
            substates.attack_direction = to_direction_5(diff, states.facing_direction);
            substates.remaining_attacks = 3;
        }
        // Too close: stayaway from player
        // Too far away: approach to player
        else if (attack_range_result != attack_range_result_t::VALID)
        {
            states.input_direction = to_direction_9(diff);
            states.input_velocity = to_normal_vector(diff);
            if (attack_range_result == attack_range_result_t::TOO_CLOSE)
                states.input_velocity = -states.input_velocity;
        }
    }
    break;

    case strategy_t::ATTACK_IN_A_ROW:
        // Reserve attack towards player when it can attack
        if (states.can_attack())
        {
            states.input_direction = substates.attack_direction;
            states.input_action = critter_action::ATTACK;

            if (substates.remaining_attacks == 0 || --substates.remaining_attacks == 0)
            {
                substates.strategy = strategy_t::REST;
                substates.rest_ticks = 90;
            }
        }
        break;

    case strategy_t::REST:
        if (substates.rest_ticks == 0 || --substates.rest_ticks == 0)
            substates.strategy = strategy_t::MOVE;
        break;

    default:
        BN_ERROR("Invalid strategy: ", static_cast<int>(substates.strategy));
    }
}

} // namespace mc::gm::ecs::sys::impl
