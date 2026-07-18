#pragma once

#include "model/collision_box.h"
#include "model/projectile.h"

#include <imgui.h>

#include <cstdint>
#include <filesystem>
#include <optional>
#include <random>

namespace mcedit::model
{
struct resources;
struct sprite_sheet;
} // namespace mcedit::model

namespace mcedit::view
{

class select_sprite_window;

class sprite_collision_editor_window final
{
private:
    const ImVec2 _window_pos;
    const ImVec2 _window_size;

    std::filesystem::path _prev_image_path;

    int _frame_index = 0;
    float _zoom_100 = 800;

    enum class element_kind : std::uint8_t
    {
        WALLBOX,
        HURTBOX,
        HITBOX,
        PROJECTILE,
    };

    struct selected_element_t
    {
        bool dirty = false;

        element_kind kind;
        unsigned index;

        union {
            model::collision_box box;
            model::projectile proj;
        };
    };

    std::optional<selected_element_t> _selected_element;

public:
    sprite_collision_editor_window(const ImVec2& window_pos, const ImVec2& window_size);

    void update(const model::resources&, const select_sprite_window& select_sprite_collision_window, std::mt19937& rng);

    void mark_selected_element_dirty();

private:
    void reset_selected_element();

    void update_canvas(const model::sprite_sheet&, std::mt19937& rng);

    void update_frame(decltype(_frame_index) frames);
    void update_zoom();
    void update_add_buttons(std::mt19937& rng);

    void update_properties();
    void update_none_properties();
    void update_box_properties();
    void update_projectile_properties();

    void add_element_with_random_properties(element_kind, std::mt19937& rng);
};

} // namespace mcedit::view
