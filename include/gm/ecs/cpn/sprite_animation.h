#pragma once

#include <cstdint>

namespace bn
{
class sprite_ptr;
class sprite_tiles_item;
} // namespace bn

namespace mc::gm::cfg
{
struct sprite_animation_info;
}

namespace mc::gm::ecs::cpn
{

struct sprite_animation final
{
    const bn::sprite_tiles_item* tiles_item;
    const cfg::sprite_animation_info* info;
    std::uint16_t current_wait_updates;
    std::uint16_t current_graphics_indexes_index;

    sprite_animation(bn::sprite_ptr&, const bn::sprite_tiles_item&, const cfg::sprite_animation_info&);

    void reset(bn::sprite_ptr&, const bn::sprite_tiles_item&, const cfg::sprite_animation_info&);

    bool done() const;

    std::uint16_t current_graphics_index() const;
};

} // namespace mc::gm::ecs::cpn
