#include "ctrl/collision_box_edit.h"

#include "model/resources.h"
#include "util/enum_utils.h"

#include <format>
#include <sstream>
#include <stdexcept>

namespace mcedit::ctrl
{

collision_box_edit::collision_box_edit(const std::filesystem::path& image_path, unsigned frame_index,
                                       model::collision_box::kind_t box_kind, unsigned box_index,
                                       const model::collision_box& old_box, const model::collision_box& new_box)
    : _image_path(image_path), _frame_index(frame_index), _box_kind(box_kind), _box_index(box_index), _old_box(old_box),
      _new_box(new_box)
{
}

void collision_box_edit::apply(model::resources& resources)
{
    box_ref(resources) = _new_box;
}

void collision_box_edit::undo(model::resources& resources)
{
    box_ref(resources) = _old_box;
}

auto collision_box_edit::undo_message() const -> std::string
{
    std::ostringstream oss;
    message_header(oss);

    if (_old_box.x != _new_box.x || _old_box.y != _new_box.y)
        oss << "Pos: (" << +_new_box.x << ", " << +_new_box.y << ") -> (" << +_old_box.x << ", " << +_old_box.y
            << ")\n";

    if (_old_box.width != _new_box.width || _old_box.height != _new_box.height)
        oss << "Dim: (" << +_new_box.width << ", " << +_new_box.height << ") -> (" << +_old_box.width << ", "
            << +_old_box.height << ")\n";

    return oss.str();
}

auto collision_box_edit::redo_message() const -> std::string
{
    std::ostringstream oss;
    message_header(oss);

    if (_old_box.x != _new_box.x || _old_box.y != _new_box.y)
        oss << "Pos: (" << +_old_box.x << ", " << +_old_box.y << ") -> (" << +_new_box.x << ", " << +_new_box.y
            << ")\n";

    if (_old_box.width != _new_box.width || _old_box.height != _new_box.height)
        oss << "Dim: (" << +_old_box.width << ", " << +_old_box.height << ") -> (" << +_new_box.width << ", "
            << +_new_box.height << ")\n";

    return oss.str();
}

auto collision_box_edit::box_ref(model::resources& resources) const -> model::collision_box&
{
    auto iter = resources.sprite_sheets.find(_image_path);
    if (iter == resources.sprite_sheets.end())
        throw std::logic_error(std::format("Sprite '{}' not found!", _image_path.stem()));

    model::sprite_frame& sprite_frame = iter->second.frames[_frame_index];
    auto& boxes = (_box_kind == model::collision_box::kind_t::WALLBOX)   ? sprite_frame.wallboxes
                  : (_box_kind == model::collision_box::kind_t::HURTBOX) ? sprite_frame.hurtboxes
                                                                         : sprite_frame.hitboxes;
    return boxes[_box_index];
}

void collision_box_edit::message_header(std::ostringstream& oss) const
{
    oss << _image_path.stem() << " #" << _frame_index << ", " << util::enum_to_sv(_box_kind) << " #" << _box_index
        << "\n";
}

} // namespace mcedit::ctrl
