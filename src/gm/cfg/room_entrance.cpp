#include "gm/cfg/room_entrance.h"

#include "ldtk_entity.h"
#include "ldtk_entity_ref.h"

#include "ldtk_gen_idents.h"
#include "ldtk_gen_project.h"

namespace mc::gm::cfg
{

auto room_entrance::position() const -> bn::fixed_point
{
    const ldtk::entity& entrance_entity = ldtk::gen::gen_project.get_level(_room_id)
                                              .get_layer(ldtk::gen::layer_ident::entrances)
                                              .find_entity(_entrance_id);

    return {entrance_entity.px().x(), entrance_entity.px().y()};
}

room_entrance::room_entrance(ldtk::gen::level_ident room_id, ldtk::gen::entity_iid entrance_id)
    : _room_id(room_id), _entrance_id(entrance_id)
{
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

} // namespace mc::gm::cfg
