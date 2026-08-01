#include "gm/ecs/sys/critter_act.h"

#include "gm/cfg/critter_animation_infos.h"
#include "gm/cfg/species_infos.h"
#include "gm/cfg/sprite_datas.h"
#include "gm/ecs/sys/impl/critter_act_lizard.h"
#include "gm/ecs/sys/impl/critter_act_slime.h"
#include "ut/enum_utils.h"

#include <type_traits>

namespace mc::gm::ecs::sys
{

namespace
{

static constexpr decltype(cpn::critter_states::devour_countdown) DEVOURING_COUNTDOWN = 60;
static constexpr decltype(cpn::critter_states::devour_countdown) CHANGING_SPECIES_COUNTDOWN = 60;

} // namespace

void critter_act(actor_registry& actor_reg)
{
    actor_reg.view<cpn::critter_states>().each([&](const gba::entity critter, cpn::critter_states& states) {
        auto* velocity = actor_reg.try_get<cpn::velocity>(critter);
        BN_ASSERT(velocity);

        // Store previous states
        const critter_action prev_action = states.executing_action;
        const direction prev_direction = states.facing_direction;
        const bn::fixed_point prev_velocity = velocity->velocity;

        // Apply species velocity multiplier
        const auto& infos = cfg::species_infos::get(states.species());
        states.input_velocity *= infos.speed();

        // Input validation / dismissal / preprocess

        if (states.attack_countdown > 0)
        {
            // Dismiss attack input on cooldown
            if (states.input_action == critter_action::ATTACK)
                states.input_action = critter_action::NONE;

            // Decrease attack cooldown after attack is done
            if (states.executing_action != critter_action::ATTACK)
                --states.attack_countdown;
        }

        // WIP
        if (states.devour_countdown > 0)
        {
            switch (states.executing_action)
            {
            case critter_action::DEVOUR:
                // Abort devour
                if (states.input_action != critter_action::DEVOUR)
                    states.devour_countdown = 0;
                // Start devouring if held devour key long enough
                else if (--states.devour_countdown == 0)
                {
                    // TODO: Should I set `executing_action` here?
                    // And don't call individual critter act functions?
                    states.input_action = critter_action::DEVOURING;
                    states.devour_countdown = DEVOURING_COUNTDOWN;
                }
                break;

            case critter_action::DEVOURING:
                if (--states.devour_countdown == 0)
                {
                    // TODO: Should I set `executing_action` here?
                    // And don't call individual critter act functions?
                    states.input_action = critter_action::CHANGING_SPECIES;
                    states.devour_countdown = CHANGING_SPECIES_COUNTDOWN;
                }
                break;

            case critter_action::CHANGING_SPECIES:
                // TODO
                break;

            default:
                // Dismiss devour input on cooldown
                if (states.input_action == critter_action::DEVOUR)
                    states.input_action = critter_action::NONE;

                // Decrease devour cooldown after devour is done
                --states.devour_countdown;
            }
        }

        // Call individual critter act functions.
        // These would see the input states, and apply those to current states, possibly with modifications.
        switch (states.species())
        {
            using species_kind = ldtk::gen::species_kind;

        case species_kind::slime:
            impl::critter_act_slime(critter, actor_reg);
            break;
        case species_kind::lizard:
            impl::critter_act_lizard(critter, actor_reg);
            break;

        default:
            BN_ERROR("Invalid species: ", static_cast<int>(states.species()));
        }

        auto* spr_anim = actor_reg.try_get<cpn::sprite_animation>(critter);
        BN_ASSERT(spr_anim);

        // Go back to no action if animation is done
        if (spr_anim->done())
            states.executing_action = critter_action::NONE;

        // Change character animation if needed
        static constexpr bn::fixed_point ZERO_VEC(0, 0);
        if (states.executing_action != prev_action || states.facing_direction != prev_direction ||
            (states.executing_action == critter_action::NONE &&
             ((velocity->velocity == ZERO_VEC) != (prev_velocity == ZERO_VEC))))
        {
            critter_animation_kind anim_kind;

            switch (states.executing_action)
            {
            case critter_action::NONE:
                anim_kind =
                    (velocity->velocity == ZERO_VEC) ? critter_animation_kind::IDLE : critter_animation_kind::WALK;
                break;

            case critter_action::ATTACK:
                anim_kind = critter_animation_kind::ATTACK;
                break;

            case critter_action::DEVOUR:           // TODO
            case critter_action::CHANGING_SPECIES: // TODO
            default:
                BN_ERROR("Invalid executing action: ", static_cast<int>(states.executing_action));
            };

            auto* spr = actor_reg.try_get<bn::sprite_ptr>(critter);
            BN_ASSERT(spr);

            const auto& spr_datas =
                cfg::sprite_datas::get(mc::ut::enum_to_enum<cfg::gen::sprite_kind>(states.species()));
            const auto& spr_item = spr_datas.sprite_item();

            const auto& anim_infos = cfg::critter_animation_infos::get(states.species());
            const auto& anim_info = anim_infos.get_info(anim_kind, states.facing_direction);

            spr_anim->reset(*spr, spr_item.tiles_item(), anim_info);
        }
    });
}

} // namespace mc::gm::ecs::sys
