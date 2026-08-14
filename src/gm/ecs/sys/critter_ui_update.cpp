#include "gm/ecs/sys/critter_ui_update.h"

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

constexpr bn::fixed_point PLAYER_UI_TEXT_POS(2, 2);
constexpr bn::color PLAYER_UI_TEXT_COLOR = bn::colors::magenta;
constexpr auto PLAYER_UI_TEXT_ALIGN = bn::sprite_text_generator::alignment_type::LEFT;

constexpr bn::fixed_point MOB_UI_TEXT_POS(bn::display::width() / 2, bn::display::height() - 12);
constexpr bn::color MOB_UI_TEXT_COLOR = bn::colors::red;
constexpr auto MOB_UI_TEXT_ALIGN = bn::sprite_text_generator::alignment_type::CENTER;

} // namespace

void critter_ui_update(singleton_registry& singleton_reg, const gba::entity singleton_entity, actor_registry& actor_reg,
                       mc::ut::text_generators& text_generators)
{
    auto* ui_states = singleton_reg.try_get<cpn::ui_states>(singleton_entity);
    BN_ASSERT(ui_states);
    const auto* focused_actor_component = singleton_reg.try_get<cpn::focused_actor>(singleton_entity);
    BN_ASSERT(focused_actor_component);
    const gba::entity focused_actor = focused_actor_component->actor;

    bool focused_mob_found = false;

    actor_reg.view<cpn::critter_states>().each([&](const gba::entity critter, cpn::critter_states& critter_states) {
        // Player
        if (critter_states.is_player())
        {
            if (critter_states.species() != ui_states->last_player_species ||
                critter_states.hp() != ui_states->last_player_hp)
            {
                ui_states->player_texts.clear();

                auto& text_gen = text_generators.get(UI_TEXT_FONT);

                const auto prev_color = text_generators.text_color(UI_TEXT_FONT);
                const auto prev_align = text_gen.alignment();
                const auto prev_priority = text_gen.bg_priority();
                text_generators.set_text_color(UI_TEXT_FONT, PLAYER_UI_TEXT_COLOR);
                text_gen.set_left_alignment();
                text_gen.set_bg_priority(UI_BG_PRIORITY);
                {
                    auto str =
                        bn::format<64>(txt::CRITTER_UI_TEXT_FMT, mc::ut::enum_to_string(critter_states.species()),
                                       static_cast<int>(critter_states.hp()));
                    text_gen.generate_top_left(PLAYER_UI_TEXT_POS, str, ui_states->player_texts);
                }
                text_gen.set_bg_priority(prev_priority);
                text_gen.set_alignment(prev_align);
                text_generators.set_text_color(UI_TEXT_FONT, prev_color);

                ui_states->last_player_species = critter_states.species();
                ui_states->last_player_hp = critter_states.hp();
            }
        }

        // Mob on focus
        if (critter == focused_actor)
        {
            focused_mob_found = true;

            if (critter_states.species() != ui_states->last_mob_species ||
                critter_states.hp() != ui_states->last_mob_hp)
            {
                ui_states->mob_texts.clear();

                auto& text_gen = text_generators.get(UI_TEXT_FONT);

                const auto prev_color = text_generators.text_color(UI_TEXT_FONT);
                const auto prev_align = text_gen.alignment();
                const auto prev_priority = text_gen.bg_priority();
                text_generators.set_text_color(UI_TEXT_FONT, MOB_UI_TEXT_COLOR);
                text_gen.set_center_alignment();
                text_gen.set_bg_priority(UI_BG_PRIORITY);
                {
                    auto str =
                        bn::format<64>(txt::CRITTER_UI_TEXT_FMT, mc::ut::enum_to_string(critter_states.species()),
                                       static_cast<int>(critter_states.hp()));
                    text_gen.generate_top_left(MOB_UI_TEXT_POS, str, ui_states->mob_texts);
                }
                text_gen.set_bg_priority(prev_priority);
                text_gen.set_alignment(prev_align);
                text_generators.set_text_color(UI_TEXT_FONT, prev_color);

                ui_states->last_mob_species = critter_states.species();
                ui_states->last_mob_hp = critter_states.hp();
            }
        }
    });

    if (!focused_mob_found)
    {
        ui_states->mob_texts.clear();

        ui_states->last_mob_species = ldtk::gen::species_kind::slime;
        ui_states->last_mob_hp = 0;
    }
}

} // namespace mc::gm::ecs::sys
