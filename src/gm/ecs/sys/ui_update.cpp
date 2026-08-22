#include "gm/ecs/sys/ui_update.h"

#include "gm/cfg/interactable_infos.h"
#include "gm/cfg/species_infos.h"
#include "gm/ecs/ut/find_entity.h"
#include "gm/ingame_texts.h"
#include "txt/critter_ui_texts.h"
#include "ut/text_generators.h"

#include <bn_colors.h>
#include <bn_display.h>
#include <bn_format.h>

namespace mc::gm::ecs::sys
{

namespace
{

constexpr int UI_BG_PRIORITY = 0;

constexpr auto UI_TEXT_FONT = mc::ut::text_generators::font::GALMURI_9;

constexpr bn::fixed_point PLAYER_STATUS_UI_TEXT_POS(2, 2);
constexpr bn::color PLAYER_STATUS_UI_TEXT_COLOR = bn::colors::magenta;
constexpr auto PLAYER_STATUS_UI_TEXT_ALIGN = bn::sprite_text_generator::alignment_type::LEFT;

constexpr bn::fixed_point MOB_STATUS_UI_TEXT_POS(bn::display::width() / 2, bn::display::height() - 12);
constexpr bn::color MOB_STATUS_UI_TEXT_COLOR = bn::colors::red;
constexpr auto MOB_STATUS_UI_TEXT_ALIGN = bn::sprite_text_generator::alignment_type::CENTER;

constexpr auto INTERACTABLE_TOOLTIP_TEXT_FONT = mc::ut::text_generators::font::GALMURI_7;
constexpr int INTERACTABLE_TOOLTIP_TEXT_BG_PRIORITY = UI_BG_PRIORITY + 1;
constexpr bn::color INTERACTABLE_TOOLTIP_TEXT_COLOR = bn::colors::cyan;
constexpr auto INTERACTABLE_TOOLTIP_TEXT_ALIGN = bn::sprite_text_generator::alignment_type::CENTER;

} // namespace

void ui_update(singleton_registry& singleton_reg, const gba::entity singleton_entity, actor_registry& actor_reg,
               mc::ut::text_generators& text_generators, const ldtk::gen::lang lang)
{
    auto* ui_states = singleton_reg.try_get<cpn::ui_states>(singleton_entity);
    BN_ASSERT(ui_states);
    const auto* actors_of_interest = singleton_reg.try_get<cpn::actors_of_interest>(singleton_entity);
    BN_ASSERT(actors_of_interest);

    const gba::entity status_mob = actors_of_interest->status_mob;
    const gba::entity nearby_interactable = actors_of_interest->nearby_interactable;
    const gba::entity player = ut::find_player_critter(actor_reg);

    // Player
    auto* player_critter_states = actor_reg.try_get<cpn::critter_states>(player);
    BN_ASSERT(player_critter_states);

    if (player_critter_states->species() != ui_states->last_player_species ||
        player_critter_states->hp() != ui_states->last_player_hp)
    {
        ui_states->status_player_texts.clear();

        auto& text_gen = text_generators.get(UI_TEXT_FONT);

        const auto prev_color = text_generators.text_color(UI_TEXT_FONT);
        const auto prev_align = text_gen.alignment();
        const auto prev_priority = text_gen.bg_priority();
        text_generators.set_text_color(UI_TEXT_FONT, PLAYER_STATUS_UI_TEXT_COLOR);
        text_gen.set_alignment(PLAYER_STATUS_UI_TEXT_ALIGN);
        text_gen.set_bg_priority(UI_BG_PRIORITY);
        {
            const auto& species_infos = cfg::species_infos::get(player_critter_states->species());
            const auto species_name = species_infos.name(lang);
            const auto current_hp = static_cast<int>(player_critter_states->hp());
            const auto max_hp = species_infos.hp();

            auto str = bn::format<64>(txt::CRITTER_STATUS_UI_TEXT_FMT, species_name, current_hp, max_hp);
            text_gen.generate_top_left(PLAYER_STATUS_UI_TEXT_POS, str, ui_states->status_player_texts);
        }
        text_gen.set_bg_priority(prev_priority);
        text_gen.set_alignment(prev_align);
        text_generators.set_text_color(UI_TEXT_FONT, prev_color);

        ui_states->last_player_species = player_critter_states->species();
        ui_states->last_player_hp = player_critter_states->hp();
    }

    // Mob to show the status
    if (actor_reg.valid(status_mob))
    {
        auto* critter_states = actor_reg.try_get<cpn::critter_states>(status_mob);
        BN_ASSERT(critter_states);

        if (critter_states->species() != ui_states->last_status_mob_species ||
            critter_states->hp() != ui_states->last_status_mob_hp)
        {
            ui_states->status_mob_texts.clear();

            auto& text_gen = text_generators.get(UI_TEXT_FONT);

            const auto prev_color = text_generators.text_color(UI_TEXT_FONT);
            const auto prev_align = text_gen.alignment();
            const auto prev_priority = text_gen.bg_priority();
            text_generators.set_text_color(UI_TEXT_FONT, MOB_STATUS_UI_TEXT_COLOR);
            text_gen.set_alignment(MOB_STATUS_UI_TEXT_ALIGN);
            text_gen.set_bg_priority(UI_BG_PRIORITY);
            {
                const auto& species_infos = cfg::species_infos::get(critter_states->species());
                const auto species_name = species_infos.name(lang);
                const auto current_hp = static_cast<int>(critter_states->hp());
                const auto max_hp = species_infos.hp();

                auto str = bn::format<64>(txt::CRITTER_STATUS_UI_TEXT_FMT, species_name, current_hp, max_hp);
                text_gen.generate_top_left(MOB_STATUS_UI_TEXT_POS, str, ui_states->status_mob_texts);
            }
            text_gen.set_bg_priority(prev_priority);
            text_gen.set_alignment(prev_align);
            text_generators.set_text_color(UI_TEXT_FONT, prev_color);

            ui_states->last_status_mob_species = critter_states->species();
            ui_states->last_status_mob_hp = critter_states->hp();
        }
    }
    else
    {
        ui_states->status_mob_texts.clear();

        ui_states->last_status_mob_species = ldtk::gen::species_kind::slime;
        ui_states->last_status_mob_hp = 0;
    }

    // Tooltip text on top of nearby interactable
    if (actor_reg.valid(nearby_interactable))
    {
        const auto* interactable_sprite = actor_reg.try_get<bn::sprite_ptr>(nearby_interactable);
        BN_ASSERT(interactable_sprite);
        const auto interactable_position =
            interactable_sprite->top_left_position() + bn::fixed_point(interactable_sprite->shape_size().width() / 2,
                                                                       interactable_sprite->shape_size().height() / 2);

        if (nearby_interactable != ui_states->last_nearby_interactable ||
            ui_states->reserved_interactable_tooltip.has_value())
        {
            const auto* interactable_states = actor_reg.try_get<cpn::interactable_states>(nearby_interactable);
            BN_ASSERT(interactable_states);
            const auto& interactable_infos = cfg::interactable_infos::get(interactable_states->kind);

            ui_states->interactable_tooltip_texts.clear();

            const auto* camera = singleton_reg.try_get<bn::camera_ptr>(singleton_entity);
            BN_ASSERT(camera);

            auto& text_gen = text_generators.get(INTERACTABLE_TOOLTIP_TEXT_FONT);

            const auto prev_color = text_generators.text_color(INTERACTABLE_TOOLTIP_TEXT_FONT);
            const auto prev_align = text_gen.alignment();
            const auto prev_priority = text_gen.bg_priority();
            const auto prev_cam = text_gen.camera();
            text_generators.set_text_color(INTERACTABLE_TOOLTIP_TEXT_FONT, INTERACTABLE_TOOLTIP_TEXT_COLOR);
            text_gen.set_alignment(INTERACTABLE_TOOLTIP_TEXT_ALIGN);
            text_gen.set_bg_priority(INTERACTABLE_TOOLTIP_TEXT_BG_PRIORITY);
            text_gen.set_camera(*camera);
            {
                const ldtk::gen::ingame_text_kind text =
                    ui_states->reserved_interactable_tooltip.value_or(interactable_infos.text);

                text_gen.generate_top_left(interactable_position, get_ingame_text(text, lang),
                                           ui_states->interactable_tooltip_texts);
            }
            text_gen.set_camera(prev_cam);
            text_gen.set_bg_priority(prev_priority);
            text_gen.set_alignment(prev_align);
            text_generators.set_text_color(INTERACTABLE_TOOLTIP_TEXT_FONT, prev_color);

            ui_states->last_nearby_interactable = nearby_interactable;
            ui_states->last_nearby_interactable_position = interactable_position;
        }
        // If nearby interactable moved, the tooltip text should chase it, too.
        else if (interactable_position != ui_states->last_nearby_interactable_position)
        {
            const auto diff = interactable_position - ui_states->last_nearby_interactable_position;
            for (auto& text_spr : ui_states->interactable_tooltip_texts)
                text_spr.set_position(text_spr.position() + diff);

            ui_states->last_nearby_interactable_position = interactable_position;
        }
    }
    else
    {
        ui_states->interactable_tooltip_texts.clear();

        ui_states->last_nearby_interactable = gba::entity_null;
    }

    ui_states->reserved_interactable_tooltip.reset();
}

} // namespace mc::gm::ecs::sys
