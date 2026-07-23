#include "view/select_sprite_window.h"

#include "model/resources.h"

#include <format>

namespace mcedit::view
{

select_sprite_window::select_sprite_window(std::string_view title, const ImVec2& window_pos, const ImVec2& window_size)
    : _title(title), _window_pos(window_pos), _window_size(window_size)
{
}

void select_sprite_window::update(const model::resources& resources)
{
    if (this->visible)
    {
        ImGui::SetNextWindowPos(_window_pos, ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(_window_size, ImGuiCond_FirstUseEver);
        if (ImGui::Begin(_title.c_str(), &this->visible))
        {
            if (ImGui::BeginChild("##Sprite files list", ImVec2(0, 0), ImGuiChildFlags_FrameStyle))
            {
                for (const auto& [image_path, sprite_sheet] : resources.sprite_sheets)
                {
                    const std::string name = image_path.stem().string();

                    if (ImGui::Selectable(name.c_str(),
                                          !this->selected_sprite.empty() && this->selected_sprite == image_path))
                        this->selected_sprite = image_path;
                }
            }
            ImGui::EndChild();
        }
        ImGui::End();
    }
}

} // namespace mcedit::view
