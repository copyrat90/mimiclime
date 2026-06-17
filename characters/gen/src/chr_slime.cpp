// This file is auto generated!
// Time-stamp 2026-6-17 20:05:51
// Exported by GBATool
// Version 1.0.0.0
// https://github.com/DarkKodKod/GBATool

#include "chr_slime.h"

namespace gbatool
{

static constexpr Chr_Slime::Animation animations[8] = {{4, 6, 0}, {8, 2, 0}, {8, 2, 0}, {8, 2, 0}, {4, 4, 1}, {4, 4, 1}, {4, 4, 1}, {4, 4, 1}};

static constexpr Chr_Slime::Frame frames[44] = {{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10}, {11, 11}, {12, 12}, {13, 13}, {14, 14}, {15, 15}, {16, 16}, {17, 17}, {18, 18}, {19, 19}, {20, 20}, {21, 21}, {22, 22}, {23, 23}, {24, 24}, {25, 25}, {26, 26}, {27, 27}, {28, 28}, {29, 29}, {30, 30}, {31, 31}, {32, 32}, {33, 33}, {34, 34}, {35, 35}, {36, 36}, {37, 37}, {38, 38}, {39, 39}, {40, 40}, {41, 41}, {42, 42}, {43, 43}};

static constexpr Chr_Slime::Sprite sprites[44] = {
    { &Chr_Slime::bnk_slime_2_slime_idle_0, 0, -14, 0 },
    { &Chr_Slime::bnk_slime_2_slime_idle_1, 0, -14, 0 },
    { &Chr_Slime::bnk_slime_2_slime_idle_2, 0, -14, 0 },
    { &Chr_Slime::bnk_slime_2_slime_idle_1, 0, -14, 0 },
    { &Chr_Slime::bnk_slime_0_slime_walk_0, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_0_slime_walk_1, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_0_slime_walk_2, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_0_slime_walk_3, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_0_slime_walk_4, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_0_slime_walk_5, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_0_slime_walk_6, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_0_slime_walk_7, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_0, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_1, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_2, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_3, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_4, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_5, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_6, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_7, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_7, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_6, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_5, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_4, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_3, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_2, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_1, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_0, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_3_slime_tackle_north_0, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_3_slime_tackle_north_1, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_3_slime_tackle_north_2, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_3_slime_tackle_north_3, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_3_slime_tackle_south_0, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_3_slime_tackle_south_1, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_3_slime_tackle_south_2, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_3_slime_tackle_south_3, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_3_slime_tackle_east_0, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_3_slime_tackle_east_1, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_3_slime_tackle_east_2, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_3_slime_tackle_east_3, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_3_slime_tackle_east_0, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_3_slime_tackle_east_1, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_3_slime_tackle_east_2, 0, -15, 0 },
    { &Chr_Slime::bnk_slime_3_slime_tackle_east_3, 0, -15, 0 }
};

static constexpr Character::Collisions::RelativeRect idle_frame_0_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -11, 18, 8),
};

static constexpr Character::Collisions::RelativeRect idle_frame_0_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> idle_frame_0_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    idle_frame_0_mask_hurtbox_collisions,
    idle_frame_0_mask_custom_0_collisions,
};

static constexpr Character::Collisions idle_frame_0_collisions(idle_frame_0_collisions_spans);

static constexpr Character::Collisions::RelativeRect idle_frame_1_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -11, 18, 8),
};

static constexpr Character::Collisions::RelativeRect idle_frame_1_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> idle_frame_1_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    idle_frame_1_mask_hurtbox_collisions,
    idle_frame_1_mask_custom_0_collisions,
};

static constexpr Character::Collisions idle_frame_1_collisions(idle_frame_1_collisions_spans);

static constexpr Character::Collisions::RelativeRect idle_frame_2_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -10, 18, 7),
};

static constexpr Character::Collisions::RelativeRect idle_frame_2_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> idle_frame_2_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    idle_frame_2_mask_hurtbox_collisions,
    idle_frame_2_mask_custom_0_collisions,
};

static constexpr Character::Collisions idle_frame_2_collisions(idle_frame_2_collisions_spans);

static constexpr Character::Collisions::RelativeRect idle_frame_3_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -11, 18, 8),
};

static constexpr Character::Collisions::RelativeRect idle_frame_3_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> idle_frame_3_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    idle_frame_3_mask_hurtbox_collisions,
    idle_frame_3_mask_custom_0_collisions,
};

static constexpr Character::Collisions idle_frame_3_collisions(idle_frame_3_collisions_spans);

