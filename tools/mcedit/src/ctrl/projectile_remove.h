#pragma once

#include "ctrl/resource_edit.h"

#include "model/projectile.h"
#include "model/sprite_frame.h"

#include <filesystem>
#include <sstream>

namespace mcedit::ctrl
{

class projectile_remove final : public resource_edit
{
private:
    const std::filesystem::path _image_path;
    const unsigned _frame_index;
    const unsigned _projectile_index;

    model::projectile _old_projectile;

public:
    projectile_remove(const std::filesystem::path& image_path, unsigned frame_index, unsigned projectile_index);

    void apply(model::resources&) override;
    void undo(model::resources&) override;

    auto undo_message() const -> std::string override;
    auto redo_message() const -> std::string override;

private:
    auto projectiles_ref(model::resources&) -> decltype((model::sprite_frame::projectiles));

    void message_footer(std::ostringstream&) const;
};

} // namespace mcedit::ctrl
