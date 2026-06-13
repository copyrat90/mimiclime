#include "gm/ecs/cpn/room.h"

#include "ldtk_int_grid_empty_t.h"
#include "ldtk_int_grid_t.h"
#include "ldtk_level.h"
#include "ldtk_level_bgs_builder.h"

#include <utility>

#include "ldtk_gen_idents.h"
#include "ldtk_gen_project.h"

namespace mc::gm::ecs::cpn
{

namespace
{

constexpr const ldtk::layer_definition& TERRAIN_LAYER_DEF =
    ldtk::gen::gen_project.defs().get_layer_def(ldtk::gen::layer_ident::terrain);
constexpr int TERRAIN_GRID_SIZE = TERRAIN_LAYER_DEF.grid_size();

auto init_level_bgs_builder(const ldtk::level& level, const bn::camera_ptr& camera) -> ldtk::level_bgs_builder
{
    return ldtk::level_bgs_builder(level)
        .set_top_left_position(0, 0)
        .set_blending_top_enabled(true)
        .set_mosaic_enabled(true)
        .set_camera(camera);
}

auto get_terrain_int_grid_size(const ldtk::int_grid_base& terrain) -> std::uint8_t
{
    return static_cast<std::uint8_t>(terrain.cell_storage_size());
}

} // namespace

int room::get_terrain_cell(const bn::fixed_point& position) const
{
    if (position.x() < 0 || position.y() < 0)
        return -1;

    const bn::fixed_point dims = dimensions();
    if (position.x() >= dims.x() || position.y() >= dims.y())
        return -1;

    const bn::point grid_pos((position.x() / TERRAIN_GRID_SIZE).floor_integer(),
                             (position.y() / TERRAIN_GRID_SIZE).floor_integer());

    switch (_terrain_int_grid_size)
    {
    case 0:
        return static_cast<const ldtk::int_grid_empty_t*>(_terrain)->cell_int_no_virtual(grid_pos.x(), grid_pos.y());
    case 1:
        return static_cast<const ldtk::int_grid_t<std::uint8_t>*>(_terrain)->cell_int_no_virtual(grid_pos.x(),
                                                                                                 grid_pos.y());
    case 2:
        return static_cast<const ldtk::int_grid_t<std::uint16_t>*>(_terrain)->cell_int_no_virtual(grid_pos.x(),
                                                                                                  grid_pos.y());
    case 4:
        return static_cast<const ldtk::int_grid_t<std::uint32_t>*>(_terrain)->cell_int_no_virtual(grid_pos.x(),
                                                                                                  grid_pos.y());
    default:
        BN_ERROR("Invalid terrain int grid size: ", (int)_terrain_int_grid_size);
    }

    std::unreachable();
}

auto room::dimensions() const -> bn::fixed_point
{
    const bn::size dimensions = _level_bgs.dimensions();

    return {dimensions.width(), dimensions.height()};
}

room::room(ldtk::gen::level_ident level_id, const bn::camera_ptr& camera)
    : _level(&ldtk::gen::gen_project.get_level(level_id)),
      _terrain(_level->get_layer(ldtk::gen::layer_ident::terrain).int_grid()),
      _terrain_int_grid_size(get_terrain_int_grid_size(*_terrain)),
      _level_bgs(init_level_bgs_builder(*_level, camera).release_build())
{
}

void room::reset(ldtk::gen::level_ident level_id)
{
    _level = &ldtk::gen::gen_project.get_level(level_id);
    _terrain = _level->get_layer(ldtk::gen::layer_ident::terrain).int_grid();
    _terrain_int_grid_size = get_terrain_int_grid_size(*_terrain);

    const bn::optional<bn::camera_ptr>& camera = _level_bgs.camera();
    BN_ASSERT(camera.has_value(), "Camera is not attached to level_bgs");
    _level_bgs.set_level(init_level_bgs_builder(*_level, camera.value()));
}

} // namespace mc::gm::ecs::cpn
