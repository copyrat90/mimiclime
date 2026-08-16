#include "gm/ecs/ut/find_critter.h"

#include <limits>

namespace mc::gm::ecs::ut
{

auto find_player_critter(actor_registry& actor_reg) -> const gba::entity
{
    gba::entity player_critter;

    actor_reg.view<cpn::critter_states>().each(
        [&player_critter](const gba::entity entity, const cpn::critter_states& states) {
            if (states.is_player())
                player_critter = entity;
        });

    return player_critter;
}

auto find_nearby_dead_critter(const gba::entity entity, actor_registry& actor_reg) -> const gba::entity
{
    static constexpr bn::fixed NEAR_LIMIT = 25;
    static constexpr bn::fixed NEAR_LIMIT_SQ = NEAR_LIMIT * NEAR_LIMIT;
    static constexpr bn::fixed MAX_DIST_SQ = bn::fixed::from_data(std::numeric_limits<int>::max());

    gba::entity near_critter;
    bn::fixed near_dist_sq = MAX_DIST_SQ;

    auto* entity_spr = actor_reg.try_get<bn::sprite_ptr>(entity);
    BN_ASSERT(entity_spr);

    actor_reg.view<cpn::critter_states, bn::sprite_ptr>().each(
        [&](const gba::entity critter, cpn::critter_states& critter_states, bn::sprite_ptr& critter_spr) {
            if (critter_states.alive() || entity == critter)
                return;

            const auto dx = entity_spr->x() - critter_spr.x();
            const auto dy = entity_spr->y() - critter_spr.y();
            const auto dist_sq = dx * dx + dy * dy;

            if (dist_sq <= NEAR_LIMIT_SQ && dist_sq < near_dist_sq)
            {
                near_critter = critter;
                near_dist_sq = dist_sq;
            }
        });

    return near_critter;
}

} // namespace mc::gm::ecs::ut
