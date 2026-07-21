#include "model/resources.h"

#include "ctrl/resources_edits.h"

#include <imgui.h>
#include <imgui_internal.h>

#include <SDL3/SDL_dialog.h>

#include <format>
#include <sstream>
#include <utility>

namespace mcedit::model
{

namespace
{
constexpr const char* SETTINGS_HANDLER_TYPENAME = "mcedit";
constexpr const char* SETTINGS_HANDLER_SUBNAME = "directories";

constexpr const char* SETTINGS_ENTRY_PROJ_DIR = "project_directory";
} // namespace

resources::resources()
{
    ImGuiSettingsHandler settings_handler;
    settings_handler.UserData = this;
    settings_handler.TypeName = SETTINGS_HANDLER_TYPENAME;
    settings_handler.TypeHash = ImHashStr(SETTINGS_HANDLER_TYPENAME);
    settings_handler.ReadOpenFn = settings_handler_read_open_callback;
    settings_handler.ReadLineFn = settings_handler_read_line_callback;
    settings_handler.WriteAllFn = settings_handler_write_all_callback;
    ImGui::AddSettingsHandler(&settings_handler);
}

void resources::update(ctrl::resources_edits& resources_edits, SDL_Renderer& renderer)
{
    bool expected = true;
    if (_select_result_published.compare_exchange_weak(expected, false, std::memory_order::acq_rel,
                                                       std::memory_order::relaxed))
    {
        const auto project_dir = _selected_project_directory;

        if (!_selected_project_directory_valid)
        {
            this->error_message = std::format("Invalid mimiclime root directory\n\t{}", project_dir);
        }
        else
        {
            this->error_message.clear();

            try
            {
                decltype(this->sprite_sheets) result;

                const std::filesystem::path sprites_directory = project_dir / "graphics/spr";

                if (std::filesystem::exists(sprites_directory))
                {
                    for (const auto& entry : std::filesystem::directory_iterator(sprites_directory))
                    {
                        try
                        {
                            if (!entry.is_regular_file() || entry.path().extension() != ".bmp")
                                continue;

                            auto json_path = entry.path();
                            json_path.replace_extension(".json");
                            if (!std::filesystem::exists(json_path))
                                continue;

                            result.try_emplace(entry.path(), entry.path(), renderer);
                        }
                        catch (const std::exception& e)
                        {
                            this->error_message += std::format("{}\n\t{}\n", entry.path(), e.what());
                        }
                    }

                    const auto prev_loaded_project_dir = std::move(this->loaded_project_directory);

                    result.swap(this->sprite_sheets);
                    this->loaded_project_directory = project_dir;

                    resources_edits.clear();

                    if (this->loaded_project_directory != prev_loaded_project_dir)
                        ImGui::MarkIniSettingsDirty();
                }
                else
                {
                    this->error_message = std::format("Invalid mimiclime sprites directory\n\t{}", sprites_directory);
                }
            }
            catch (const std::exception& ex)
            {
                this->error_message = ex.what();
            }
        }
    }
}

void resources::select_project_directory(SDL_Window& window)
{
    const std::filesystem::path default_path =
        !this->loaded_project_directory.empty() ? this->loaded_project_directory : std::filesystem::current_path();

    SDL_ShowOpenFolderDialog(select_project_directory_callback, this, &window, default_path.string().c_str(), false);
}

void resources::select_project_directory_callback(void* self_raw, const char* const* filelist,
                                                  [[maybe_unused]] int filter)
{
    auto& self = *static_cast<resources*>(self_raw);

    if (filelist && filelist[0])
    {
        self._selected_project_directory_valid = false;
        self._selected_project_directory.clear();

        struct load_result_publisher_t
        {
            std::atomic_bool& _published;
            ~load_result_publisher_t()
            {
                _published.store(true, std::memory_order::release);
            }
            load_result_publisher_t(std::atomic_bool& published) : _published(published)
            {
            }
        } load_result_publisher(self._select_result_published);

        self._selected_project_directory = std::filesystem::path(filelist[0]);
        const std::filesystem::path sprites_directory = self._selected_project_directory / "graphics/spr";

        if (std::filesystem::exists(sprites_directory))
            self._selected_project_directory_valid = true;
    }
}

void* resources::settings_handler_read_open_callback(ImGuiContext*, ImGuiSettingsHandler*,
                                                     [[maybe_unused]] const char* name)
{
    return (void*)1;
}

void resources::settings_handler_read_line_callback(ImGuiContext*, ImGuiSettingsHandler* handler,
                                                    [[maybe_unused]] void* entry, const char* line)
{
    auto& self = *static_cast<resources*>(handler->UserData);

    std::istringstream iss(line);
    std::string key;
    std::string value;
    if (std::getline(iss, key, '=') && key == SETTINGS_ENTRY_PROJ_DIR && std::getline(iss, value))
    {
        std::filesystem::path candidate_project_dir(value);

        if (std::filesystem::exists(candidate_project_dir / "graphics/spr"))
        {
            self._selected_project_directory_valid = true;
            self._selected_project_directory = candidate_project_dir;
            self._select_result_published.store(true, std::memory_order::release);
        }
    }
}

void resources::settings_handler_write_all_callback(ImGuiContext*, ImGuiSettingsHandler* handler, ImGuiTextBuffer* buf)
{
    auto& self = *static_cast<resources*>(handler->UserData);

    buf->appendf("[%s][%s]\n", SETTINGS_HANDLER_TYPENAME, SETTINGS_HANDLER_SUBNAME);
    buf->append(SETTINGS_ENTRY_PROJ_DIR);
    buf->appendf("=%s\n", self.loaded_project_directory.string().c_str());
    buf->append("\n");
}

} // namespace mcedit::model
