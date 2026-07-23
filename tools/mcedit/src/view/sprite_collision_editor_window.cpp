#include "view/sprite_collision_editor_window.h"

#include "ctrl/collision_box_add.h"
#include "ctrl/collision_box_edit.h"
#include "ctrl/collision_box_remove.h"
#include "ctrl/projectile_add.h"
#include "ctrl/projectile_edit.h"
#include "ctrl/projectile_remove.h"
#include "ctrl/sprite_frame_clear.h"
#include "ctrl/sprite_frame_copy.h"
#include "model/resources.h"
#include "util/enum_utils.h"
#include "view/select_sprite_window.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <limits>
#include <memory>
#include <numbers>
#include <utility>
#include <vector>

namespace mcedit::view
{

namespace
{

constexpr float ZOOM_MIN = 100;
constexpr float ZOOM_MAX = 2000;

constexpr float RECT_EDIT_SPEED = 0.05f;

constexpr ImColor CANVAS_BG_COLOR(80, 80, 80);
constexpr ImColor ANCHOR_COLOR(160, 160, 0);

constexpr ImColor WALLBOX_COLOR(0, 192, 0);
constexpr ImColor HURTBOX_COLOR(192, 0, 0);
constexpr ImColor HITBOX_COLOR(0, 0, 192);
constexpr std::array<ImColor, 3> COLL_BOX_COLORS = {WALLBOX_COLOR, HURTBOX_COLOR, HITBOX_COLOR};

constexpr ImColor PROJECTILE_COLOR(192, 0, 192);

constexpr float PROJECTILE_RADIUS = 4;
constexpr float PROJECTILE_SPEED_MUL = 5;
constexpr float PROJECTILE_AREA = std::numbers::pi_v<float> * PROJECTILE_RADIUS * PROJECTILE_RADIUS;

} // namespace

sprite_collision_editor_window::sprite_collision_editor_window(const ImVec2& window_pos, const ImVec2& window_size,
                                                               ctrl::resources_edits& resources_edits)
    : _window_pos(window_pos), _window_size(window_size),
      _observer([this](ctrl::resources_edits::event_kind edit_event) {
          switch (edit_event)
          {
          case ctrl::resources_edits::event_kind::UNDO:
          case ctrl::resources_edits::event_kind::REDO:
          case ctrl::resources_edits::event_kind::CLEAR:
              mark_selected_element_dirty();
              break;

          default:
              break;
          }
      })
{
    resources_edits.attach_observer(_observer);
}

void sprite_collision_editor_window::update(const model::resources& resources, ctrl::resources_edits& resources_edits,
                                            const select_sprite_window& select_sprite_collision_window,
                                            std::mt19937& rng)
{
    if (select_sprite_collision_window.selected_sprite.empty())
        return;

    auto spr_iter = resources.sprite_sheets.find(select_sprite_collision_window.selected_sprite);
    if (spr_iter == resources.sprite_sheets.cend())
        return;

    const model::sprite_sheet& sprite_sheet = spr_iter->second;

    if (sprite_sheet.image_path != _prev_image_path || _frame_index < 0 ||
        _frame_index >= static_cast<decltype(_frame_index)>(sprite_sheet.frames.size()))
    {
        _frame_index = 0;
        _copy_frame_index = 0;
        reset_selected_element();

        _prev_image_path = sprite_sheet.image_path;
    }

    const model::sprite_frame& sprite_frame = sprite_sheet.frames[_frame_index];

    if (_selected_element.has_value())
    {
        if (_selected_element->kind == element_kind::PROJECTILE)
        {
            if (_selected_element->index >= sprite_frame.projectiles.size())
                reset_selected_element();
            else if (_selected_element->dirty)
            {
                _selected_element->proj = sprite_frame.projectiles[_selected_element->index],
                _selected_element->dirty = false;
            }
        }
        else
        {
            const auto& boxes = (_selected_element->kind == element_kind::WALLBOX)   ? sprite_frame.wallboxes
                                : (_selected_element->kind == element_kind::HURTBOX) ? sprite_frame.hurtboxes
                                                                                     : sprite_frame.hitboxes;
            if (_selected_element->index >= boxes.size())
                reset_selected_element();
            else if (_selected_element->dirty)
            {
                _selected_element->box = boxes[_selected_element->index];
                _selected_element->dirty = false;
            }
        }
    }

    ImGui::SetNextWindowPos(_window_pos, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(_window_size, ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Sprite collision editor"))
    {
        if (ImGui::BeginTable("##Table", 2, ImGuiTableFlags_Resizable))
        {
            struct end_table_t
            {
                ~end_table_t()
                {
                    ImGui::EndTable();
                }
            } end_table;

            ImGui::TableSetupColumn(nullptr, ImGuiTableColumnFlags_WidthStretch, 2.0f);
            ImGui::TableSetupColumn(nullptr, ImGuiTableColumnFlags_WidthStretch, 1.0f);

            ImGui::TableNextRow();
            ImGui::TableNextColumn();

            update_canvas(sprite_sheet, rng);

            const auto frames = static_cast<decltype(_frame_index)>(sprite_sheet.frames.size());
            update_frame(frames);
            update_zoom();
            update_add_buttons(resources_edits, sprite_sheet, rng);
            ImGui::Separator();
            update_copy_frame(frames, resources_edits, sprite_sheet);
            update_clear_frame(resources_edits, sprite_sheet);

            ImGui::TableNextColumn();

            update_properties(resources_edits, sprite_sheet);
        }
    }
    ImGui::End();
}

void sprite_collision_editor_window::mark_selected_element_dirty()
{
    if (_selected_element.has_value())
        _selected_element->dirty = true;
}

void sprite_collision_editor_window::reset_selected_element()
{
    _selected_element.reset();
}

void sprite_collision_editor_window::update_canvas(const model::sprite_sheet& sprite_sheet, std::mt19937& rng)
{
    static constexpr auto calculate_uvs = [](const model::sprite_sheet& sprite_sheet,
                                             unsigned frame_idx) -> std::pair<ImVec2, ImVec2> {
        const unsigned columns = sprite_sheet.texture_width / sprite_sheet.frame_width;

        const unsigned ix = frame_idx % columns;
        const unsigned iy = frame_idx / columns;

        const auto uv0_x = (static_cast<float>(ix) * sprite_sheet.frame_width / sprite_sheet.texture_width);
        const auto uv0_y = (static_cast<float>(iy) * sprite_sheet.frame_height / sprite_sheet.texture_height);
        const auto uv1_x = (static_cast<float>(ix + 1) * sprite_sheet.frame_width / sprite_sheet.texture_width);
        const auto uv1_y = (static_cast<float>(iy + 1) * sprite_sheet.frame_height / sprite_sheet.texture_height);

        return {ImVec2(uv0_x, uv0_y), ImVec2(uv1_x, uv1_y)};
    };

    static constexpr auto calculate_box_area = [](const model::collision_box& box, const ImVec2& canvas_center,
                                                  float zoom_100) -> std::pair<ImVec2, ImVec2> {
        const ImVec2 box_min(canvas_center.x + box.x * zoom_100 / 100, canvas_center.y + box.y * zoom_100 / 100);
        const ImVec2 box_max(box_min.x + box.width * zoom_100 / 100, box_min.y + box.height * zoom_100 / 100);

        return {box_min, box_max};
    };

    static constexpr auto box_is_hovered = [](const ImVec2& mouse_pos, const model::collision_box& box,
                                              const ImVec2& canvas_center, float zoom_100) -> bool {
        const auto [box_min, box_max] = calculate_box_area(box, canvas_center, zoom_100);

        return (box_min.x <= mouse_pos.x && mouse_pos.x <= box_max.x) &&
               (box_min.y <= mouse_pos.y && mouse_pos.y <= box_max.y);
    };

    static constexpr auto projectile_is_hovered = [](const ImVec2& mouse_pos, const model::projectile& proj,
                                                     const ImVec2& canvas_center, float zoom_100) -> bool {
        const ImVec2 proj_pos(canvas_center.x + proj.x * zoom_100 / 100, canvas_center.y + proj.y * zoom_100 / 100);
        const ImVec2 diff = mouse_pos - proj_pos;
        return diff.x * diff.x + diff.y * diff.y <=
               PROJECTILE_RADIUS * PROJECTILE_RADIUS * zoom_100 / 100 * zoom_100 / 100;
    };

    const model::sprite_frame& sprite_frame = sprite_sheet.frames[_frame_index];

    const ImVec2 content_region = ImGui::GetContentRegionAvail();
    const ImVec2 canvas_size(content_region.x, content_region.y * 0.75f);

    const bool clicked = ImGui::InvisibleButton("##Canvas", canvas_size);
    const ImVec2 canvas_min = ImGui::GetItemRectMin();
    const ImVec2 canvas_max = ImGui::GetItemRectMax();
    const ImVec2 canvas_center = (canvas_min + canvas_max) / 2;

    // Wheel to zoom
    if (ImGui::SetItemKeyOwner(ImGuiKey_MouseWheelY))
    {
        ImGuiIO& io = ImGui::GetIO();
        if (io.MouseWheel != 0)
            _zoom_100 = std::clamp(_zoom_100 * (1 + io.MouseWheel * 0.1f), ZOOM_MIN, ZOOM_MAX);
    }

    // Find smallest hovered elements to fill colors
    std::vector<selected_element_t> smallest_hovered_elements;
    {
        ImGuiIO& io = ImGui::GetIO();

        float smallest_area = std::numeric_limits<decltype(smallest_area)>::max();

        // Find projectiles that are hovered
        for (decltype(model::sprite_frame::projectiles)::size_type proj_idx = 0;
             proj_idx < sprite_frame.projectiles.size(); ++proj_idx)
        {
            const auto& proj = sprite_frame.projectiles[proj_idx];

            if (!projectile_is_hovered(io.MousePos, proj, canvas_center, _zoom_100))
                continue;

            smallest_hovered_elements.push_back(selected_element_t{
                .kind = element_kind::PROJECTILE,
                .index = static_cast<decltype(selected_element_t::index)>(proj_idx),
                .proj = proj,
                .prev_proj = proj,
            });
            smallest_area = PROJECTILE_AREA;
        }

        // Find smallest boxes that are hovered
        auto find_smallest_box_in_boxes = [&](const decltype(model::sprite_frame::wallboxes)& boxes,
                                              element_kind box_kind) {
            for (decltype(model::sprite_frame::wallboxes)::size_type box_idx = 0; box_idx < boxes.size(); ++box_idx)
            {
                const auto& box = boxes[box_idx];

                if (!box_is_hovered(io.MousePos, box, canvas_center, _zoom_100))
                    continue;

                const auto box_area = static_cast<decltype(smallest_area)>(box.width * box.height);
                if (box_area <= smallest_area)
                {
                    if (box_area < smallest_area)
                        smallest_hovered_elements.clear();

                    smallest_hovered_elements.push_back(selected_element_t{
                        .kind = box_kind,
                        .index = static_cast<decltype(selected_element_t::index)>(box_idx),
                        .box = box,
                        .prev_box = box,
                    });
                    smallest_area = box_area;
                }
            }
        };

        find_smallest_box_in_boxes(sprite_frame.wallboxes, element_kind::WALLBOX);
        find_smallest_box_in_boxes(sprite_frame.hurtboxes, element_kind::HURTBOX);
        find_smallest_box_in_boxes(sprite_frame.hitboxes, element_kind::HITBOX);
    }

    // Select/Deselect element on click
    if (clicked)
    {
        // Deselect if no elements are hovered
        if (smallest_hovered_elements.empty())
            reset_selected_element();
        // Select random element among the hovered smallest elements
        else
        {
            // Exclude already selected one if there's another element
            if (_selected_element.has_value() && smallest_hovered_elements.size() >= 2)
            {
                std::erase_if(smallest_hovered_elements, [&](const selected_element_t& elem) {
                    return elem.kind == _selected_element->kind && elem.index == _selected_element->index;
                });
            }

            std::uniform_int_distribution<std::size_t> dist(0, smallest_hovered_elements.size() - 1);
            const auto& newly_selected_elem = smallest_hovered_elements[dist(rng)];
            _selected_element = newly_selected_elem;
        }
    }

    const ImVec2 image_zoomed_size = ImVec2(sprite_sheet.frame_width, sprite_sheet.frame_height) * _zoom_100 / 100;
    const ImVec2 image_min = canvas_center - image_zoomed_size / 2;
    const ImVec2 image_max = canvas_center + image_zoomed_size / 2;

    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    struct pop_clip_rect_t
    {
        ImDrawList& _draw_list;
        ~pop_clip_rect_t()
        {
            _draw_list.PopClipRect();
        }
        pop_clip_rect_t(ImDrawList& draw_list) : _draw_list(draw_list)
        {
        }
    };

    draw_list->PushClipRect(canvas_min, canvas_max, true);
    {
        pop_clip_rect_t pop_clip_rect(*draw_list);

        // Fill canvas background color
        draw_list->AddRectFilled(canvas_min, canvas_max, CANVAS_BG_COLOR);

        // Draw sprite frame
        const auto [uv_min, uv_max] = calculate_uvs(sprite_sheet, _frame_index);
        draw_list->AddImage(&sprite_sheet.texture, image_min, image_max, uv_min, uv_max);

        static constexpr float HOVER_ALPHA = 0.2f;

        // Draw collision boxes
        for (auto box_kind = element_kind::WALLBOX; box_kind <= element_kind::HITBOX;
             box_kind = static_cast<element_kind>(std::to_underlying(box_kind) + 1))
        {
            const ImColor& color = COLL_BOX_COLORS[std::to_underlying(box_kind)];
            const auto& boxes = (box_kind == element_kind::WALLBOX)   ? sprite_frame.wallboxes
                                : (box_kind == element_kind::HURTBOX) ? sprite_frame.hurtboxes
                                                                      : sprite_frame.hitboxes;

            for (decltype(model::sprite_frame::wallboxes)::size_type box_idx = 0; box_idx < boxes.size(); ++box_idx)
            {
                // Selected box is skipped because we deal with it seperately below
                if (_selected_element.has_value() && _selected_element->kind == box_kind &&
                    _selected_element->index == box_idx)
                    continue;

                const auto& box = boxes[box_idx];
                const auto [box_min, box_max] = calculate_box_area(box, canvas_center, _zoom_100);

                if (std::ranges::find_if(smallest_hovered_elements, [&](const selected_element_t& elem) {
                        return elem.kind == box_kind && elem.index == box_idx;
                    }) != smallest_hovered_elements.cend())
                {
                    ImColor hover_color = color;
                    hover_color.Value.w = HOVER_ALPHA;
                    draw_list->AddRectFilled(box_min, box_max, hover_color);
                }

                draw_list->AddRect(box_min, box_max, color);
            }
        }

        // Draw projectiles
        for (decltype(model::sprite_frame::projectiles)::size_type proj_idx = 0;
             proj_idx < sprite_frame.projectiles.size(); ++proj_idx)
        {
            // Selected projectile is skipped because we deal with it seperately below
            if (_selected_element.has_value() && _selected_element->kind == element_kind::PROJECTILE &&
                _selected_element->index == proj_idx)
                continue;

            const auto& proj = sprite_frame.projectiles[proj_idx];
            const ImVec2 proj_pos(canvas_center.x + proj.x * _zoom_100 / 100,
                                  canvas_center.y + proj.y * _zoom_100 / 100);
            const float proj_radius = PROJECTILE_RADIUS * _zoom_100 / 100;

            if (std::ranges::find_if(smallest_hovered_elements, [&](const selected_element_t& elem) {
                    return elem.kind == element_kind::PROJECTILE && elem.index == proj_idx;
                }) != smallest_hovered_elements.cend())
            {
                static constexpr ImColor HOVER_COLOR = [] {
                    ImColor result = PROJECTILE_COLOR;
                    result.Value.w = HOVER_ALPHA;
                    return result;
                }();

                draw_list->AddCircleFilled(proj_pos, proj_radius, HOVER_COLOR);
            }

            draw_list->AddCircle(proj_pos, proj_radius, PROJECTILE_COLOR);
            draw_list->AddLine(proj_pos,
                               proj_pos + model::to_normal_vector(proj.direction) * proj.speed * PROJECTILE_SPEED_MUL *
                                              _zoom_100 / 100,
                               PROJECTILE_COLOR, 2);
        }

        // Draw selected element
        if (_selected_element.has_value())
        {
            static constexpr float SELECT_ALPHA = 0.55f;

            switch (_selected_element->kind)
            {
            case element_kind::WALLBOX:
            case element_kind::HURTBOX:
            case element_kind::HITBOX: {
                const ImColor& border_color = COLL_BOX_COLORS[std::to_underlying(_selected_element->kind)];
                ImColor fill_color = border_color;
                fill_color.Value.w = SELECT_ALPHA;

                const auto [box_min, box_max] = calculate_box_area(_selected_element->box, canvas_center, _zoom_100);
                draw_list->AddRectFilled(box_min, box_max, fill_color);
                draw_list->AddRect(box_min, box_max, border_color);
            }
            break;

            case element_kind::PROJECTILE: {
                static constexpr ImColor FILL_COLOR = [] constexpr -> ImColor {
                    ImColor result = PROJECTILE_COLOR;
                    result.Value.w = SELECT_ALPHA;
                    return result;
                }();

                const auto& proj = _selected_element->proj;
                const ImVec2 proj_pos(canvas_center.x + proj.x * _zoom_100 / 100,
                                      canvas_center.y + proj.y * _zoom_100 / 100);
                const float proj_radius = PROJECTILE_RADIUS * _zoom_100 / 100;

                draw_list->AddCircleFilled(proj_pos, proj_radius, FILL_COLOR);
                draw_list->AddCircle(proj_pos, proj_radius, PROJECTILE_COLOR);
                draw_list->AddLine(proj_pos,
                                   proj_pos + model::to_normal_vector(proj.direction) * proj.speed *
                                                  PROJECTILE_SPEED_MUL * _zoom_100 / 100,
                                   PROJECTILE_COLOR, 2);
            }
            break;

            default:
                IM_ASSERT(false && "Invalid element kind");
            }
        }

        // Draw anchor
        static constexpr float ANCHOR_LENGTH = 3;
        static constexpr float ANCHOR_THICKNESS = 2;
        draw_list->AddLineH(canvas_center.x - ANCHOR_LENGTH / 2 * _zoom_100 / 100,
                            canvas_center.x + ANCHOR_LENGTH / 2 * _zoom_100 / 100, canvas_center.y, ANCHOR_COLOR,
                            ANCHOR_THICKNESS);
        draw_list->AddLineV(canvas_center.x, canvas_center.y - ANCHOR_LENGTH / 2 * _zoom_100 / 100,
                            canvas_center.y + ANCHOR_LENGTH / 2 * _zoom_100 / 100, ANCHOR_COLOR, ANCHOR_THICKNESS);
    }
}

void sprite_collision_editor_window::update_frame(decltype(_frame_index) frames)
{
    if (ImGui::SliderInt("Frame##Sprite collision editor", &_frame_index, 0, frames - 1, "%d",
                         ImGuiSliderFlags_AlwaysClamp))
    {
        reset_selected_element();
    }
}

void sprite_collision_editor_window::update_zoom()
{
    ImGui::DragFloat("Zoom##Sprite collision editor", &_zoom_100, 2, ZOOM_MIN, ZOOM_MAX, "%.0f%%");
}

void sprite_collision_editor_window::update_add_buttons(ctrl::resources_edits& resources_edits,
                                                        const model::sprite_sheet& sprite_sheet, std::mt19937& rng)
{
    struct pop_style_color_t
    {
        ~pop_style_color_t()
        {
            ImGui::PopStyleColor();
        }
    };

    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)WALLBOX_COLOR);
    {
        pop_style_color_t pop_style_color;
        if (ImGui::Button("Add wallbox"))
            add_element_with_random_properties(element_kind::WALLBOX, resources_edits, sprite_sheet, rng);
    }

    ImGui::SameLine();
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)HURTBOX_COLOR);
    {
        pop_style_color_t pop_style_color;
        if (ImGui::Button("Add hurtbox"))
            add_element_with_random_properties(element_kind::HURTBOX, resources_edits, sprite_sheet, rng);
    }

    ImGui::SameLine();
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)HITBOX_COLOR);
    {
        pop_style_color_t pop_style_color;
        if (ImGui::Button("Add hitbox"))
            add_element_with_random_properties(element_kind::HITBOX, resources_edits, sprite_sheet, rng);
    }

    ImGui::SameLine();
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)PROJECTILE_COLOR);
    {
        pop_style_color_t pop_style_color;
        if (ImGui::Button("Add projectile"))
            add_element_with_random_properties(element_kind::PROJECTILE, resources_edits, sprite_sheet, rng);
    }
}

