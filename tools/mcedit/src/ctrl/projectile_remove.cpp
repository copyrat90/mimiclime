#include "ctrl/projectile_remove.h"

#include "model/resources.h"
#include "util/enum_utils.h"

#include <format>
#include <limits>
#include <stdexcept>

namespace mcedit::ctrl
{

projectile_remove::projectile_remove(const std::filesystem::path& image_path, unsigned frame_index,
                                     unsigned projectile_index)
    : _image_path(image_path), _frame_index(frame_index), _projectile_index(projectile_index)
{
}

void projectile_remove::apply(model::resources& resources)
{
    auto& projectiles = projectiles_ref(resources);

    if (_projectile_index >= projectiles.size()) [[unlikely]]
        throw std::logic_error(std::format("Invalid projectile index: {}", _projectile_index));

    _old_projectile = projectiles[_projectile_index];

    projectiles.erase(projectiles.cbegin() + _projectile_index);
}

void projectile_remove::undo(model::resources& resources)
{
    auto& projectiles = projectiles_ref(resources);

    projectiles.insert(projectiles.cbegin() + _projectile_index, _old_projectile);
}

auto projectile_remove::undo_message() const -> std::string
{
    std::ostringstream oss;
    oss << "Add: ";
    message_footer(oss);

    return oss.str();
}

auto projectile_remove::redo_message() const -> std::string
{
    std::ostringstream oss;
    oss << "Del: ";
    message_footer(oss);

    return oss.str();
}

auto projectile_remove::projectiles_ref(model::resources& resources)
    -> decltype((model::sprite_frame::projectiles))
{
    auto iter = resources.sprite_sheets.find(_image_path);
    if (iter == resources.sprite_sheets.end())
        throw std::logic_error(std::format("Sprite '{}' not found!", _image_path.stem()));

    model::sprite_frame& sprite_frame = iter->second.frames[_frame_index];
    return sprite_frame.projectiles;
}

void projectile_remove::message_footer(std::ostringstream& oss) const
{
    oss << _image_path.stem() << " #" << _frame_index << ", PROJECTILE #" << _projectile_index << "\n";
}

} // namespace mcedit::ctrl