static constexpr const Character::Collisions idle_collisions[] = {
    idle_frame_0_collisions,
    idle_frame_1_collisions,
    idle_frame_2_collisions,
    idle_frame_3_collisions,
};

static constexpr Character::Collisions::RelativeRect walk_frame_0_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -12, 18, 8),
};

static constexpr Character::Collisions::RelativeRect walk_frame_0_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_frame_0_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_frame_0_mask_hurtbox_collisions,
    walk_frame_0_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_frame_0_collisions(walk_frame_0_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_frame_1_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -12, 18, 8),
};

static constexpr Character::Collisions::RelativeRect walk_frame_1_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_frame_1_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_frame_1_mask_hurtbox_collisions,
    walk_frame_1_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_frame_1_collisions(walk_frame_1_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_frame_2_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-8, -12, 17, 8),
};

static constexpr Character::Collisions::RelativeRect walk_frame_2_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_frame_2_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_frame_2_mask_hurtbox_collisions,
    walk_frame_2_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_frame_2_collisions(walk_frame_2_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_frame_3_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-8, -12, 17, 8),
};

static constexpr Character::Collisions::RelativeRect walk_frame_3_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_frame_3_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_frame_3_mask_hurtbox_collisions,
    walk_frame_3_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_frame_3_collisions(walk_frame_3_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_frame_4_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-8, -12, 17, 8),
};

static constexpr Character::Collisions::RelativeRect walk_frame_4_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_frame_4_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_frame_4_mask_hurtbox_collisions,
    walk_frame_4_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_frame_4_collisions(walk_frame_4_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_frame_5_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-7, -12, 17, 8),
};

static constexpr Character::Collisions::RelativeRect walk_frame_5_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_frame_5_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_frame_5_mask_hurtbox_collisions,
    walk_frame_5_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_frame_5_collisions(walk_frame_5_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_frame_6_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-8, -12, 17, 8),
};

static constexpr Character::Collisions::RelativeRect walk_frame_6_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_frame_6_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_frame_6_mask_hurtbox_collisions,
    walk_frame_6_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_frame_6_collisions(walk_frame_6_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_frame_7_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-8, -12, 17, 8),
};

static constexpr Character::Collisions::RelativeRect walk_frame_7_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_frame_7_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_frame_7_mask_hurtbox_collisions,
    walk_frame_7_mask_custom_0_collisions,
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

static constexpr Character::Collisions::RelativeRect walk_south_frame_0_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -12, 18, 8),
};

static constexpr Character::Collisions::RelativeRect walk_south_frame_0_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_south_frame_0_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_south_frame_0_mask_hurtbox_collisions,
    walk_south_frame_0_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_south_frame_0_collisions(walk_south_frame_0_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_south_frame_1_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -12, 18, 8),
};

static constexpr Character::Collisions::RelativeRect walk_south_frame_1_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_south_frame_1_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_south_frame_1_mask_hurtbox_collisions,
    walk_south_frame_1_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_south_frame_1_collisions(walk_south_frame_1_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_south_frame_2_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -12, 18, 8),
};

static constexpr Character::Collisions::RelativeRect walk_south_frame_2_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_south_frame_2_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_south_frame_2_mask_hurtbox_collisions,
    walk_south_frame_2_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_south_frame_2_collisions(walk_south_frame_2_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_south_frame_3_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -12, 18, 8),
};

static constexpr Character::Collisions::RelativeRect walk_south_frame_3_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_south_frame_3_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_south_frame_3_mask_hurtbox_collisions,
    walk_south_frame_3_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_south_frame_3_collisions(walk_south_frame_3_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_south_frame_4_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -12, 18, 8),
};

static constexpr Character::Collisions::RelativeRect walk_south_frame_4_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_south_frame_4_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_south_frame_4_mask_hurtbox_collisions,
    walk_south_frame_4_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_south_frame_4_collisions(walk_south_frame_4_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_south_frame_5_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -13, 18, 8),
};

static constexpr Character::Collisions::RelativeRect walk_south_frame_5_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_south_frame_5_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_south_frame_5_mask_hurtbox_collisions,
    walk_south_frame_5_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_south_frame_5_collisions(walk_south_frame_5_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_south_frame_6_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -13, 18, 8),
};

static constexpr Character::Collisions::RelativeRect walk_south_frame_6_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_south_frame_6_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_south_frame_6_mask_hurtbox_collisions,
    walk_south_frame_6_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_south_frame_6_collisions(walk_south_frame_6_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_south_frame_7_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -13, 18, 8),
};

