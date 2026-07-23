#include "ctrl/projectile_edit.h"

#include "model/resources.h"
#include "util/enum_utils.h"

#include <format>
#include <sstream>
#include <stdexcept>

namespace mcedit::ctrl
{

projectile_edit::projectile_edit(const std::filesystem::path& image_path, unsigned frame_index,
                                 unsigned projectile_index, const model::projectile& old_projectile,
                                 const model::projectile& new_projectile)
    : _image_path(image_path), _frame_index(frame_index), _projectile_index(projectile_index),
      _old_projectile(old_projectile), _new_projectile(new_projectile)
{
}

void projectile_edit::apply(model::resources& resources)
{
    projectile_ref(resources) = _new_projectile;
}

void projectile_edit::undo(model::resources& resources)
{
    projectile_ref(resources) = _old_projectile;
}

auto projectile_edit::undo_message() const -> std::string
{
    std::ostringstream oss;
    message_header(oss);

    if (_old_projectile.kind != _new_projectile.kind)
        oss << "Kind: " << util::enum_to_sv(_new_projectile.kind) << " -> " << util::enum_to_sv(_old_projectile.kind)
            << "\n";

    if (_old_projectile.x != _new_projectile.x || _old_projectile.y != _new_projectile.y)
        oss << "Pos: (" << +_new_projectile.x << ", " << +_new_projectile.y << ") -> (" << +_old_projectile.x << ", "
            << +_old_projectile.y << ")\n";

    if (_old_projectile.direction != _new_projectile.direction)
        oss << "Dir: " << util::enum_to_sv(_new_projectile.direction) << " -> "
            << util::enum_to_sv(_old_projectile.direction) << "\n";

    if (_old_projectile.speed != _new_projectile.speed)
        oss << "Speed: " << +_new_projectile.speed << " -> " << +_old_projectile.speed << "\n";

    return oss.str();
}

auto projectile_edit::redo_message() const -> std::string
{
    std::ostringstream oss;
    message_header(oss);

    if (_old_projectile.kind != _new_projectile.kind)
        oss << "Kind: " << util::enum_to_sv(_old_projectile.kind) << " -> " << util::enum_to_sv(_new_projectile.kind)
            << "\n";

    if (_old_projectile.x != _new_projectile.x || _old_projectile.y != _new_projectile.y)
        oss << "Pos: (" << +_old_projectile.x << ", " << +_old_projectile.y << ") -> (" << +_new_projectile.x << ", "
            << +_new_projectile.y << ")\n";

    if (_old_projectile.direction != _new_projectile.direction)
        oss << "Dir: " << util::enum_to_sv(_old_projectile.direction) << " -> "
            << util::enum_to_sv(_new_projectile.direction) << "\n";

    if (_old_projectile.speed != _new_projectile.speed)
        oss << "Speed: " << +_old_projectile.speed << " -> " << +_new_projectile.speed << "\n";

    return oss.str();
}

auto projectile_edit::projectile_ref(model::resources& resources) const -> model::projectile&
{
    auto iter = resources.sprite_sheets.find(_image_path);
    if (iter == resources.sprite_sheets.end())
        throw std::logic_error(std::format("Sprite '{}' not found!", _image_path.stem()));

    model::sprite_sheet& sprite_sheet = iter->second;
    sprite_sheet.has_changes = true;

    model::sprite_frame& sprite_frame = sprite_sheet.frames[_frame_index];
    return sprite_frame.projectiles[_projectile_index];
}

void projectile_edit::message_header(std::ostringstream& oss) const
{
    oss << _image_path.stem() << " #" << _frame_index << ", PROJECTILE #" << _projectile_index << "\n";
}

} // namespace mcedit::ctrl
