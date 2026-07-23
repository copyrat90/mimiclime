#pragma once

#include <cstdint>
#include <optional>
#include <string>

extern "C"
{
struct SDL_Window;
}

namespace mcedit::model
{
struct resources;
}

namespace mcedit::view
{

class popup_modals final
{
public:
    enum class unsaved_changes_op_kind : std::uint8_t
    {
        EXIT_PROGRAM,
        OPEN_DIRECTORY,
    };

private:
    std::string _resources_error_message;

    std::optional<unsaved_changes_op_kind> _unsaved_changes;
    bool _unsaved_changes_popup_open = false;

public:
    void update(model::resources&, SDL_Window&, bool& main_loop_done);

    void notify_unsaved_changes(unsaved_changes_op_kind);
};

} // namespace mcedit::view
