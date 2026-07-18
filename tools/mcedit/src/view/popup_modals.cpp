#include "view/popup_modals.h"

#include "model/resources.h"

#include <imgui.h>

#include <utility>

namespace mcedit::view
{

void popup_modals::update(model::resources& resources)
{
    if (!resources.error_message.empty())
    {
        _resources_error_message = std::move(resources.error_message);
        ImGui::OpenPopup("Resource error");
    }

    if (!_resources_error_message.empty())
    {
        const ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

        if (ImGui::BeginPopupModal("Resource error", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text(_resources_error_message.c_str());

            if (ImGui::Button("Close##Resource error"))
            {
                ImGui::CloseCurrentPopup();
                _resources_error_message.clear();
            }

            ImGui::EndPopup();
        }
    }
}

} // namespace mcedit::view
