#include "main_menu_bar.h"

#include "model/resources.h"
#include "view/select_sprite_window.h"

#include <imgui.h>

namespace mcedit::view
{

void main_menu_bar::update(select_sprite_window& select_sprite_collision_window, model::resources& resources, SDL_Window& window)
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File##Main menu bar"))
        {
            if (ImGui::MenuItem("Open mimiclime directory##Main menu bar", nullptr, resources.loaded()))
                resources.select_project_directory(window);

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