static constexpr Character::Collisions::RelativeRect walk_south_frame_7_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_south_frame_7_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_south_frame_7_mask_hurtbox_collisions,
    walk_south_frame_7_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_south_frame_7_collisions(walk_south_frame_7_collisions_spans);

static constexpr const Character::Collisions walk_south_collisions[] = {
    walk_south_frame_0_collisions,
    walk_south_frame_1_collisions,
    walk_south_frame_2_collisions,
    walk_south_frame_3_collisions,
    walk_south_frame_4_collisions,
    walk_south_frame_5_collisions,
    walk_south_frame_6_collisions,
    walk_south_frame_7_collisions,
};

static constexpr Character::Collisions::RelativeRect walk_north_frame_0_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -13, 18, 8),
};

static constexpr Character::Collisions::RelativeRect walk_north_frame_0_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_north_frame_0_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_north_frame_0_mask_hurtbox_collisions,
    walk_north_frame_0_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_north_frame_0_collisions(walk_north_frame_0_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_north_frame_1_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -13, 18, 8),
};

static constexpr Character::Collisions::RelativeRect walk_north_frame_1_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_north_frame_1_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_north_frame_1_mask_hurtbox_collisions,
    walk_north_frame_1_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_north_frame_1_collisions(walk_north_frame_1_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_north_frame_2_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -13, 18, 8),
};

static constexpr Character::Collisions::RelativeRect walk_north_frame_2_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_north_frame_2_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_north_frame_2_mask_hurtbox_collisions,
    walk_north_frame_2_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_north_frame_2_collisions(walk_north_frame_2_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_north_frame_3_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -13, 18, 8),
};

static constexpr Character::Collisions::RelativeRect walk_north_frame_3_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_north_frame_3_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_north_frame_3_mask_hurtbox_collisions,
    walk_north_frame_3_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_north_frame_3_collisions(walk_north_frame_3_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_north_frame_4_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -13, 18, 9),
};

static constexpr Character::Collisions::RelativeRect walk_north_frame_4_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_north_frame_4_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_north_frame_4_mask_hurtbox_collisions,
    walk_north_frame_4_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_north_frame_4_collisions(walk_north_frame_4_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_north_frame_5_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -13, 18, 9),
};

static constexpr Character::Collisions::RelativeRect walk_north_frame_5_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_north_frame_5_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_north_frame_5_mask_hurtbox_collisions,
    walk_north_frame_5_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_north_frame_5_collisions(walk_north_frame_5_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_north_frame_6_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -13, 18, 9),
};

static constexpr Character::Collisions::RelativeRect walk_north_frame_6_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_north_frame_6_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_north_frame_6_mask_hurtbox_collisions,
    walk_north_frame_6_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_north_frame_6_collisions(walk_north_frame_6_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_north_frame_7_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -12, 18, 8),
};

static constexpr Character::Collisions::RelativeRect walk_north_frame_7_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_north_frame_7_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_north_frame_7_mask_hurtbox_collisions,
    walk_north_frame_7_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_north_frame_7_collisions(walk_north_frame_7_collisions_spans);

static constexpr const Character::Collisions walk_north_collisions[] = {
    walk_north_frame_0_collisions,
    walk_north_frame_1_collisions,
    walk_north_frame_2_collisions,
    walk_north_frame_3_collisions,
    walk_north_frame_4_collisions,
    walk_north_frame_5_collisions,
    walk_north_frame_6_collisions,
    walk_north_frame_7_collisions,
};

static constexpr Character::Collisions::RelativeRect tackle_north_frame_0_mask_hitbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -12, 18, 8),
};

static constexpr Character::Collisions::RelativeRect tackle_north_frame_0_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> tackle_north_frame_0_collisions_spans[] = {
    tackle_north_frame_0_mask_hitbox_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
    tackle_north_frame_0_mask_custom_0_collisions,
};

static constexpr Character::Collisions tackle_north_frame_0_collisions(tackle_north_frame_0_collisions_spans);

static constexpr Character::Collisions::RelativeRect tackle_north_frame_1_mask_hitbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -12, 18, 8),
};

static constexpr Character::Collisions::RelativeRect tackle_north_frame_1_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> tackle_north_frame_1_collisions_spans[] = {
    tackle_north_frame_1_mask_hitbox_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
    tackle_north_frame_1_mask_custom_0_collisions,
};