void sprite_collision_editor_window::update_copy_frame(decltype(_frame_index) frames,
                                                       ctrl::resources_edits& resources_edits,
                                                       const model::sprite_sheet& sprite_sheet)
{
    ImGui::SliderInt("Copy from frame##Sprite collision editor", &_copy_frame_index, 0, frames - 1, "%d",
                     ImGuiSliderFlags_AlwaysClamp);

    ImGui::SameLine();
    if (ImGui::Button("Copy##Sprite collision editor"))
    {
        if (_frame_index != _copy_frame_index)
        {
            auto copy =
                std::make_unique<ctrl::sprite_frame_copy>(sprite_sheet.image_path, _copy_frame_index, _frame_index);

            resources_edits.add(std::move(copy));
        }
    }
}

void sprite_collision_editor_window::update_clear_frame(ctrl::resources_edits& resources_edits,
                                                        const model::sprite_sheet& sprite_sheet)
{
    if (ImGui::Button("Clear all##Sprite collision editor"))
    {
        auto clear = std::make_unique<ctrl::sprite_frame_clear>(sprite_sheet.image_path, _frame_index);

        resources_edits.add(std::move(clear));
    }
}

void sprite_collision_editor_window::update_properties(ctrl::resources_edits& resources_edits,
                                                       const model::sprite_sheet& sprite_sheet)
{
    if (!_selected_element.has_value())
        update_none_properties();
    else
        switch (_selected_element->kind)
        {
        case element_kind::WALLBOX:
        case element_kind::HURTBOX:
        case element_kind::HITBOX:
            update_box_properties(resources_edits, sprite_sheet);
            break;

        case element_kind::PROJECTILE:
            update_projectile_properties(resources_edits, sprite_sheet);
            break;

        default:
            IM_ASSERT(false && "Invalid element kind");
        }
}

