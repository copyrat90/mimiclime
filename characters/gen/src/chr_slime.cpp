// This file is auto generated!
// Exported by GBATool
// Version 1.0.0.0
// https://github.com/DarkKodKod/GBATool

#include "chr_slime.h"

namespace gbatool
{

static constexpr Chr_Slime::Animation animations[2] = {{0, 5, 0}, {8, 4, 0}};

static constexpr Chr_Slime::Frame frames[8] = {{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}};

static constexpr Chr_Slime::Sprite sprites[8] = {
    { &Chr_Slime::bnk_slime_0_slime_walk_0, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_0_slime_walk_1, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_0_slime_walk_2, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_0_slime_walk_3, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_0_slime_walk_4, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_0_slime_walk_5, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_0_slime_walk_6, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_0_slime_walk_7, 0, -15, 0 }
};

static constexpr bn::span<const Character::Collisions> idle_collisions;

static constexpr Character::Collisions::RelativeRect walk_frame_0_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -13, 18, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_frame_0_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_frame_0_mask_hurtbox_collisions,
};

static constexpr Character::Collisions walk_frame_0_collisions(walk_frame_0_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_frame_1_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -13, 18, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_frame_1_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_frame_1_mask_hurtbox_collisions,
};

static constexpr Character::Collisions walk_frame_1_collisions(walk_frame_1_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_frame_2_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-8, -13, 18, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_frame_2_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_frame_2_mask_hurtbox_collisions,
};

static constexpr Character::Collisions walk_frame_2_collisions(walk_frame_2_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_frame_3_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-8, -13, 18, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_frame_3_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_frame_3_mask_hurtbox_collisions,
};

static constexpr Character::Collisions walk_frame_3_collisions(walk_frame_3_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_frame_4_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-8, -13, 18, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_frame_4_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_frame_4_mask_hurtbox_collisions,
};

static constexpr Character::Collisions walk_frame_4_collisions(walk_frame_4_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_frame_5_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-8, -13, 18, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_frame_5_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_frame_5_mask_hurtbox_collisions,
};

static constexpr Character::Collisions walk_frame_5_collisions(walk_frame_5_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_frame_6_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -13, 18, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_frame_6_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_frame_6_mask_hurtbox_collisions,
};

static constexpr Character::Collisions walk_frame_6_collisions(walk_frame_6_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_frame_7_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -13, 18, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_frame_7_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_frame_7_mask_hurtbox_collisions,
};

static constexpr Character::Collisions walk_frame_7_collisions(walk_frame_7_collisions_spans);

static constexpr const Character::Collisions walk_collisions[] = {
    walk_frame_0_collisions,
    walk_frame_1_collisions,
    walk_frame_2_collisions,
    walk_frame_3_collisions,
    walk_frame_4_collisions,
    walk_frame_5_collisions,
    walk_frame_6_collisions,
    walk_frame_7_collisions,
};

static constexpr const bn::span<const Character::Collisions> collisions[] = {
    idle_collisions,
    walk_collisions,
};

Chr_Slime::Chr_Slime() :
    Character(
        bn::span<const Chr_Slime::Animation>(animations, 2), 
        bn::span<const Chr_Slime::Frame>(frames, 8), 
        bn::span<const Chr_Slime::Sprite>(sprites, 8),
        collisions, _frameSprites
    )
{
}

}
