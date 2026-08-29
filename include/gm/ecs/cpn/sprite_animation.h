#pragma once

#include <cstdint>

namespace bn
{
class sprite_ptr;
} // namespace bn

namespace mc::gm::cfg
{
struct sprite_animation_info;
}
namespace mc::gm::cfg::gen
{
enum class sprite_kind;
}

namespace mc::gm::ecs::cpn
{

struct sprite_animation final
{
    cfg::gen::sprite_kind sprite_kind;
    const cfg::sprite_animation_info* info;
    std::uint16_t current_wait_updates;
    std::uint16_t current_graphics_indexes_index;

    bool paused;

    sprite_animation(bn::sprite_ptr&, cfg::gen::sprite_kind, const cfg::sprite_animation_info&, bool done_ = false, bool paused_ = false);

    void reset(bn::sprite_ptr&, cfg::gen::sprite_kind, const cfg::sprite_animation_info&, bool done_ = false);

    bool done() const;

    std::uint16_t current_graphics_index() const;
};

} // namespace mc::gm::ecs::cpn
