#include "gm/ecs/cpn/sprite_flicker.h"

namespace mc::gm::ecs::cpn
{

sprite_flicker::sprite_flicker(decltype(destroy_countdown) destroy_countdown_, decltype(toggle_ticks) toggle_ticks_)
    : destroy_countdown(destroy_countdown_), toggle_ticks(toggle_ticks_), toggle_countdown(1)
{
}

} // namespace mc::gm::ecs::cpn
