
#include "gm/ecs/sys/impl/critter_input_mob_butterfly.h"

#include "gm/ecs/ut/find_entity.h"

#include <bn_sprite_shape_size.h>

namespace mc::gm::ecs::sys::impl
{

namespace
{

enum class attack_range_result_t
{
    VALID,
    TOO_FAR,
};

auto calc_attack_range(const bn::fixed_point& diff) -> attack_range_result_t
{
    static constexpr bn::fixed MAX_ATTACK_DIST = 8;
    static constexpr bn::fixed MAX_ATTACK_DIST_SQ = MAX_ATTACK_DIST * MAX_ATTACK_DIST;

    const bn::fixed distance_squared = diff.x() * diff.x() + diff.y() * diff.y();

    if (distance_squared > MAX_ATTACK_DIST_SQ)
        return attack_range_result_t::TOO_FAR;
    else
        return attack_range_result_t::VALID;
}

} // namespace

void critter_input_mob_butterfly(const gba::entity critter, actor_registry& actor_reg)
{
    auto& states = actor_reg.get<cpn::critter_states>(critter);
    auto& substates = states.substates<cpn::impl::critter_substates_butterfly>();

    switch (substates.strategy)
    {
        using strategy_t = cpn::impl::critter_substates_butterfly::strategy_t;

    case strategy_t::MOVE:
        if (auto* coll_events = actor_reg.try_get<cpn::collision_events>(critter); coll_events)
        {
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

            // Start attacking in a row if in the attack range, or bumped into wall
            if (coll_events->collided_wall ||
                (states.can_attack() && attack_range_result == attack_range_result_t::VALID))
            {
                substates.strategy = strategy_t::ATTACK;
            }
            // Too far away: approach to player
            else if (attack_range_result != attack_range_result_t::VALID)
            {
                states.input_direction = to_direction_9(diff);
                states.input_velocity = to_normal_vector(diff);
            }
        }
        break;

    case strategy_t::ATTACK:
        if (states.can_attack())
        {
            states.input_action = critter_action::ATTACK;

            substates.strategy = strategy_t::REST;
            substates.rest_ticks = 60;
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
