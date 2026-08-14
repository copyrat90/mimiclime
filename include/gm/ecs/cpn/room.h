#pragma once

#include "gm/cfg/room_entrance.h"

#include "ldtk_level_bgs_ptr.h"

#include <bn_optional.h>
#include <bn_top_left_fixed_rect.h>

#include <cstdint>

#include "ldtk_gen_idents_fwd.h"

namespace ldtk
{
class level;
class int_grid_base;
} // namespace ldtk

namespace bn
{
class camera_ptr;
}

namespace mc::gm::ecs::cpn
{

struct room final
{
private:
    const ldtk::level* _level;
    const ldtk::int_grid_base* _terrain;
    std::uint8_t _terrain_int_grid_size;

    ldtk::level_bgs_ptr _level_bgs;

public:
    int get_terrain_cell(const bn::fixed_point& position) const;

    auto dimensions() const -> bn::fixed_point;

    bool collide_with_wall(const bn::fixed_point& position) const;
    auto collide_with_exit(const bn::top_left_fixed_rect& collision) const -> bn::optional<cfg::room_entrance>;

public:
    auto level() const -> decltype(*_level)
    {
        return *_level;
    }

    auto terrain() const -> decltype(*_terrain)
    {
        return *_terrain;
    }

    auto terrain_int_grid_size() const -> decltype(_terrain_int_grid_size)
    {
        return _terrain_int_grid_size;
    }

    auto level_bgs() -> decltype((_level_bgs))
    {
        return _level_bgs;
    }

    auto level_bgs() const -> decltype((_level_bgs))
    {
        return _level_bgs;
    }

public:
    room(ldtk::gen::level_ident, const bn::camera_ptr&);

    room(const room&) = delete;
    room& operator=(const room&) = delete;

    void reset(ldtk::gen::level_ident);
};

} // namespace mc::gm::ecs::cpn
