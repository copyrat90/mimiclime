#pragma once

#include "ctrl/resource_edit.h"

#include "model/collision_box.h"

#include <filesystem>
#include <sstream>

namespace mcedit::ctrl
{

class collision_box_edit final : public resource_edit
{
private:
    const std::filesystem::path _image_path;
    const unsigned _frame_index;
    const model::collision_box::kind_t _box_kind;
    const unsigned _box_index;

    const model::collision_box _old_box;
    const model::collision_box _new_box;

public:
    collision_box_edit(const std::filesystem::path& image_path, unsigned frame_index,
                       model::collision_box::kind_t box_kind, unsigned box_index, const model::collision_box& old_box,
                       const model::collision_box& new_box);

    void apply(model::resources&) override;
    void undo(model::resources&) override;

    auto undo_message() const -> std::string override;
    auto redo_message() const -> std::string override;

private:
    auto box_ref(model::resources&) const -> model::collision_box&;

    void message_header(std::ostringstream&) const;
};

} // namespace mcedit::ctrl