static constexpr Character::Collisions tackle_north_frame_1_collisions(tackle_north_frame_1_collisions_spans);

static constexpr Character::Collisions::RelativeRect tackle_north_frame_2_mask_hitbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -12, 18, 8),
};

static constexpr Character::Collisions::RelativeRect tackle_north_frame_2_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> tackle_north_frame_2_collisions_spans[] = {
    tackle_north_frame_2_mask_hitbox_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
    tackle_north_frame_2_mask_custom_0_collisions,
};

static constexpr Character::Collisions tackle_north_frame_2_collisions(tackle_north_frame_2_collisions_spans);

static constexpr Character::Collisions::RelativeRect tackle_north_frame_3_mask_hitbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -12, 18, 8),
};

static constexpr Character::Collisions::RelativeRect tackle_north_frame_3_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> tackle_north_frame_3_collisions_spans[] = {
    tackle_north_frame_3_mask_hitbox_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
    tackle_north_frame_3_mask_custom_0_collisions,
};

static constexpr Character::Collisions tackle_north_frame_3_collisions(tackle_north_frame_3_collisions_spans);

static constexpr const Character::Collisions tackle_north_collisions[] = {
    tackle_north_frame_0_collisions,
    tackle_north_frame_1_collisions,
    tackle_north_frame_2_collisions,
    tackle_north_frame_3_collisions,
};

static constexpr Character::Collisions::RelativeRect tackle_south_frame_0_mask_hitbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -12, 18, 8),
};

static constexpr Character::Collisions::RelativeRect tackle_south_frame_0_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> tackle_south_frame_0_collisions_spans[] = {
    tackle_south_frame_0_mask_hitbox_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
    tackle_south_frame_0_mask_custom_0_collisions,
};

static constexpr Character::Collisions tackle_south_frame_0_collisions(tackle_south_frame_0_collisions_spans);

static constexpr Character::Collisions::RelativeRect tackle_south_frame_1_mask_hitbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -12, 18, 8),
};

static constexpr Character::Collisions::RelativeRect tackle_south_frame_1_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> tackle_south_frame_1_collisions_spans[] = {
    tackle_south_frame_1_mask_hitbox_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
    tackle_south_frame_1_mask_custom_0_collisions,
};

static constexpr Character::Collisions tackle_south_frame_1_collisions(tackle_south_frame_1_collisions_spans);

static constexpr Character::Collisions::RelativeRect tackle_south_frame_2_mask_hitbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -12, 18, 8),
};

static constexpr Character::Collisions::RelativeRect tackle_south_frame_2_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> tackle_south_frame_2_collisions_spans[] = {
    tackle_south_frame_2_mask_hitbox_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
    tackle_south_frame_2_mask_custom_0_collisions,
};

static constexpr Character::Collisions tackle_south_frame_2_collisions(tackle_south_frame_2_collisions_spans);

static constexpr Character::Collisions::RelativeRect tackle_south_frame_3_mask_hitbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -12, 18, 8),
};

static constexpr Character::Collisions::RelativeRect tackle_south_frame_3_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> tackle_south_frame_3_collisions_spans[] = {
    tackle_south_frame_3_mask_hitbox_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
    tackle_south_frame_3_mask_custom_0_collisions,
};

static constexpr Character::Collisions tackle_south_frame_3_collisions(tackle_south_frame_3_collisions_spans);

static constexpr const Character::Collisions tackle_south_collisions[] = {
    tackle_south_frame_0_collisions,
    tackle_south_frame_1_collisions,
    tackle_south_frame_2_collisions,
    tackle_south_frame_3_collisions,
};

static constexpr Character::Collisions::RelativeRect tackle_east_frame_0_mask_hitbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -12, 18, 8),
};

static constexpr Character::Collisions::RelativeRect tackle_east_frame_0_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> tackle_east_frame_0_collisions_spans[] = {
    tackle_east_frame_0_mask_hitbox_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
    tackle_east_frame_0_mask_custom_0_collisions,
};

static constexpr Character::Collisions tackle_east_frame_0_collisions(tackle_east_frame_0_collisions_spans);

static constexpr Character::Collisions::RelativeRect tackle_east_frame_1_mask_hitbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -12, 18, 8),
};

static constexpr Character::Collisions::RelativeRect tackle_east_frame_1_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> tackle_east_frame_1_collisions_spans[] = {
    tackle_east_frame_1_mask_hitbox_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
    tackle_east_frame_1_mask_custom_0_collisions,
};

