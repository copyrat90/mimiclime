#include "gm/ecs/sys/room_change.h"

#include "gm/ecs/cpn/room_change_states.h"

#include "ibn_transitions.h"

namespace mc::gm::ecs::sys
{

namespace
{

constexpr auto TRANSITION_KINDS = ibn::transitions::kinds::FADE | ibn::transitions::kinds::SPRITES_MOSAIC_VERTICAL |
                                  ibn::transitions::kinds::BGS_MOSAIC_VERTICAL;
constexpr std::int8_t TRANSITION_DURATION = 30;

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

                actor_reg.view<cpn::character_proxy>().each(
                    [&](const gba::entity entity, cpn::character_proxy& chara_proxy) {
                        // Move the player to the entrance position
                        if (actor_reg.all_of<cpn::player_character_controller>(entity))
                            chara_proxy.character().set_top_left_position(room_change_states->entrance.position());
                        // Remove character entity if it's not the player
                        else
                            actor_reg.destroy(entity);
                    });

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
