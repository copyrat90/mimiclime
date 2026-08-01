#include "gm/ecs/cpn/sprite_animation.h"

#include "gm/cfg/sprite_animation_info.h"

#include <bn_sprite_ptr.h>

namespace mc::gm::ecs::cpn
{

sprite_animation::sprite_animation(bn::sprite_ptr& sprite, const bn::sprite_tiles_item& tiles_item_,
                                   const cfg::sprite_animation_info& info_)
{
    reset(sprite, tiles_item_, info_);
}

void sprite_animation::reset(bn::sprite_ptr& sprite, const bn::sprite_tiles_item& tiles_item_,
                             const cfg::sprite_animation_info& info_)
{
    this->info = &info_;
    this->tiles_item = &tiles_item_;
    this->current_wait_updates = info_.wait_updates;
    this->current_graphics_indexes_index = 0;

    sprite.set_horizontal_flip(info_.horizontal_flip);
    sprite.set_vertical_flip(info_.vertical_flip);
    sprite.set_tiles(tiles_item_, info_.graphics_indexes[this->current_graphics_indexes_index]);
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
