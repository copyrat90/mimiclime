#include "ctrl/collision_box_remove.h"

#include "model/resources.h"
#include "util/enum_utils.h"

#include <stdexcept>
#include <format>

namespace mcedit::ctrl
{

collision_box_remove::collision_box_remove(const std::filesystem::path& image_path, unsigned frame_index,
                                           model::collision_box::kind_t box_kind, unsigned box_index)
    : _image_path(image_path), _frame_index(frame_index), _box_kind(box_kind), _box_index(box_index)
{
}

void collision_box_remove::apply(model::resources& resources)
{
    auto& boxes = boxes_ref(resources);

    if (_box_index >= boxes.size()) [[unlikely]]
        throw std::logic_error(std::format("Invalid box index: {}", _box_index));

    _old_box = boxes[_box_index];

    boxes.erase(boxes.cbegin() + _box_index);
}

void collision_box_remove::undo(model::resources& resources)
{
    auto& boxes = boxes_ref(resources);

    boxes.insert(boxes.cbegin() + _box_index, _old_box);
}

auto collision_box_remove::undo_message() const -> std::string
{
    std::ostringstream oss;
    oss << "Add: ";
    message_footer(oss);

    return oss.str();
}

auto collision_box_remove::redo_message() const -> std::string
{
    std::ostringstream oss;
    oss << "Del: ";
    message_footer(oss);

    return oss.str();
}

auto collision_box_remove::boxes_ref(model::resources& resources) -> decltype((model::sprite_frame::wallboxes))
{
    auto iter = resources.sprite_sheets.find(_image_path);
    if (iter == resources.sprite_sheets.end())
        throw std::logic_error(std::format("Sprite '{}' not found!", _image_path.stem()));

    model::sprite_frame& sprite_frame = iter->second.frames[_frame_index];
    return (_box_kind == model::collision_box::kind_t::WALLBOX)   ? sprite_frame.wallboxes
           : (_box_kind == model::collision_box::kind_t::HURTBOX) ? sprite_frame.hurtboxes
                                                                  : sprite_frame.hitboxes;
}

void collision_box_remove::message_footer(std::ostringstream& oss) const
{
    oss << _image_path.stem() << " #" << _frame_index << ", " << util::enum_to_sv(_box_kind) << " #" << _box_index
        << "\n";
}

} // namespace mcedit::ctrl
