#pragma once

#include "ctrl/resource_edit.h"

#include "model/sprite_frame.h"

#include <filesystem>

namespace mcedit::ctrl
{

class sprite_frame_clear final : public resource_edit
{
private:
    const std::filesystem::path _image_path;
    const unsigned _frame_index;

    model::sprite_frame _old_sprite_frame;

public:
    sprite_frame_clear(const std::filesystem::path& image_path, unsigned frame_index);

    void apply(model::resources&) override;
    void undo(model::resources&) override;

    auto undo_message() const -> std::string override;
    auto redo_message() const -> std::string override;

private:
    auto sprite_frame_ref(model::resources&) const -> model::sprite_frame&;
};

} // namespace mcedit::ctrl
