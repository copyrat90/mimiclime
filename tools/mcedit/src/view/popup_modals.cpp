#include "view/popup_modals.h"

#include "model/resources.h"

#include <imgui.h>

#include <utility>

namespace mcedit::view
{

namespace
{

void next_window_center()
{
    const ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
}

} // namespace

void popup_modals::update(model::resources& resources, SDL_Window& window, bool& main_loop_done)
{
    if (!resources.error_message.empty())
    {
        _resources_error_message = std::move(resources.error_message);
        ImGui::OpenPopup("Resource error##Popup modals");
    }

    if (!_resources_error_message.empty())
    {
        next_window_center();
        if (ImGui::BeginPopupModal("Resource error##Popup modals", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
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

    if (_unsaved_changes_popup_open)
    {
        ImGui::OpenPopup("Unsaved changes##Popup modals");
        _unsaved_changes_popup_open = false;
    }

    if (_unsaved_changes.has_value())
    {
        next_window_center();
        if (ImGui::BeginPopupModal("Unsaved changes##Popup modals", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        {
            switch (*_unsaved_changes)
            {
            case unsaved_changes_op_kind::EXIT_PROGRAM:
                ImGui::Text("Save changes before exit?");

                if (ImGui::Button("Yes##Unsaved changes"))
                {
                    resources.save_changes();
                    main_loop_done = true;

                    _unsaved_changes.reset();
                }

                ImGui::SameLine();
                if (ImGui::Button("No##Unsaved changes"))
                {
                    main_loop_done = true;

                    _unsaved_changes.reset();
                }

                ImGui::SameLine();
                if (ImGui::Button("Cancel##Unsaved changes"))
                    _unsaved_changes.reset();

                break;

            case unsaved_changes_op_kind::OPEN_DIRECTORY:
                ImGui::Text("Save changes before opening directory?");

                if (ImGui::Button("Yes##Unsaved changes"))
                {
                    resources.save_changes();
                    resources.select_project_directory(window);

                    _unsaved_changes.reset();
                }

                ImGui::SameLine();
                if (ImGui::Button("No##Unsaved changes"))
                {
                    resources.select_project_directory(window);

                    _unsaved_changes.reset();
                }

                ImGui::SameLine();
                if (ImGui::Button("Cancel##Unsaved changes"))
                    _unsaved_changes.reset();

                break;

            default:
                IM_ASSERT(false && "Invalid op kind");
            }

            ImGui::EndPopup();
        }
    }
}

void popup_modals::notify_unsaved_changes(unsaved_changes_op_kind op_kind)
{
    if (_unsaved_changes != op_kind)
    {
        _unsaved_changes = op_kind;
        _unsaved_changes_popup_open = true;
    }
}

} // namespace mcedit::view
