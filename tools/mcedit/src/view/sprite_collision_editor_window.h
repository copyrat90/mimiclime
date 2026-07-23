#pragma once

#include "ctrl/resources_edits.h"
#include "model/collision_box.h"
#include "model/projectile.h"
#include "util/observer.h"

#include <imgui.h>

#include <cstdint>
#include <filesystem>
#include <optional>
#include <random>
#include <utility>

namespace mcedit::model
{
struct resources;
struct sprite_sheet;
struct sprite_frame;
} // namespace mcedit::model

namespace mcedit::view
{

class select_sprite_window;

class sprite_collision_editor_window final
{
private:
    const ImVec2 _window_pos;
    const ImVec2 _window_size;

    util::observer<void(ctrl::resources_edits::event_kind)> _observer;

    std::filesystem::path _prev_image_path;

    int _frame_index = 0;
    float _zoom_100 = 800;

    int _copy_frame_index = 0;

    enum class element_kind : std::uint8_t
    {
        WALLBOX = std::to_underlying(model::collision_box::kind_t::WALLBOX),
        HURTBOX = std::to_underlying(model::collision_box::kind_t::HURTBOX),
        HITBOX = std::to_underlying(model::collision_box::kind_t::HITBOX),
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

        // for store previous properties to issue edit command
        union {
            model::collision_box prev_box;
            model::projectile prev_proj;
        };
    };

    std::optional<selected_element_t> _selected_element;

public:
    sprite_collision_editor_window(const ImVec2& window_pos, const ImVec2& window_size, ctrl::resources_edits&);

    void update(const model::resources&, ctrl::resources_edits&,
                const select_sprite_window& select_sprite_collision_window, std::mt19937& rng);

private:
    void mark_selected_element_dirty();

    void reset_selected_element();

    void update_canvas(const model::sprite_sheet&, std::mt19937& rng);

    void update_frame(decltype(_frame_index) frames);
    void update_zoom();
    void update_add_buttons(ctrl::resources_edits&, const model::sprite_sheet&, std::mt19937& rng);
    void update_copy_frame(decltype(_frame_index) frames, ctrl::resources_edits&, const model::sprite_sheet&);
    void update_clear_frame(ctrl::resources_edits&, const model::sprite_sheet&);

    void update_properties(ctrl::resources_edits&, const model::sprite_sheet&);
    void update_none_properties();
    void update_box_properties(ctrl::resources_edits&, const model::sprite_sheet&);
    void update_projectile_properties(ctrl::resources_edits&, const model::sprite_sheet&);

    void add_element_with_random_properties(element_kind, ctrl::resources_edits&, const model::sprite_sheet&,
                                            std::mt19937& rng);
};

} // namespace mcedit::view
