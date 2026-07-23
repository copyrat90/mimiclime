#include "ctrl/collision_box_add.h"

#include "model/resources.h"
#include "util/enum_utils.h"

#include <format>
#include <limits>
#include <stdexcept>

namespace mcedit::ctrl
{

collision_box_add::collision_box_add(const std::filesystem::path& image_path, unsigned frame_index,
                                     model::collision_box::kind_t box_kind, const model::collision_box& new_box)
    : _image_path(image_path), _frame_index(frame_index), _box_kind(box_kind), _new_box(new_box),
      _box_index(std::numeric_limits<decltype(_box_index)>::max())
{
}

void collision_box_add::apply(model::resources& resources)
{
    auto& boxes = boxes_ref(resources);

    _box_index = static_cast<decltype(_box_index)>(boxes.size());

    boxes.push_back(_new_box);
}

void collision_box_add::undo(model::resources& resources)
{
    auto& boxes = boxes_ref(resources);

    if (_box_index >= boxes.size()) [[unlikely]]
        throw std::logic_error(std::format("Invalid box index: {}", _box_index));

    boxes.erase(boxes.cbegin() + _box_index);
}

auto collision_box_add::undo_message() const -> std::string
{
    std::ostringstream oss;
    oss << "Del: ";
    message_footer(oss);

    return oss.str();
}

auto collision_box_add::redo_message() const -> std::string
{
    std::ostringstream oss;
    oss << "Add: ";
    message_footer(oss);

    return oss.str();
}

auto collision_box_add::boxes_ref(model::resources& resources) -> decltype((model::sprite_frame::wallboxes))
{
    auto iter = resources.sprite_sheets.find(_image_path);
    if (iter == resources.sprite_sheets.end())
        throw std::logic_error(std::format("Sprite '{}' not found!", _image_path.stem()));

    model::sprite_sheet& sprite_sheet = iter->second;
    sprite_sheet.has_changes = true;

    model::sprite_frame& sprite_frame = sprite_sheet.frames[_frame_index];
    return (_box_kind == model::collision_box::kind_t::WALLBOX)   ? sprite_frame.wallboxes
           : (_box_kind == model::collision_box::kind_t::HURTBOX) ? sprite_frame.hurtboxes
                                                                  : sprite_frame.hitboxes;
}

void collision_box_add::message_footer(std::ostringstream& oss) const
{
    oss << _image_path.stem() << " #" << _frame_index << ", " << util::enum_to_sv(_box_kind) << " #" << _box_index
        << "\n";
}

} // namespace mcedit::ctrl
