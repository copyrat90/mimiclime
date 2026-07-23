#include "main_menu_bar.h"

#include "ctrl/resources_edits.h"
#include "model/resources.h"
#include "view/popup_modals.h"
#include "view/select_sprite_window.h"

#include <imgui.h>

namespace mcedit::view
{

void main_menu_bar::update(select_sprite_window& select_sprite_collision_window, popup_modals& popups,
                           model::resources& resources, ctrl::resources_edits& resources_edits, SDL_Window& window)
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File##Main menu bar"))
        {
            if (ImGui::MenuItem("Open mimiclime directory##Main menu bar", nullptr, resources.loaded()))
            {
                if (resources.has_changes())
                    popups.notify_unsaved_changes(popup_modals::unsaved_changes_op_kind::OPEN_DIRECTORY);
                else
                    resources.select_project_directory(window);
            }

            ImGui::Separator();

            bool no_changes = !resources.has_changes();
            if (ImGui::MenuItem("Save changes##Main menu bar", "Ctrl+S", no_changes, resources.loaded()))
                resources_edits.save();

            ImGui::Separator();

            if (ImGui::MenuItem("Undo##Main menu bar", "Ctrl+Z", nullptr, resources_edits.has_undo()))
                resources_edits.undo();

            if (ImGui::MenuItem("Redo##Main menu bar", "Ctrl+Y/Ctrl+Shift+Z", nullptr, resources_edits.has_redo()))
                resources_edits.redo();

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Window##Main menu bar", resources.loaded()))
        {
            ImGui::MenuItem("Sprite collision editor##Main menu bar", nullptr, &select_sprite_collision_window.visible);

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Debug##Main menu bar"))
        {
            if (ImGui::MenuItem("Log##Main menu bar", nullptr, _debug_log_window_visible))
                _debug_log_window_visible = !_debug_log_window_visible;
            if (ImGui::MenuItem("Metrics##Main menu bar", nullptr, _metrics_window_visible))
                _metrics_window_visible = !_metrics_window_visible;

            ImGui::Separator();

            if (ImGui::MenuItem("Demo##Main menu bar", nullptr, _demo_window_visible))
                _demo_window_visible = !_demo_window_visible;

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    if (_debug_log_window_visible)
        ImGui::ShowDebugLogWindow(&_debug_log_window_visible);
    if (_metrics_window_visible)
        ImGui::ShowMetricsWindow(&_metrics_window_visible);
    if (_demo_window_visible)
        ImGui::ShowDemoWindow(&_demo_window_visible);
}

} // namespace mcedit::view
