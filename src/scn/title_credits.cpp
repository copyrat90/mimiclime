#include "scn/title_credits.h"

#include "scn/scene_context.h"
#include "scn/scene_stack.h"
#include "ut/configs.h"

#include <bn_keypad.h>

namespace mc::scn
{

namespace
{

constexpr auto FONT = ut::text_generators::font::GALMURI_11;

constexpr bn::fixed HEADING_X = 30;
constexpr bn::fixed AUTHOR_X = 50;

constexpr bn::fixed_point PROGRAMMING_POS(HEADING_X, 25);
constexpr bn::fixed_point PROGRAMMING_AUTHOR_POS(AUTHOR_X, 47);

constexpr bn::fixed_point GRAPHICS_POS(HEADING_X, 90);
constexpr bn::fixed_point GRAPHICS_AUTHOR_POS(AUTHOR_X, 112);

constexpr auto TITLE_CREDITS_TEXTS =
    ut::get_config_entity(ldtk::gen::entity_ident::system_texts)
        .get_field(ldtk::gen::entity_field_ident::ENTITY_system_texts_FIELD_title_credits)
        .get<bn::span<const bn::string_view>>();

} // namespace

title_credits::title_credits(scene_context& ctx) : scene(ctx)
{
    auto& gens = ctx.text_generators();
    auto& gen = gens.get(FONT);

    const auto lang = ctx.config_save().language();

    const auto prev_alignment = gen.alignment();
    gen.set_left_alignment();
    {
        gen.generate_top_left(PROGRAMMING_POS, TITLE_CREDITS_TEXTS[2 + 2 * static_cast<int>(lang)], _text_sprites);
        gen.generate_top_left(PROGRAMMING_AUTHOR_POS, TITLE_CREDITS_TEXTS[0], _text_sprites);
        gen.generate_top_left(GRAPHICS_POS, TITLE_CREDITS_TEXTS[2 + 2 * static_cast<int>(lang) + 1], _text_sprites);
        gen.generate_top_left(GRAPHICS_AUTHOR_POS, TITLE_CREDITS_TEXTS[1], _text_sprites);
    }
    gen.set_alignment(prev_alignment);
}

bool title_credits::update()
{
    if (bn::keypad::a_pressed() || bn::keypad::b_pressed())
        context().stack().reserve_replace_top_with_delay<title_options>(ldtk::gen::title_options_menu::credits,
                                                                        context());

    return false;
}

} // namespace mc::scn