void sprite_collision_editor_window::update_none_properties()
{
    ImGui::Text("Click the element to edit...");
}

void sprite_collision_editor_window::update_box_properties(ctrl::resources_edits& resources_edits,
                                                           const model::sprite_sheet& sprite_sheet)
{
    auto& box = _selected_element->box;
    const auto& box_color = COLL_BOX_COLORS[std::to_underlying(_selected_element->kind)];

    auto submit_box_edit = [&] {
        auto edit = std::make_unique<ctrl::collision_box_edit>(
            sprite_sheet.image_path, _frame_index,
            static_cast<model::collision_box::kind_t>(std::to_underlying(_selected_element->kind)),
            _selected_element->index, _selected_element->prev_box, box);

        resources_edits.add(std::move(edit));
    };

    ImGui::TextColored(box_color, "%s #%u", util::enum_to_c_str(_selected_element->kind), _selected_element->index);

    int position_temp[2] = {box.x, box.y};
    const bool position_dragged = ImGui::DragInt2("Position##Sprite collision editor", position_temp, RECT_EDIT_SPEED,
                                                  std::numeric_limits<decltype(model::collision_box::x)>::min(),
                                                  std::numeric_limits<decltype(model::collision_box::x)>::max(),
                                                  nullptr, ImGuiSliderFlags_ClampOnInput);
    if (ImGui::IsItemActivated())
    {
        _selected_element->prev_box = box;
    }
    if (position_dragged)
    {
        box.x = static_cast<decltype(model::collision_box::x)>(position_temp[0]);
        box.y = static_cast<decltype(model::collision_box::y)>(position_temp[1]);
    }
    if (ImGui::IsItemDeactivatedAfterEdit())
    {
        if (box.x != _selected_element->prev_box.x || box.y != _selected_element->prev_box.y)
            submit_box_edit();
    }

    int dimensions_temp[2] = {box.width, box.height};
    const bool dimensions_dragged = ImGui::DragInt2(
        "Dimensions##Sprite collision editor", dimensions_temp, RECT_EDIT_SPEED, 1,
        std::numeric_limits<decltype(model::collision_box::width)>::max(), nullptr, ImGuiSliderFlags_ClampOnInput);
    if (ImGui::IsItemActivated())
    {
        _selected_element->prev_box = box;
    }
    if (dimensions_dragged)
    {
        box.width = static_cast<decltype(model::collision_box::width)>(dimensions_temp[0]);
        box.height = static_cast<decltype(model::collision_box::height)>(dimensions_temp[1]);
    }
    if (ImGui::IsItemDeactivatedAfterEdit())
    {
        if (box.width != _selected_element->prev_box.width || box.height != _selected_element->prev_box.height)
            submit_box_edit();
    }

    ImGui::Separator();

    if (ImGui::Button("Remove collision box"))
    {
        auto remove_box = std::make_unique<ctrl::collision_box_remove>(
            sprite_sheet.image_path, _frame_index,
            static_cast<model::collision_box::kind_t>(std::to_underlying(_selected_element->kind)),
            _selected_element->index);
        resources_edits.add(std::move(remove_box));

        reset_selected_element();
    }
}