static constexpr Character::Collisions tackle_east_frame_1_collisions(tackle_east_frame_1_collisions_spans);

static constexpr Character::Collisions::RelativeRect tackle_east_frame_2_mask_hitbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -12, 18, 8),
};

static constexpr Character::Collisions::RelativeRect tackle_east_frame_2_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> tackle_east_frame_2_collisions_spans[] = {
    tackle_east_frame_2_mask_hitbox_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
    tackle_east_frame_2_mask_custom_0_collisions,
};

static constexpr Character::Collisions tackle_east_frame_2_collisions(tackle_east_frame_2_collisions_spans);

static constexpr Character::Collisions::RelativeRect tackle_east_frame_3_mask_hitbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -12, 18, 8),
};

static constexpr Character::Collisions::RelativeRect tackle_east_frame_3_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> tackle_east_frame_3_collisions_spans[] = {
    tackle_east_frame_3_mask_hitbox_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
    tackle_east_frame_3_mask_custom_0_collisions,
};

static constexpr Character::Collisions tackle_east_frame_3_collisions(tackle_east_frame_3_collisions_spans);

static constexpr const Character::Collisions tackle_east_collisions[] = {
    tackle_east_frame_0_collisions,
    tackle_east_frame_1_collisions,
    tackle_east_frame_2_collisions,
    tackle_east_frame_3_collisions,
};

static constexpr Character::Collisions::RelativeRect tackle_west_frame_0_mask_hitbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -12, 18, 8),
};

static constexpr Character::Collisions::RelativeRect tackle_west_frame_0_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> tackle_west_frame_0_collisions_spans[] = {
    tackle_west_frame_0_mask_hitbox_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
    tackle_west_frame_0_mask_custom_0_collisions,
};

static constexpr Character::Collisions tackle_west_frame_0_collisions(tackle_west_frame_0_collisions_spans);

static constexpr Character::Collisions::RelativeRect tackle_west_frame_1_mask_hitbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -12, 18, 8),
};

static constexpr Character::Collisions::RelativeRect tackle_west_frame_1_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> tackle_west_frame_1_collisions_spans[] = {
    tackle_west_frame_1_mask_hitbox_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
    tackle_west_frame_1_mask_custom_0_collisions,
};

static constexpr Character::Collisions tackle_west_frame_1_collisions(tackle_west_frame_1_collisions_spans);

static constexpr Character::Collisions::RelativeRect tackle_west_frame_2_mask_hitbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -12, 18, 8),
};

static constexpr Character::Collisions::RelativeRect tackle_west_frame_2_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> tackle_west_frame_2_collisions_spans[] = {
    tackle_west_frame_2_mask_hitbox_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
    tackle_west_frame_2_mask_custom_0_collisions,
};

static constexpr Character::Collisions tackle_west_frame_2_collisions(tackle_west_frame_2_collisions_spans);

static constexpr Character::Collisions::RelativeRect tackle_west_frame_3_mask_hitbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -12, 18, 8),
};

static constexpr Character::Collisions::RelativeRect tackle_west_frame_3_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -12, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> tackle_west_frame_3_collisions_spans[] = {
    tackle_west_frame_3_mask_hitbox_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
    tackle_west_frame_3_mask_custom_0_collisions,
};

static constexpr Character::Collisions tackle_west_frame_3_collisions(tackle_west_frame_3_collisions_spans);

static constexpr const Character::Collisions tackle_west_collisions[] = {
    tackle_west_frame_0_collisions,
    tackle_west_frame_1_collisions,
    tackle_west_frame_2_collisions,
    tackle_west_frame_3_collisions,
};

static constexpr const bn::span<const Character::Collisions> collisions[] = {
    idle_collisions,
    walk_collisions,
    walk_south_collisions,
    walk_north_collisions,
    tackle_north_collisions,
    tackle_south_collisions,
    tackle_east_collisions,
    tackle_west_collisions,
};

Chr_Slime::Chr_Slime() :
    Character(
<<<<<<< HEAD
        bn::span<const Chr_Slime::Animation>(animations, 4),
        bn::span<const Chr_Slime::Frame>(frames, 28),
        bn::span<const Chr_Slime::Sprite>(sprites, 28),
=======
        bn::span<const Chr_Slime::Animation>(animations, 8),
        bn::span<const Chr_Slime::Frame>(frames, 44),
        bn::span<const Chr_Slime::Sprite>(sprites, 44),
>>>>>>> ae73091 (Added collisions for tackle animations)
        collisions, _frameSprites, 0
    )
{
}

}
