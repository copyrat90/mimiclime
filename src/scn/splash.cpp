#include "scn/splash.h"

#include "scn/scene_context.h"
#include "scn/scene_stack.h"
#include "scn/title.h"

#include "ibn_transitions.h"

#include <bn_assert.h>
#include <bn_dmg_music.h>
#include <bn_keypad.h>
#include <bn_music.h>

#include <cstdint>

namespace mc::scn
{

namespace
{

constexpr auto TRANSITION_KINDS = ibn::transitions::kinds::TRANSPARENCY;

constexpr int FADE_IN_DURATION_UPDATES = 60;
constexpr int WAITING_DURATION_UPDATES = 240;
constexpr int FADE_OUT_DURATION_UPDATES = 60;

} // namespace

splash::splash(scene_context& ctx) : scene(ctx)
{
    bn::music::stop();
    bn::dmg_music::stop();

    auto& text_gens = ctx.text_generators();
    auto& text_gen_small = text_gens.get(ut::text_generators::font::GALMURI_7);
    auto& text_gen_big = text_gens.get(ut::text_generators::font::GALMURI_11_BOLD);

    const bool prev_blending_enabled_small = text_gen_small.blending_enabled();
    const bool prev_blending_enabled_big = text_gen_big.blending_enabled();
    const auto prev_align_small = text_gen_small.alignment();
    const auto prev_align_big = text_gen_big.alignment();
    text_gen_small.set_blending_enabled(true);
    text_gen_big.set_blending_enabled(true);
    text_gen_small.set_center_alignment();
    text_gen_big.set_center_alignment();

    text_gen_small.generate(0, -20, "A submission to", _text_sprites);
    text_gen_big.generate(0, -5, "GBA Jam 2026", _text_sprites);
    text_gen_small.generate(0, 20, "https://copyrat90.itch.io/mimiclime", _text_sprites);

    text_gen_small.set_blending_enabled(prev_blending_enabled_small);
    text_gen_big.set_blending_enabled(prev_blending_enabled_big);
    text_gen_small.set_alignment(prev_align_small);
    text_gen_big.set_alignment(prev_align_big);

    auto& transitions = context().transitions();
    transitions.set_alpha(TRANSITION_KINDS, 1);
    transitions.start(TRANSITION_KINDS, FADE_IN_DURATION_UPDATES, 0);
}

bool splash::update()
{
    _key_ever_pressed |= bn::keypad::any_pressed();

    switch (_state)
    {
    case state::FADE_IN:
        update_fade_in();
        break;
    case state::WAITING:
        update_waiting();
        break;
    case state::FADE_OUT:
        update_fade_out();
        break;
    default:
        BN_ERROR("Invalid state: ", (int)_state);
    }

    return false;
}

void splash::update_fade_in()
{
    if (context().transitions().done(TRANSITION_KINDS))
    {
        if (_key_ever_pressed)
            transit_to_fade_out();
        else
            transit_to_waiting();
    }
}

void splash::update_waiting()
{
    if (_key_ever_pressed || ++_waiting_current_update == WAITING_DURATION_UPDATES)
        transit_to_fade_out();
}

void splash::update_fade_out()
{
    if (context().transitions().done())
    {
        _text_sprites.clear();
        context().transitions().set_alpha(TRANSITION_KINDS, 0);

        auto& scene_stack = context().stack();
        scene_stack.reserve_replace_top_with_delay<title>(ldtk::gen::title_menu::start, context());
    }
}

void splash::transit_to_waiting()
{
    _state = state::WAITING;
}

void splash::transit_to_fade_out()
{
    context().transitions().start(TRANSITION_KINDS, FADE_OUT_DURATION_UPDATES, 1);

    _state = state::FADE_OUT;
}

} // namespace mc::scn
