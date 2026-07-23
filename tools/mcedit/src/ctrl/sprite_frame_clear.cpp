#include "ctrl/sprite_frame_clear.h"

#include "model/resources.h"

#include <format>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace mcedit::ctrl
{

sprite_frame_clear::sprite_frame_clear(const std::filesystem::path& image_path, unsigned frame_index)
    : _image_path(image_path), _frame_index(frame_index)
{
}

void sprite_frame_clear::apply(model::resources& resources)
{
    auto& frame = sprite_frame_ref(resources);

    _old_sprite_frame = std::move(frame);
}

void sprite_frame_clear::undo(model::resources& resources)
{
    auto& frame = sprite_frame_ref(resources);

    frame = std::move(_old_sprite_frame);
}

auto sprite_frame_clear::undo_message() const -> std::string
{
    std::ostringstream oss;
    oss << "Revert clear: " << _image_path.stem() << " #" << _frame_index;

    return oss.str();
}

auto sprite_frame_clear::redo_message() const -> std::string
{
    std::ostringstream oss;
    oss << "Clear: " << _image_path.stem() << " #" << _frame_index;

    return oss.str();
}

auto sprite_frame_clear::sprite_frame_ref(model::resources& resources) const -> model::sprite_frame&
{
    auto iter = resources.sprite_sheets.find(_image_path);
    if (iter == resources.sprite_sheets.end())
        throw std::logic_error(std::format("Sprite '{}' not found!", _image_path.stem()));

    model::sprite_sheet& sprite_sheet = iter->second;
    sprite_sheet.has_changes = true;

    return sprite_sheet.frames[_frame_index];
}

} // namespace mcedit::ctrl