void sprite_collision_editor_window::update_projectile_properties(ctrl::resources_edits& resources_edits,
                                                                  const model::sprite_sheet& sprite_sheet)
{
    auto& proj = _selected_element->proj;

    auto submit_projectile_edit = [&] {
        auto edit = std::make_unique<ctrl::projectile_edit>(
            sprite_sheet.image_path, _frame_index, _selected_element->index, _selected_element->prev_proj, proj);

        resources_edits.add(std::move(edit));
    };

    ImGui::TextColored(PROJECTILE_COLOR, "%s #%u", util::enum_to_c_str(element_kind::PROJECTILE),
                       _selected_element->index);

    if (ImGui::BeginCombo("Kind##Sprite collision editor", util::enum_to_c_str(proj.kind)))
    {
        template for (constexpr std::meta::info proj_kind_info :
                      std::define_static_array(std::meta::enumerators_of(^^model::projectile::kind_t)))
        {
            const model::projectile::kind_t proj_kind = [:proj_kind_info:];
            const bool selected = (proj.kind == proj_kind);

            if (ImGui::Selectable(std::define_static_string(std::meta::identifier_of(proj_kind_info)), selected))
            {
                if (!selected)
                {
                    _selected_element->prev_proj = proj;
                    proj.kind = proj_kind;
                    submit_projectile_edit();
                }
            }

            if (selected)
                ImGui::SetItemDefaultFocus();
        }

        ImGui::EndCombo();
    }

    int position_temp[2] = {proj.x, proj.y};
    const bool position_dragged = ImGui::DragInt2("Position##Sprite collision editor", position_temp, RECT_EDIT_SPEED,
                                                  std::numeric_limits<decltype(model::projectile::x)>::min(),
                                                  std::numeric_limits<decltype(model::projectile::x)>::max(), nullptr,
                                                  ImGuiSliderFlags_ClampOnInput);
    if (ImGui::IsItemActivated())
    {
        _selected_element->prev_proj = proj;
    }
    if (position_dragged)
    {
        proj.x = static_cast<decltype(model::projectile::x)>(position_temp[0]);
        proj.y = static_cast<decltype(model::projectile::y)>(position_temp[1]);
    }
    if (ImGui::IsItemDeactivatedAfterEdit())
    {
        if (proj.x != _selected_element->prev_proj.x || proj.y != _selected_element->prev_proj.y)
            submit_projectile_edit();
    }

    int direction_temp = static_cast<int>(proj.direction);
    const char* direction_c_str = util::enum_to_c_str(proj.direction);
    const bool direction_slid = ImGui::SliderInt(
        "Direction##Sprite collision editor", &direction_temp, static_cast<int>(model::direction_t::NONE),
        util::size_of_enum<model::direction_t>() - 1 + static_cast<int>(model::direction_t::NONE), direction_c_str);
    if (ImGui::IsItemActivated())
    {
        _selected_element->prev_proj = proj;
    }
    if (direction_slid)
    {
        proj.direction = static_cast<decltype(model::projectile::direction)>(direction_temp);
    }
    if (ImGui::IsItemDeactivatedAfterEdit())
    {
        if (proj.direction != _selected_element->prev_proj.direction)
            submit_projectile_edit();
    }

    ImGui::DragFloat("Speed##Sprite collision editor", &proj.speed, 0.005f, 0, 1000, "%.3f px/frame",
                     ImGuiSliderFlags_AlwaysClamp);
    if (ImGui::IsItemActivated())
    {
        _selected_element->prev_proj = proj;
    }
    if (ImGui::IsItemDeactivatedAfterEdit())
    {
        if (proj.speed != _selected_element->prev_proj.speed)
            submit_projectile_edit();
    }

    ImGui::Separator();

    if (ImGui::Button("Remove projectile"))
    {
        auto remove_proj =
            std::make_unique<ctrl::projectile_remove>(sprite_sheet.image_path, _frame_index, _selected_element->index);
        resources_edits.add(std::move(remove_proj));

        reset_selected_element();
    }
}

