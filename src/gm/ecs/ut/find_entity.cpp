#include "gm/ecs/ut/find_entity.h"

#include <limits>

namespace mc::gm::ecs::ut
{

namespace
{

constexpr bn::fixed NEAR_LIMIT = 25;
constexpr bn::fixed NEAR_LIMIT_SQ = NEAR_LIMIT * NEAR_LIMIT;
constexpr bn::fixed MAX_DIST_SQ = bn::fixed::from_data(std::numeric_limits<int>::max());

} // namespace

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

auto find_nearby_interactable(const gba::entity critter, actor_registry& actor_reg) -> const gba::entity
{
    gba::entity near_interactable;
    bn::fixed near_dist_sq = MAX_DIST_SQ;

    auto* critter_spr = actor_reg.try_get<bn::sprite_ptr>(critter);
    BN_ASSERT(critter_spr);
    auto* critter_states = actor_reg.try_get<cpn::critter_states>(critter);
    BN_ASSERT(critter_states);

    if (critter_states->alive())
    {
        actor_reg.view<cpn::interactable_states, bn::sprite_ptr>().each(
            [&](const gba::entity interactable, cpn::interactable_states& interactable_states,
                bn::sprite_ptr& interactable_spr) {
                if (critter == interactable)
                    return;
                if (interactable_states.kind == interactable_kind::devourable_mob)
                {
                    if (!critter_states->can_devour())
                        return;
                }
                else
                {
                    if (!critter_states->can_interact())
                        return;
                }

                const auto dx = critter_spr->x() - interactable_spr.x();
                const auto dy = critter_spr->y() - interactable_spr.y();
                const auto dist_sq = dx * dx + dy * dy;

                if (dist_sq <= NEAR_LIMIT_SQ && dist_sq < near_dist_sq)
                {
                    near_interactable = interactable;
                    near_dist_sq = dist_sq;
                }
            });
    }

    return near_interactable;
}

auto find_nearby_sign(const gba::entity critter, actor_registry& actor_reg) -> const gba::entity
{
    gba::entity near_sign;
    bn::fixed near_dist_sq = MAX_DIST_SQ;

    auto* critter_spr = actor_reg.try_get<bn::sprite_ptr>(critter);
    BN_ASSERT(critter_spr);
    auto* critter_states = actor_reg.try_get<cpn::critter_states>(critter);
    BN_ASSERT(critter_states);

    if (critter_states->alive())
    {
        actor_reg.view<cpn::sign_states, bn::sprite_ptr>().each(
            [&](const gba::entity sign, cpn::sign_states&, bn::sprite_ptr& sign_spr) {
                if (critter == sign)
                    return;

                const auto dx = critter_spr->x() - sign_spr.x();
                const auto dy = critter_spr->y() - sign_spr.y();
                const auto dist_sq = dx * dx + dy * dy;

                if (dist_sq <= NEAR_LIMIT_SQ && dist_sq < near_dist_sq)
                {
                    near_sign = sign;
                    near_dist_sq = dist_sq;
                }
            });
    }

    return near_sign;
}

} // namespace mc::gm::ecs::ut
