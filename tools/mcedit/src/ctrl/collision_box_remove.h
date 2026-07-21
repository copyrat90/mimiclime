#pragma once

#include "ctrl/resource_edit.h"

#include "model/collision_box.h"
#include "model/sprite_frame.h"

#include <filesystem>
#include <sstream>

namespace mcedit::ctrl
{

class collision_box_remove final : public resource_edit
{
private:
    const std::filesystem::path _image_path;
    const unsigned _frame_index;
    const model::collision_box::kind_t _box_kind;
    const unsigned _box_index;

    model::collision_box _old_box;

public:
    collision_box_remove(const std::filesystem::path& image_path, unsigned frame_index,
                         model::collision_box::kind_t box_kind, unsigned box_index);

    void apply(model::resources&) override;
    void undo(model::resources&) override;

    auto undo_message() const -> std::string override;
    auto redo_message() const -> std::string override;

private:
    auto boxes_ref(model::resources&) -> decltype((model::sprite_frame::wallboxes));

    void message_footer(std::ostringstream&) const;
};

} // namespace mcedit::ctrl
