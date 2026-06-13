#pragma once

#include "scn/scene.h"

#include <bn_regular_bg_ptr.h>

#include <cstdint>

namespace mc::scn
{

class splash final : public scene
{
public:
    splash(scene_context&);

public:
    bool update() override;

private:
    void update_fade_in();
    void update_waiting();
    void update_fade_out();

    void transit_to_waiting();
    void transit_to_fade_out();

private:
    enum class state : std::uint8_t
    {
        FADE_IN,
        WAITING,
        FADE_OUT,
    };

private:
    bn::regular_bg_ptr _bg;

    state _state = state::FADE_IN;
    bool _key_ever_pressed = false;

    std::uint16_t _waiting_current_update = 0;
};

} // namespace mc::scn
