#pragma once

#include "gm/cfg/box_data.h"
#include "gm/cfg/projectile_data.h"

#include <bn_span.h>
#include <bn_sprite_item.h>

namespace mc::gm::cfg::gen
{
enum class sprite_kind;
}

namespace mc::gm::cfg
{

struct sprite_frame_datas final
{
    bn::span<const box_data> wallboxes;
    bn::span<const box_data> hurtboxes;
    bn::span<const box_data> hitboxes;
    bn::span<const projectile_data> projectiles;
};

class sprite_datas final
{
private:
    gen::sprite_kind _kind;

    const bn::sprite_item& _sprite_item;

    bn::span<const sprite_frame_datas> _frames;

public:
    static constexpr auto get(gen::sprite_kind) -> const sprite_datas&;

public:
    constexpr sprite_datas(gen::sprite_kind kind, const bn::sprite_item& sprite_item, decltype(_frames) frames) : _kind(kind), _sprite_item(sprite_item), _frames(frames)
    {
    }

    constexpr auto kind() const -> decltype(_kind)
    {
        return _kind;
    }

    constexpr auto sprite_item() const -> decltype((_sprite_item))
    {
        return _sprite_item;
    }

    constexpr auto frame(unsigned frame_index) const -> decltype(_frames)::const_reference
    {
        BN_ASSERT(frame_index < static_cast<unsigned>(_frames.size()), "OOB index: ", frame_index, " (max ", _frames.size() - 1, ")");

        return _frames[frame_index];
    }
};

} // namespace mc::gm::cfg

#include "gen/sprite_datas.inl"
