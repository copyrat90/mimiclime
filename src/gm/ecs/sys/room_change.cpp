#include "gm/ecs/sys/room_change.h"

#include "gm/ecs/cpn/room_change_states.h"
#include "gm/ecs/ut/breakable_factories.h"
#include "gm/ecs/ut/critter_factories.h"

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
                 actor_registry& actor_reg)
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

                const bn::fixed_point entrance_position = room_change_states->entrance.position();

                actor_reg.view<cpn::critter_states>().each([&](const gba::entity entity, cpn::critter_states& states) {
                    if (states.is_player())
                    {
                        // Reset directions
                        states.input_direction = direction::NONE;

                        // Move the player to the entrance position
                        auto* spr = actor_reg.try_get<bn::sprite_ptr>(entity);
                        BN_ASSERT(spr);

                        const bn::fixed_point moved_pos =
                            entrance_position -
                            bn::fixed_point(spr->shape_size().width() / 2, spr->shape_size().height() / 2);
                        spr->set_top_left_position(moved_pos);
                    }
                    // Remove character entity if it's not the player
                    else
                        actor_reg.destroy(entity);
                });

                // Reset camera to entrance position
                auto* camera = singleton_reg.try_get<bn::camera_ptr>(singleton_entity);
                BN_ASSERT(camera);
                camera->set_position(entrance_position + CAMERA_CENTER_OFFSET);

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
                        const ldtk::gen::breakable_kind kind =
                            entity.get_field(ldtk::gen::entity_field_ident::ENTITY_breakable_FIELD_kind)
                                .get<ldtk::gen::breakable_kind>();

                        ut::create_breakable(kind, entity.px(), actor_reg, singleton_reg, singleton_entity);
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
