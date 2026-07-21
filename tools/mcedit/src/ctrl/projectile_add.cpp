#include "ctrl/projectile_add.h"

#include "model/resources.h"

#include <format>
#include <limits>
#include <stdexcept>

namespace mcedit::ctrl
{

projectile_add::projectile_add(const std::filesystem::path& image_path, unsigned frame_index,
                               const model::projectile& new_projectile)
    : _image_path(image_path), _frame_index(frame_index), _new_projectile(new_projectile),
      _projectile_index(std::numeric_limits<decltype(_projectile_index)>::max())
{
}

void projectile_add::apply(model::resources& resources)
{
    auto& projectiles = projectiles_ref(resources);

    _projectile_index = static_cast<decltype(_projectile_index)>(projectiles.size());

    projectiles.push_back(_new_projectile);
}

void projectile_add::undo(model::resources& resources)
{
    auto& projectiles = projectiles_ref(resources);

    if (_projectile_index >= projectiles.size()) [[unlikely]]
        throw std::logic_error(std::format("Invalid projectile index: {}", _projectile_index));

    projectiles.erase(projectiles.cbegin() + _projectile_index);
}

auto projectile_add::undo_message() const -> std::string
{
    std::ostringstream oss;
    oss << "Del: ";
    message_footer(oss);

    return oss.str();
}

auto projectile_add::redo_message() const -> std::string
{
    std::ostringstream oss;
    oss << "Add: ";
    message_footer(oss);

    return oss.str();
}

auto projectile_add::projectiles_ref(model::resources& resources) -> decltype((model::sprite_frame::projectiles))
{
    auto iter = resources.sprite_sheets.find(_image_path);
    if (iter == resources.sprite_sheets.end())
        throw std::logic_error(std::format("Sprite '{}' not found!", _image_path.stem()));

    model::sprite_frame& sprite_frame = iter->second.frames[_frame_index];
    return sprite_frame.projectiles;
}

void projectile_add::message_footer(std::ostringstream& oss) const
{
    oss << _image_path.stem() << " #" << _frame_index << ", PROJECTILE #" << _projectile_index << "\n";
}

} // namespace mcedit::ctrl
