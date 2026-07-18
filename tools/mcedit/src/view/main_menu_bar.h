#pragma once

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

class select_sprite_window;

class main_menu_bar final
{
private:
    bool _debug_log_window_visible = false;
    bool _metrics_window_visible = false;
    bool _demo_window_visible = false;

public:
    void update(select_sprite_window& select_sprite_collision_window, model::resources&, SDL_Window& window);
};

} // namespace mcedit::view
