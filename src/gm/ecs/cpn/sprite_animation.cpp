#include "gm/ecs/cpn/sprite_animation.h"

#include "gm/cfg/sprite_animation_info.h"
#include "gm/cfg/sprite_datas.h"

#include <bn_sprite_builder.h>
#include <bn_sprite_ptr.h>

namespace mc::gm::ecs::cpn
{

sprite_animation::sprite_animation(bn::sprite_ptr& sprite, cfg::gen::sprite_kind sprite_kind_,
                                   const cfg::sprite_animation_info& info_)
    : sprite_kind(sprite_kind_)
{
    reset(sprite, sprite_kind_, info_);
}

void sprite_animation::reset(bn::sprite_ptr& sprite, cfg::gen::sprite_kind sprite_kind_,
                             const cfg::sprite_animation_info& info_)
{
    const auto& sprite_item = cfg::sprite_datas::get(sprite_kind_).sprite_item();

    if (sprite_kind_ == this->sprite_kind)
    {
        sprite.set_tiles(sprite_item.tiles_item(), info_.graphics_indexes[0]);
        sprite.set_horizontal_flip(info_.horizontal_flip);
        sprite.set_vertical_flip(info_.vertical_flip);
    }
    else
    {
        sprite = bn::sprite_builder(sprite_item, info_.graphics_indexes[0])
                     .set_camera(sprite.camera())
                     .set_position(sprite.position())
                     .set_blending_enabled(true)
                     .set_horizontal_flip(info_.horizontal_flip)
                     .set_vertical_flip(info_.vertical_flip)
                     .release_build();
    }

    this->info = &info_;
    this->sprite_kind = sprite_kind_;
    this->current_wait_updates = info_.wait_updates;
    this->current_graphics_indexes_index = 0;
}

bool sprite_animation::done() const
{
    BN_ASSERT(this->info);

    const auto graphics_indexes_size = static_cast<unsigned>(this->info->graphics_indexes.size());
    return !this->info->forever && this->current_graphics_indexes_index >= graphics_indexes_size - 1 &&
           this->current_wait_updates == 0;
}

std::uint16_t sprite_animation::current_graphics_index() const
{
    BN_ASSERT(this->info);
    [[maybe_unused]] const auto graphics_indexes_size = static_cast<unsigned>(this->info->graphics_indexes.size());
    BN_ASSERT(this->current_graphics_indexes_index < graphics_indexes_size,
              "Invalid index: ", this->current_graphics_indexes_index, " (max ", graphics_indexes_size - 1, ")");

    return this->info->graphics_indexes[this->current_graphics_indexes_index];
}

} // namespace mc::gm::ecs::cpn
