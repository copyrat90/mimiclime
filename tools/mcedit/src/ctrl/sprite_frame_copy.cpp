#include "ctrl/sprite_frame_copy.h"

#include "model/resources.h"

#include <format>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace mcedit::ctrl
{

sprite_frame_copy::sprite_frame_copy(const std::filesystem::path& image_path, unsigned source_frame_index,
                                     unsigned destination_frame_index)
    : _image_path(image_path), _source_frame_index(source_frame_index),
      _destination_frame_index(destination_frame_index)
{
}

void sprite_frame_copy::apply(model::resources& resources)
{
    if (_source_frame_index == _destination_frame_index)
        return;

    auto& src = sprite_frame_ref(_source_frame_index, resources);
    auto& dest = sprite_frame_ref(_destination_frame_index, resources);

    _old_sprite_frame = std::move(dest);

    dest = src;
}

void sprite_frame_copy::undo(model::resources& resources)
{
    if (_source_frame_index == _destination_frame_index)
        return;

    auto& dest = sprite_frame_ref(_destination_frame_index, resources);

    dest = std::move(_old_sprite_frame);
}

auto sprite_frame_copy::undo_message() const -> std::string
{
    std::ostringstream oss;
    oss << "Revert copy from " << _image_path.stem() << " #" << _source_frame_index << " to #"
        << _destination_frame_index;

    return oss.str();
}

auto sprite_frame_copy::redo_message() const -> std::string
{
    std::ostringstream oss;
    oss << "Copy from " << _image_path.stem() << " #" << _source_frame_index << " to #" << _destination_frame_index;

    return oss.str();
}

auto sprite_frame_copy::sprite_frame_ref(unsigned frame_index, model::resources& resources) const
    -> model::sprite_frame&
{
    auto iter = resources.sprite_sheets.find(_image_path);
    if (iter == resources.sprite_sheets.end())
        throw std::logic_error(std::format("Sprite '{}' not found!", _image_path.stem()));

    model::sprite_sheet& sprite_sheet = iter->second;
    sprite_sheet.has_changes = true;

    return sprite_sheet.frames[frame_index];
}

} // namespace mcedit::ctrl
