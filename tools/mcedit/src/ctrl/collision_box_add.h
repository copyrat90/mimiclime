#pragma once

#include "ctrl/resource_edit.h"

#include "model/collision_box.h"
#include "model/sprite_frame.h"

#include <filesystem>
#include <sstream>

namespace mcedit::ctrl
{

class collision_box_add final : public resource_edit
{
private:
    const std::filesystem::path _image_path;
    const unsigned _frame_index;
    const model::collision_box::kind_t _box_kind;

    const model::collision_box _new_box;

    unsigned _box_index;

public:
    collision_box_add(const std::filesystem::path& image_path, unsigned frame_index,
                      model::collision_box::kind_t box_kind, const model::collision_box& new_box);

    void apply(model::resources&) override;
    void undo(model::resources&) override;

    auto undo_message() const -> std::string override;
    auto redo_message() const -> std::string override;

private:
    auto boxes_ref(model::resources&) -> decltype((model::sprite_frame::wallboxes));

    void message_footer(std::ostringstream&) const;
};

} // namespace mcedit::ctrl
