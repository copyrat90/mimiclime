#include "gm/ecs/sys/critter_act.h"

#include "gm/cfg/critter_animation_infos.h"
#include "gm/cfg/species_infos.h"
#include "gm/cfg/sprite_datas.h"
#include "gm/ecs/sys/impl/critter_act_lizard.h"
#include "gm/ecs/sys/impl/critter_act_slime.h"
#include "gm/lerp.h"
#include "ut/enum_utils.h"

#include <bn_sprite_builder.h>

#include <type_traits>

namespace mc::gm::ecs::sys
{

namespace
{

constexpr decltype(cpn::critter_states::devour_countdown) WANT_TO_DEVOUR_COUNTDOWN = 60;
constexpr decltype(cpn::critter_states::devour_countdown) MOVE_TO_DEVOUR_COUNTDOWN = 60;
constexpr decltype(cpn::critter_states::devour_countdown) PRE_CHANGE_SPECIES_COUNTDOWN = 45;
constexpr decltype(cpn::critter_states::devour_countdown) POST_CHANGE_SPECIES_COUNTDOWN = 45;
constexpr decltype(cpn::critter_states::devour_countdown) DEVOUR_COOLDOWN = 60;

constexpr decltype(cpn::sprite_flicker::toggle_ticks) FLICKER_TOGGLE_TICKS = 3;

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

        if (states.alive())
        {
            if (states.attack_countdown > 0)
            {
                // Decrease attack cooldown after attack is done
                if (states.executing_action != critter_action::ATTACK)
                    --states.attack_countdown;
            }

            if (states.devour_countdown > 0)
            {
                // Update devour
                switch (states.executing_action)
                {
                case critter_action::WANT_TO_DEVOUR:
                    // Abort devour
                    if (states.input_action != critter_action::WANT_TO_DEVOUR)
                    {
                        states.executing_action = critter_action::NONE;
                        states.devour_countdown = 0;
                    }
                    // Start devour if held devour key long enough
                    else if (--states.devour_countdown == 0)
                    {
                        ++states.invincible_shared_counter;
                        states.executing_action = critter_action::MOVE_TO_DEVOUR;
                        states.devour_countdown = MOVE_TO_DEVOUR_COUNTDOWN;
                    }
                    break;

                case critter_action::MOVE_TO_DEVOUR:
                    if (--states.devour_countdown != 0)
                    {
                        // Move to target position gradually
                        static constexpr bn::fixed LERP_RATIO = 0.05f;

                        const auto* critter_sprite = actor_reg.try_get<bn::sprite_ptr>(critter);
                        BN_ASSERT(critter_sprite);
                        const auto critter_pos = critter_sprite->top_left_position() +
                                                 bn::fixed_point(critter_sprite->shape_size().width() / 2,
                                                                 critter_sprite->shape_size().height() / 2);

                        const auto lerped_pos = lerp(critter_pos, states.target_position, LERP_RATIO);
                        velocity->velocity = lerped_pos - critter_pos;

                        if (velocity->velocity != bn::fixed_point(0, 0))
                            states.facing_direction = to_direction_5(velocity->velocity, states.facing_direction);
                        else
                            goto PROGRESS_TO_PRE_CHANGE_SPECIES;
                    }
                    else
                    {
                    PROGRESS_TO_PRE_CHANGE_SPECIES:
                        velocity->velocity = bn::fixed_point(0, 0);

                        auto* devouring_critter_flicker = actor_reg.try_get<cpn::sprite_flicker>(critter);
                        if (devouring_critter_flicker)
                            *devouring_critter_flicker =
                                cpn::sprite_flicker(PRE_CHANGE_SPECIES_COUNTDOWN, FLICKER_TOGGLE_TICKS);
                        else
                            actor_reg.emplace<cpn::sprite_flicker>(critter, PRE_CHANGE_SPECIES_COUNTDOWN,
                                                                   FLICKER_TOGGLE_TICKS);

                        auto* devoured_critter_flicker = actor_reg.try_get<cpn::sprite_flicker>(states.devour_critter);
                        if (devoured_critter_flicker)
                            *devoured_critter_flicker =
                                cpn::sprite_flicker(PRE_CHANGE_SPECIES_COUNTDOWN, FLICKER_TOGGLE_TICKS);
                        else
                            actor_reg.emplace<cpn::sprite_flicker>(states.devour_critter, PRE_CHANGE_SPECIES_COUNTDOWN,
                                                                   FLICKER_TOGGLE_TICKS);

                        states.executing_action = critter_action::PRE_CHANGE_SPECIES;
                        states.devour_countdown = PRE_CHANGE_SPECIES_COUNTDOWN;
                    }
                    break;

                case critter_action::PRE_CHANGE_SPECIES:
                    if (--states.devour_countdown == 0)
                    {
                        auto* critter_sprite = actor_reg.try_get<bn::sprite_ptr>(critter);
                        BN_ASSERT(critter_sprite);
                        auto* critter_sprite_anim = actor_reg.try_get<cpn::sprite_animation>(critter);
                        BN_ASSERT(critter_sprite_anim);
                        auto camera = critter_sprite->camera();
                        BN_ASSERT(camera);
                        const auto critter_pos = critter_sprite->top_left_position() +
                                                 bn::fixed_point(critter_sprite->shape_size().width() / 2,
                                                                 critter_sprite->shape_size().height() / 2);

                        const auto* devour_critter_states =
                            actor_reg.try_get<cpn::critter_states>(states.devour_critter);
                        BN_ASSERT(devour_critter_states);
                        const auto devour_critter_species = devour_critter_states->species();

                        const auto& anim_infos = cfg::critter_animation_infos::get(devour_critter_species);
                        const auto spr_kind = mc::ut::enum_to_enum<cfg::gen::sprite_kind>(devour_critter_species);
                        const auto& spr_datas = cfg::sprite_datas::get(spr_kind);
                        const auto& spr_item = spr_datas.sprite_item();
                        const bn::fixed_point pos_diff(spr_item.shape_size().width() / 2,
                                                       spr_item.shape_size().height() / 2);
                        const auto& anim_info =
                            anim_infos.get_info(critter_animation_kind::DEAD, states.facing_direction);

                        // Change sprite & anim to new species
                        bn::sprite_builder spr_builder(spr_item, anim_info.graphics_indexes[0]);
                        spr_builder.set_top_left_position(critter_pos - pos_diff)
                            .set_horizontal_flip(anim_info.horizontal_flip)
                            .set_vertical_flip(anim_info.vertical_flip)
                            .set_blending_enabled(true)
                            .set_camera(*camera);
                        *critter_sprite = spr_builder.release_build();
                        critter_sprite_anim->reset(*critter_sprite, spr_kind, anim_info);

                        // Change critter states to new species
                        states.change_species(devour_critter_species);

                        // Remove devoured mob
                        actor_reg.destroy(states.devour_critter);
                        states.devour_critter = gba::entity_null;

                        auto* critter_flicker = actor_reg.try_get<cpn::sprite_flicker>(critter);
                        if (critter_flicker)
                            *critter_flicker = cpn::sprite_flicker(PRE_CHANGE_SPECIES_COUNTDOWN, FLICKER_TOGGLE_TICKS);
                        else
                            actor_reg.emplace<cpn::sprite_flicker>(critter, PRE_CHANGE_SPECIES_COUNTDOWN,
                                                                   FLICKER_TOGGLE_TICKS);

                        states.executing_action = critter_action::POST_CHANGE_SPECIES;
                        states.devour_countdown = POST_CHANGE_SPECIES_COUNTDOWN;
                    }
                    break;

                case critter_action::POST_CHANGE_SPECIES:
                    if (--states.devour_countdown == 0)
                    {
                        --states.invincible_shared_counter;
                        states.executing_action = critter_action::NONE;
                        states.devour_countdown = DEVOUR_COOLDOWN;
                    }
                    break;

                default:
                    // Decrease devour cooldown after devour is done
                    --states.devour_countdown;

                    goto INDIVIDUAL_CRITTER_ACTS;
                }
            }
            else
            {
                if (states.input_action == critter_action::WANT_TO_DEVOUR &&
                    states.executing_action != critter_action::WANT_TO_DEVOUR)
                {
                    states.executing_action = critter_action::WANT_TO_DEVOUR;
                    states.devour_countdown = WANT_TO_DEVOUR_COUNTDOWN;

                    if (states.input_direction != direction::NONE)
                        states.facing_direction = to_direction_5(states.input_direction, states.facing_direction);
                    velocity->velocity = states.input_velocity;
                }
                else
                {
                INDIVIDUAL_CRITTER_ACTS:
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
                }
            }
        }
        else // If not alive,
        {
            if (states.executing_action != critter_action::DEAD)
            {
                states.executing_action = critter_action::DEAD;
                velocity->velocity = bn::fixed_point(0, 0);
            }
        }

