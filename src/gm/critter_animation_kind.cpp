#include "gm/critter_animation_kind.h"

#include "gm/direction.h"

#include <type_traits>

namespace mc::gm
{

auto get_critter_animation_id(critter_animation_kind anim_kind, direction dir_4) -> critter_animation_id
{
    BN_ASSERT(dir_4 == direction::UP || dir_4 == direction::RIGHT || dir_4 == direction::DOWN ||
                  dir_4 == direction::LEFT,
              "Invalid direction: ", static_cast<int>(dir_4));

    return static_cast<critter_animation_id>(4 * static_cast<std::underlying_type_t<decltype(anim_kind)>>(anim_kind) +
                                             static_cast<std::underlying_type_t<decltype(dir_4)>>(dir_4) / 2);
}

} // namespace mc::gm
