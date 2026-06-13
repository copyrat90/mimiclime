#pragma once

#include <bn_fixed_point.h>

#include "ldtk_gen_idents_fwd.h"
#include "ldtk_gen_iids_fwd.h"

namespace ldtk
{
class entity;
class entity_ref;
} // namespace ldtk

namespace mc::gm::cfg
{

struct room_entrance final
{
private:
    ldtk::gen::level_ident _room_id;
    ldtk::gen::entity_iid _entrance_id;

public:
    auto position() const -> bn::fixed_point;

public:
    auto room_id() const -> decltype(_room_id)
    {
        return _room_id;
    }

    auto entrance_id() const -> decltype(_entrance_id)
    {
        return _entrance_id;
    }

public:
    room_entrance(ldtk::gen::level_ident room_id, ldtk::gen::entity_iid entrance_id);
    explicit room_entrance(const ldtk::entity_ref& entrance_ref);

    static auto from_exit(const ldtk::entity& exit_entity) -> room_entrance;
};

} // namespace mc::gm::cfg
