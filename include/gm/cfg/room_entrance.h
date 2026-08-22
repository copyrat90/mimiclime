#pragma once

#include <bn_fixed_point.h>

#include <cstdint>

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
    std::uint8_t _entrance_index;

public:
    auto position() const -> bn::fixed_point;

public:
    auto room_id() const -> decltype(_room_id)
    {
        return _room_id;
    }

    auto entrance_index() const -> decltype(_entrance_index)
    {
        return _entrance_index;
    }

public:
    room_entrance(ldtk::gen::level_ident room_id, std::uint8_t entrance_index);
    room_entrance(ldtk::gen::level_ident room_id, ldtk::gen::entity_iid entrance_id);
    explicit room_entrance(const ldtk::entity_ref& entrance_ref);

    static auto from_exit(const ldtk::entity& exit_entity) -> room_entrance;

    static auto get_beginning_entrance() -> room_entrance;
};

} // namespace mc::gm::cfg