void sprite_collision_editor_window::add_element_with_random_properties(element_kind kind,
                                                                        ctrl::resources_edits& resources_edits,
                                                                        const model::sprite_sheet& sprite_sheet,
                                                                        std::mt19937& rng)
{
    static constexpr decltype(model::collision_box::x) POS_MAX = 16;
    static constexpr decltype(model::collision_box::x) POS_MIN = -POS_MAX;
    static constexpr decltype(model::collision_box::width) BOX_DIMENSION = 8;

    const model::sprite_frame& sprite_frame = sprite_sheet.frames[_frame_index];

    switch (kind)
    {
    case element_kind::WALLBOX:
    case element_kind::HURTBOX:
    case element_kind::HITBOX: {
        std::uniform_int_distribution<decltype(model::collision_box::x)> pos_dist(POS_MIN, POS_MAX - BOX_DIMENSION);

        model::collision_box box{
            .x = pos_dist(rng),
            .y = pos_dist(rng),
            .width = BOX_DIMENSION,
            .height = BOX_DIMENSION,
        };

        auto box_add = std::make_unique<ctrl::collision_box_add>(
            sprite_sheet.image_path, _frame_index, static_cast<model::collision_box::kind_t>(std::to_underlying(kind)),
            box);
        resources_edits.add(std::move(box_add));

        const auto& boxes = (kind == element_kind::WALLBOX)   ? sprite_frame.wallboxes
                            : (kind == element_kind::HURTBOX) ? sprite_frame.hurtboxes
                                                              : sprite_frame.hitboxes;
        _selected_element = selected_element_t{
            .kind = kind,
            .index = static_cast<decltype(selected_element_t::index)>(boxes.size() - 1),
            .box = box,
            .prev_box = box,
        };
    }
    break;

    case element_kind::PROJECTILE: {
        std::uniform_int_distribution<decltype(model::collision_box::x)> pos_dist(POS_MIN, POS_MAX);

        model::projectile proj{
            .kind = model::projectile::kind_t::FIREBALL,
            .x = pos_dist(rng),
            .y = pos_dist(rng),
            .direction = model::direction_t::UP,
            .speed = 4.0f,
        };

        auto proj_add = std::make_unique<ctrl::projectile_add>(sprite_sheet.image_path, _frame_index, proj);
        resources_edits.add(std::move(proj_add));

        _selected_element = selected_element_t{
            .kind = kind,
            .index = static_cast<decltype(selected_element_t::index)>(sprite_frame.projectiles.size() - 1),
            .proj = proj,
            .prev_proj = proj,
        };
    }
    break;

    default:
        IM_ASSERT(false && "Invalid kind");
    }
}

} // namespace mcedit::view
