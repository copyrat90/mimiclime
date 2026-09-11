#include "gm/ecs/sys/room_change.h"

#include "gm/ecs/cpn/room_change_states.h"
#include "gm/ecs/ut/breakable_factories.h"
#include "gm/ecs/ut/critter_factories.h"
#include "gm/ecs/ut/interactable_factories.h"
#include "gm/ecs/ut/openable_factories.h"
#include "gm/ecs/ut/sign_factories.h"
#include "gm/ecs/ut/triggerable_factories.h"
#include "gm/game_save.h"

#include "ibn_transitions.h"

#include "ldtk_level.h"

#include <bn_display.h>
#include <bn_sprite_shape_size.h>

#include "ldtk_gen_idents.h"

namespace mc::gm::ecs::sys
{

namespace
{

constexpr auto TRANSITION_KINDS = ibn::transitions::kinds::FADE | ibn::transitions::kinds::SPRITES_MOSAIC_VERTICAL |
                                  ibn::transitions::kinds::BGS_MOSAIC_VERTICAL;
constexpr std::int8_t TRANSITION_DURATION = 30;

constexpr bn::fixed_point CAMERA_CENTER_OFFSET(-bn::display::width() / 2, -bn::display::height() / 2);

} // namespace

void room_change(singleton_registry& singleton_reg, const gba::entity singleton_entity, ibn::transitions& transitions,
                 actor_registry& actor_reg, const game_save& save)
{
    auto* room_change_states = singleton_reg.try_get<cpn::room_change_states>(singleton_entity);

    if (room_change_states)
    {
        switch (room_change_states->fade)
        {
            using fade_state = cpn::room_change_states::fade_state;

        case fade_state::INIT:
            if (--room_change_states->countdown <= 0)
            {
                transitions.set_alpha(TRANSITION_KINDS, 0);
                transitions.start(TRANSITION_KINDS, TRANSITION_DURATION, 1);

                room_change_states->fade = fade_state::FADING_OUT;
                room_change_states->countdown = TRANSITION_DURATION;
            }
            break;

        case fade_state::FADING_OUT:
            if (--room_change_states->countdown <= 0)
            {
                transitions.set_alpha(TRANSITION_KINDS, 1);
                transitions.start(TRANSITION_KINDS, TRANSITION_DURATION, 0);

                auto* room = singleton_reg.try_get<cpn::room>(singleton_entity);
                BN_ASSERT(room);
                room->reset(room_change_states->entrance.room_id());
                room->level_bgs().set_visible(true);

                const bn::fixed_point entrance_position = room_change_states->entrance.position();

                // Reset camera to entrance position
                auto* camera = singleton_reg.try_get<bn::camera_ptr>(singleton_entity);
                BN_ASSERT(camera);
                camera->set_position(entrance_position + CAMERA_CENTER_OFFSET);

                if (room_change_states->reload_player)
                {
                    // Remove all entities including player
                    actor_reg.clear();

                    // Re-create player as recently saved species
                    ut::create_player_critter(save.player_species, entrance_position, actor_reg, singleton_reg,
                                              singleton_entity);
                }
                else
                {
                    actor_reg.view<cpn::critter_states>().each(
                        [&](const gba::entity critter, cpn::critter_states& critter_states) {
                            // For the player,
                            if (critter_states.is_player())
                            {
                                // Reset directions
                                critter_states.input_direction = direction::NONE;

                                // Move the player to the entrance position
                                auto* spr = actor_reg.try_get<bn::sprite_ptr>(critter);
                                BN_ASSERT(spr);

                                const bn::fixed_point moved_pos =
                                    entrance_position -
                                    bn::fixed_point(spr->shape_size().width() / 2, spr->shape_size().height() / 2);
                                spr->set_top_left_position(moved_pos);
                            }
                            // Remove all critters that are not the player
                            else
                                actor_reg.destroy(critter);
                        });

                    // Remove all entities that are not the player
                    actor_reg.view<gba::ecs::exclude<cpn::critter_states>>().each(
                        [&](const gba::entity entity) { actor_reg.destroy(entity); });
                }

                // Load entities
                const ldtk::layer& entities_layer = room->level().get_layer(ldtk::gen::layer_ident::entities);
                for (const ldtk::entity& entity : entities_layer.entity_instances())
                {
                    switch (entity.identifier())
                    {
                        using entity_ident = ldtk::gen::entity_ident;

                    case entity_ident::mob: {
                        ldtk::gen::species_kind species =
                            entity.get_field(ldtk::gen::entity_field_ident::ENTITY_mob_FIELD_species)
                                .get<ldtk::gen::species_kind>();

                        ut::create_mob_critter(species, entity.px(), actor_reg, singleton_reg, singleton_entity);
                    }
                    break;

                    case entity_ident::breakable: {
                        const bn::optional<ldtk::gen::game_flag> broken_flag =
                            entity.get_field(ldtk::gen::entity_field_ident::ENTITY_breakable_FIELD_broken).has_value()
                                ? bn::optional(
                                      entity.get_field(ldtk::gen::entity_field_ident::ENTITY_breakable_FIELD_broken)
                                          .get<ldtk::gen::game_flag>())
                                : bn::nullopt;
                        const bool broken = broken_flag.has_value() ? save.game_flag(*broken_flag) : false;

                        if (!broken)
                        {
                            const ldtk::gen::breakable_kind kind =
                                entity.get_field(ldtk::gen::entity_field_ident::ENTITY_breakable_FIELD_kind)
                                    .get<ldtk::gen::breakable_kind>();

                            ut::create_breakable(kind, broken_flag, entity.px(), actor_reg, singleton_reg,
                                                 singleton_entity);
                        }
                    }
                    break;

                    case entity_ident::save_point: {
                        const auto entrance = cfg::room_entrance(
                            entity.get_field(ldtk::gen::entity_field_ident::ENTITY_save_point_FIELD_spawn_point)
                                .get<ldtk::entity_ref>());

                        ut::create_save_point(entity.px(), entrance, actor_reg, singleton_reg, singleton_entity);
                    }
                    break;

                    case entity_ident::sign: {
                        const auto descriptions =
                            entity.get_field(ldtk::gen::entity_field_ident::ENTITY_sign_FIELD_descriptions)
                                .get<bn::span<const bn::string_view>>();

                        ut::create_sign(entity.px(), descriptions, actor_reg, singleton_reg, singleton_entity);
                    }
                    break;

                    case entity_ident::triggerable: {
                        const ldtk::gen::triggerable_kind kind =
                            entity.get_field(ldtk::gen::entity_field_ident::ENTITY_triggerable_FIELD_kind)
                                .get<ldtk::gen::triggerable_kind>();
                        const ldtk::gen::game_flag triggered =
                            entity.get_field(ldtk::gen::entity_field_ident::ENTITY_triggerable_FIELD_triggered)
                                .get<ldtk::gen::game_flag>();

                        ut::create_triggerable(kind, triggered, entity.px(), actor_reg, singleton_reg, singleton_entity,
                                               save);
                    }
                    break;

                    case entity_ident::openable: {
                        const ldtk::gen::openable_kind kind =
                            entity.get_field(ldtk::gen::entity_field_ident::ENTITY_openable_FIELD_kind)
                                .get<ldtk::gen::openable_kind>();
                        const ldtk::gen::game_flag opened =
                            entity.get_field(ldtk::gen::entity_field_ident::ENTITY_openable_FIELD_opened)
                                .get<ldtk::gen::game_flag>();

                        ut::create_openable(kind, opened, entity.px(), actor_reg, singleton_reg, singleton_entity,
                                            save);
                    }
                    break;

                    default:
                        break;
                    }
                }

                room_change_states->fade = fade_state::FADING_IN;
                room_change_states->countdown = TRANSITION_DURATION;
            }
            break;

        case fade_state::FADING_IN:
            if (--room_change_states->countdown <= 0)
            {
                transitions.set_alpha(TRANSITION_KINDS, 0);
                transitions.clear(TRANSITION_KINDS);

                singleton_reg.remove_unchecked(*room_change_states);
            }
            break;

        default:
            BN_ERROR("Invalid fade_state: ", static_cast<int>(room_change_states->fade));
        }
    }
}

} // namespace mc::gm::ecs::sys
