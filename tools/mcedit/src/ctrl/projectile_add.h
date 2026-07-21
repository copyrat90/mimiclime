#pragma once

#include "ctrl/resource_edit.h"

#include "model/projectile.h"
#include "model/sprite_frame.h"

#include <filesystem>
#include <sstream>

namespace mcedit::ctrl
{

class projectile_add final : public resource_edit
{
private:
    const std::filesystem::path _image_path;
    const unsigned _frame_index;

    const model::projectile _new_projectile;

    unsigned _projectile_index;

public:
    projectile_add(const std::filesystem::path& image_path, unsigned frame_index, const model::projectile& new_projectile);

    void apply(model::resources&) override;
    void undo(model::resources&) override;

    auto undo_message() const -> std::string override;
    auto redo_message() const -> std::string override;

private:
    auto projectiles_ref(model::resources&) -> decltype((model::sprite_frame::projectiles));

    void message_footer(std::ostringstream&) const;
};

} // namespace mcedit::ctrl
