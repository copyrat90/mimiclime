#pragma once

#include "ctrl/resource_edit.h"

#include "model/projectile.h"

#include <filesystem>

namespace mcedit::ctrl
{

class projectile_edit final : public resource_edit
{
private:
    const std::filesystem::path _image_path;
    const unsigned _frame_index;
    const unsigned _projectile_index;

    const model::projectile _old_projectile;
    const model::projectile _new_projectile;

public:
    projectile_edit(const std::filesystem::path& image_path, unsigned frame_index, unsigned projectile_index,
                    const model::projectile& old_projectile, const model::projectile& new_projectile);

    void apply(model::resources&) override;
    void undo(model::resources&) override;

    auto undo_message() const -> std::string override;
    auto redo_message() const -> std::string override;

private:
    auto projectile_ref(model::resources&) const -> model::projectile&;

    void message_header(std::ostringstream&) const;
};

} // namespace mcedit::ctrl
