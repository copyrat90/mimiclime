#include "gm/ecs/sys/ui_update.h"

#include "gm/cfg/species_infos.h"
#include "gm/ecs/ut/find_critter.h"
#include "gm/ingame_texts.h"
#include "txt/critter_ui_texts.h"
#include "ut/enum_utils.h"
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

constexpr auto DEVOUR_TOOLTIP_TEXT_FONT = mc::ut::text_generators::font::GALMURI_7;
constexpr int DEVOUR_TOOLTIP_TEXT_BG_PRIORITY = UI_BG_PRIORITY + 1;
constexpr bn::color DEVOUR_TOOLTIP_TEXT_COLOR = bn::colors::cyan;
constexpr auto DEVOUR_TOOLTIP_TEXT_ALIGN = bn::sprite_text_generator::alignment_type::CENTER;

} // namespace

void ui_update(singleton_registry& singleton_reg, const gba::entity singleton_entity, actor_registry& actor_reg,
               mc::ut::text_generators& text_generators, const ldtk::gen::lang lang)
{
    auto* ui_states = singleton_reg.try_get<cpn::ui_states>(singleton_entity);
    BN_ASSERT(ui_states);
    const auto* actors_of_interest = singleton_reg.try_get<cpn::actors_of_interest>(singleton_entity);
    BN_ASSERT(actors_of_interest);

    const gba::entity status_mob = actors_of_interest->status_mob;
    const gba::entity nearby_devourable_mob = actors_of_interest->nearby_devourable_mob;
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
            const auto species_name = mc::ut::enum_to_string(player_critter_states->species());
            const auto current_hp = static_cast<int>(player_critter_states->hp());
            const auto max_hp = cfg::species_infos::get(player_critter_states->species()).hp();

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
                const auto species_name = mc::ut::enum_to_string(critter_states->species());
                const auto current_hp = static_cast<int>(critter_states->hp());
                const auto max_hp = cfg::species_infos::get(critter_states->species()).hp();

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

    // Devour text on top of nearby devourable mob
    if (actor_reg.valid(nearby_devourable_mob) && player_critter_states->can_devour())
    {
        const auto* mob_sprite = actor_reg.try_get<bn::sprite_ptr>(nearby_devourable_mob);
        BN_ASSERT(mob_sprite);
        const auto mob_position =
            mob_sprite->top_left_position() +
            bn::fixed_point(mob_sprite->shape_size().width() / 2, mob_sprite->shape_size().height() / 2);

        if (nearby_devourable_mob != ui_states->last_nearby_devourable_mob)
        {
            ui_states->devour_tooltip_texts.clear();

            const auto* camera = singleton_reg.try_get<bn::camera_ptr>(singleton_entity);
            BN_ASSERT(camera);

            auto& text_gen = text_generators.get(DEVOUR_TOOLTIP_TEXT_FONT);

            const auto prev_color = text_generators.text_color(DEVOUR_TOOLTIP_TEXT_FONT);
            const auto prev_align = text_gen.alignment();
            const auto prev_priority = text_gen.bg_priority();
            const auto prev_cam = text_gen.camera();
            text_generators.set_text_color(DEVOUR_TOOLTIP_TEXT_FONT, DEVOUR_TOOLTIP_TEXT_COLOR);
            text_gen.set_alignment(DEVOUR_TOOLTIP_TEXT_ALIGN);
            text_gen.set_bg_priority(DEVOUR_TOOLTIP_TEXT_BG_PRIORITY);
            text_gen.set_camera(*camera);
            {
                text_gen.generate_top_left(mob_position,
                                           get_ingame_text(ldtk::gen::ingame_text_kind::tooltip_devour, lang),
                                           ui_states->devour_tooltip_texts);
            }
            text_gen.set_camera(prev_cam);
            text_gen.set_bg_priority(prev_priority);
            text_gen.set_alignment(prev_align);
            text_generators.set_text_color(DEVOUR_TOOLTIP_TEXT_FONT, prev_color);

            ui_states->last_nearby_devourable_mob = nearby_devourable_mob;
            ui_states->last_nearby_devourable_mob_position = mob_position;
        }
        // If devourable mob moved, the tooltip text should chase it, too.
        else if (mob_position != ui_states->last_nearby_devourable_mob_position)
        {
            const auto diff = mob_position - ui_states->last_nearby_devourable_mob_position;
            for (auto& text_spr : ui_states->devour_tooltip_texts)
                text_spr.set_position(text_spr.position() + diff);

            ui_states->last_nearby_devourable_mob_position = mob_position;
        }
    }
    else
    {
        ui_states->devour_tooltip_texts.clear();

        ui_states->last_nearby_devourable_mob = gba::entity_null;
    }
}

} // namespace mc::gm::ecs::sys
