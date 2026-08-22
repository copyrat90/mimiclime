#include "gm/cfg/room_entrance.h"

#include "ut/configs.h"

#include "ldtk_entity.h"
#include "ldtk_entity_ref.h"

#include <bn_log.h>

#include <algorithm>

#include "ldtk_gen_idents.h"
#include "ldtk_gen_project.h"

namespace mc::gm::cfg
{

auto room_entrance::position() const -> bn::fixed_point
{
    const auto& entrances =
        ldtk::gen::gen_project.get_level(_room_id).get_layer(ldtk::gen::layer_ident::entrances).entity_instances();

    BN_ASSERT(_entrance_index < entrances.size(), "Invalid entrance index: ", static_cast<int>(_entrance_index),
              " for room id: ", static_cast<int>(_room_id));

    const ldtk::entity& entrance_entity = *(entrances.data() + _entrance_index);

    return {entrance_entity.px().x(), entrance_entity.px().y()};
}

room_entrance::room_entrance(ldtk::gen::level_ident room_id, std::uint8_t entrance_index)
    : _room_id(room_id), _entrance_index(entrance_index)
{
    const auto& entrances =
        ldtk::gen::gen_project.get_level(_room_id).get_layer(ldtk::gen::layer_ident::entrances).entity_instances();

    // Fallback to valid entrance if it isn't valid
    if (entrance_index >= entrances.size())
    {
        if (entrances.empty())
        {
            BN_LOG("room_id=", static_cast<int>(room_id), ", entrance_index=", static_cast<int>(entrance_index),
                   " OOB, fallback to beginning entrance");
            *this = get_beginning_entrance();
        }
        else
        {
            BN_LOG("room_id=", static_cast<int>(room_id), ", entrance_index=", static_cast<int>(entrance_index),
                   " OOB, fallback to idx=0");
            _entrance_index = 0;
        }
    }
}

room_entrance::room_entrance(ldtk::gen::level_ident room_id, ldtk::gen::entity_iid entrance_id) : _room_id(room_id)
{
    const auto& entrances =
        ldtk::gen::gen_project.get_level(_room_id).get_layer(ldtk::gen::layer_ident::entrances).entity_instances();

    auto iter = std::ranges::find_if(entrances,
                                     [entrance_id](const ldtk::entity& entity) { return entity.iid() == entrance_id; });

    // Fallback to valid entrance if it isn't valid
    if (iter == entrances.cend())
    {
        if (entrances.empty())
        {
            BN_LOG("room_id=", static_cast<int>(room_id), ", entrance_id=", static_cast<int>(entrance_id),
                   " not found, fallback to beginning entrance");
            *this = get_beginning_entrance();
        }
        else
        {
            BN_LOG("room_id=", static_cast<int>(room_id), ", entrance_id=", static_cast<int>(entrance_id),
                   " not found, fallback to idx=0");
            _entrance_index = 0;
        }
    }
    else
    {
        _entrance_index = static_cast<std::uint8_t>(iter - entrances.begin());
    }
}

room_entrance::room_entrance(const ldtk::entity_ref& entrance_ref)
    : room_entrance(entrance_ref.level_ident(), entrance_ref.entity_iid())
{
}

auto room_entrance::from_exit(const ldtk::entity& exit_entity) -> room_entrance
{
    BN_ASSERT(exit_entity.identifier() == ldtk::gen::entity_ident::exit, "entity is not exit");

    const ldtk::entity_ref entrance_ref =
        exit_entity.get_field(ldtk::gen::entity_field_ident::ENTITY_exit_FIELD_destination).get<ldtk::entity_ref>();

    return room_entrance(entrance_ref);
}

auto room_entrance::get_beginning_entrance() -> gm::cfg::room_entrance
{
    static constexpr const ldtk::entity& GAME_BEGINNING_EXIT =
        ut::get_config_entity(ldtk::gen::entity_ident::exit, ldtk::gen::layer_ident::exits);

    return gm::cfg::room_entrance::from_exit(GAME_BEGINNING_EXIT);
}

} // namespace mc::gm::cfg
