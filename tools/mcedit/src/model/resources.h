#pragma once

#include "model/sprite_sheet.h"

#include <atomic>
#include <filesystem>
#include <unordered_map>

extern "C"
{
struct SDL_Window;
struct ImGuiContext;
struct ImGuiSettingsHandler;
struct ImGuiTextBuffer;
}

namespace mcedit::model
{

struct resources final
{
public:
    std::filesystem::path loaded_project_directory;

    std::unordered_map<std::filesystem::path, sprite_sheet> sprite_sheets;

    std::string error_message;

private:
    // Callback thread data
    std::atomic_bool _select_result_published;
    bool _selected_project_directory_valid;
    std::filesystem::path _selected_project_directory;

public:
    resources();

    void update(SDL_Renderer&);

    bool loaded() const
    {
        return !this->loaded_project_directory.empty();
    }

    void select_project_directory(SDL_Window&);

private:
    static void select_project_directory_callback(void* self, const char* const* filelist, int filter);

    static void* settings_handler_read_open_callback(ImGuiContext*, ImGuiSettingsHandler*, const char* name);
    static void settings_handler_read_line_callback(ImGuiContext*, ImGuiSettingsHandler*, void* entry,
                                                    const char* line);
    static void settings_handler_write_all_callback(ImGuiContext*, ImGuiSettingsHandler*, ImGuiTextBuffer*);
};

} // namespace mcedit::model
