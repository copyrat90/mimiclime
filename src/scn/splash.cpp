#include "scn/splash.h"

#include "scn/scene_context.h"
#include "scn/scene_stack.h"
#include "scn/title.h"

#include "ibn_transitions.h"

#include <bn_assert.h>
#include <bn_dmg_music.h>
#include <bn_keypad.h>
#include <bn_music.h>
#include <bn_regular_bg_builder.h>

#include <cstdint>

#include "bn_regular_bg_items_gba_jam_2026_logo.h"

namespace mc::scn
{

namespace
{

constexpr auto TRANSITION_KINDS = ibn::transitions::kinds::TRANSPARENCY;

constexpr int FADE_IN_DURATION_UPDATES = 60;
constexpr int WAITING_DURATION_UPDATES = 240;
constexpr int FADE_OUT_DURATION_UPDATES = 60;

auto create_bg() -> bn::regular_bg_ptr
{
    static constexpr const auto& splash = bn::regular_bg_items::gba_jam_2026_logo;

    return bn::regular_bg_builder(splash).set_blending_top_enabled(true).release_build();
}

} // namespace

splash::splash(scene_context& ctx) : scene(ctx), _bg(create_bg())
{
    bn::music::stop();
    bn::dmg_music::stop();

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
        _bg.set_visible(false);
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
