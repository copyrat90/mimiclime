#pragma once

#include <imgui.h>

#include <filesystem>
#include <string>
#include <string_view>

namespace mcedit::model
{
struct resources;
}

namespace mcedit::view
{

class select_sprite_window final
{
public:
    bool visible = false;

    std::filesystem::path selected_sprite;

private:
    const std::string _title;
    const ImVec2 _window_pos;
    const ImVec2 _window_size;

public:
    select_sprite_window(std::string_view title, const ImVec2& window_pos, const ImVec2& window_size);

    void update(const model::resources&);
};

} // namespace mcedit::view