        auto* spr_anim = actor_reg.try_get<cpn::sprite_animation>(critter);
        BN_ASSERT(spr_anim);

        // Go back to no action if animation is done
        if (spr_anim->done())
            states.executing_action = critter_action::NONE;

        // Change character animation if needed
        static constexpr bn::fixed_point ZERO_VEC(0, 0);
        const auto anim_prev_action =
            (prev_action == critter_action::WANT_TO_DEVOUR || prev_action == critter_action::MOVE_TO_DEVOUR)
                ? critter_action::NONE
            : (prev_action == critter_action::PRE_CHANGE_SPECIES || prev_action == critter_action::POST_CHANGE_SPECIES)
                ? critter_action::DEAD
                : prev_action;
        const auto anim_exec_action = (states.executing_action == critter_action::WANT_TO_DEVOUR ||
                                       states.executing_action == critter_action::MOVE_TO_DEVOUR)
                                          ? critter_action::NONE
                                      : (states.executing_action == critter_action::PRE_CHANGE_SPECIES ||
                                         states.executing_action == critter_action::POST_CHANGE_SPECIES)
                                          ? critter_action::DEAD
                                          : states.executing_action;
        if (anim_exec_action != anim_prev_action || states.facing_direction != prev_direction ||
            (anim_exec_action == critter_action::NONE &&
             ((velocity->velocity == ZERO_VEC) != (prev_velocity == ZERO_VEC))))
        {
            critter_animation_kind anim_kind;

            if (anim_exec_action == critter_action::NONE)
                anim_kind =
                    (velocity->velocity == ZERO_VEC) ? critter_animation_kind::IDLE : critter_animation_kind::WALK;
            else
                anim_kind = ut::enum_to_enum<critter_animation_kind>(anim_exec_action);

            auto* spr = actor_reg.try_get<bn::sprite_ptr>(critter);
            BN_ASSERT(spr);

            const auto spr_kind = mc::ut::enum_to_enum<cfg::gen::sprite_kind>(states.species());
            const auto& anim_infos = cfg::critter_animation_infos::get(states.species());
            const auto& anim_info = anim_infos.get_info(anim_kind, states.facing_direction);

            spr_anim->reset(*spr, spr_kind, anim_info);
        }
    });
}

} // namespace mc::gm::ecs::sys
