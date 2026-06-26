// This file is auto generated!
// Exported by GBATool
// Version 1.0.0.0
// https://github.com/DarkKodKod/GBATool

#include "chr_fireball.h"

namespace gbatool
{

static constexpr Chr_Fireball::Animation animations[1] = {{4, 4, 0}};

static constexpr Chr_Fireball::Frame frames[4] = {{0, 0}, {1, 1}, {2, 2}, {3, 3}};

static constexpr Chr_Fireball::Sprite sprites[4] = {
    { &Chr_Fireball::bnk_fireball_0_fireball_fly_0, 0, 0, 0 },
    { &Chr_Fireball::bnk_fireball_0_fireball_fly_1, 0, 0, 0 },
    { &Chr_Fireball::bnk_fireball_0_fireball_fly_2, 0, 0, 0 },
    { &Chr_Fireball::bnk_fireball_0_fireball_fly_3, 0, 0, 0 }
};

static constexpr Character::Collisions::RelativeRect rotate_frame_0_mask_hitbox_collisions[] = {
    Character::Collisions::RelativeRect(-2, -2, 4, 4),
};

static constexpr Character::Collisions::RelativeRect rotate_frame_0_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-3, -3, 6, 6),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> rotate_frame_0_collisions_spans[] = {
    rotate_frame_0_mask_hitbox_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
    rotate_frame_0_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions rotate_frame_0_collisions(rotate_frame_0_collisions_spans);

static constexpr Character::Collisions::RelativeRect rotate_frame_1_mask_hitbox_collisions[] = {
    Character::Collisions::RelativeRect(-2, -2, 4, 4),
};

static constexpr Character::Collisions::RelativeRect rotate_frame_1_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-3, -3, 6, 6),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> rotate_frame_1_collisions_spans[] = {
    rotate_frame_1_mask_hitbox_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
    rotate_frame_1_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions rotate_frame_1_collisions(rotate_frame_1_collisions_spans);

static constexpr Character::Collisions::RelativeRect rotate_frame_2_mask_hitbox_collisions[] = {
    Character::Collisions::RelativeRect(-2, -2, 4, 4),
};

static constexpr Character::Collisions::RelativeRect rotate_frame_2_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-3, -3, 6, 6),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> rotate_frame_2_collisions_spans[] = {
    rotate_frame_2_mask_hitbox_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
    rotate_frame_2_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions rotate_frame_2_collisions(rotate_frame_2_collisions_spans);

static constexpr Character::Collisions::RelativeRect rotate_frame_3_mask_hitbox_collisions[] = {
    Character::Collisions::RelativeRect(-2, -2, 4, 4),
};

static constexpr Character::Collisions::RelativeRect rotate_frame_3_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-3, -3, 6, 6),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> rotate_frame_3_collisions_spans[] = {
    rotate_frame_3_mask_hitbox_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
    rotate_frame_3_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions rotate_frame_3_collisions(rotate_frame_3_collisions_spans);

static constexpr const Character::Collisions rotate_collisions[] = {
    rotate_frame_0_collisions,
    rotate_frame_1_collisions,
    rotate_frame_2_collisions,
    rotate_frame_3_collisions,
};

static constexpr const bn::span<const Character::Collisions> collisions[] = {
    rotate_collisions,
};

Chr_Fireball::Chr_Fireball() :
    Character(
        bn::span<const Chr_Fireball::Animation>(animations, 1), 
        bn::span<const Chr_Fireball::Frame>(frames, 4), 
        bn::span<const Chr_Fireball::Sprite>(sprites, 4),
        collisions, _frameSprites, 0
    )
{
}

}
