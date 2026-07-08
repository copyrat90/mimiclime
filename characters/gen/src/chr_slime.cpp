// This file is auto generated!
// Exported by GBAForge
// Version 1.0.0.0
// https://github.com/DarkKodKod/GBAForge

#include "chr_slime.h"

namespace gbatool
{

static constexpr Chr_Slime::Animation animations[12] = {{4, 6, 0}, {0, 5, 0}, {0, 5, 0}, {0, 5, 0}, {8, 1, 0}, {8, 1, 0}, {8, 1, 0}, {0, 5, 0}, {4, 4, 1}, {4, 4, 1}, {4, 4, 1}, {0, 5, 0}};

static constexpr Chr_Slime::Frame frames[40] = {{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10}, {11, 11}, {12, 12}, {13, 13}, {14, 14}, {15, 15}, {16, 16}, {17, 17}, {18, 18}, {19, 19}, {20, 20}, {21, 21}, {22, 22}, {23, 23}, {24, 24}, {25, 25}, {26, 26}, {27, 27}, {28, 28}, {29, 29}, {30, 30}, {31, 31}, {32, 32}, {33, 33}, {34, 34}, {35, 35}, {36, 36}, {37, 37}, {38, 38}, {39, 39}};

static constexpr Chr_Slime::Sprite sprites[40] = {
    { &Chr_Slime::bnk_slime_2_slime_idle_0, 0, -7, 0 },
    { &Chr_Slime::bnk_slime_2_slime_idle_1, 0, -7, 0 },
    { &Chr_Slime::bnk_slime_2_slime_idle_2, 0, -7, 0 },
    { &Chr_Slime::bnk_slime_2_slime_idle_1, 0, -7, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_7, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_6, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_5, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_4, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_3, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_2, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_1, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_0, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_0_slime_walk_0, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_0_slime_walk_1, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_0_slime_walk_2, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_0_slime_walk_3, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_0_slime_walk_4, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_0_slime_walk_5, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_0_slime_walk_6, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_0_slime_walk_7, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_0, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_1, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_2, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_3, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_4, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_5, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_6, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_1_slime_walk_vertically_7, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_3_slime_tackle_north_0, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_3_slime_tackle_north_1, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_3_slime_tackle_north_2, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_3_slime_tackle_north_3, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_3_slime_tackle_east_0, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_3_slime_tackle_east_1, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_3_slime_tackle_east_2, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_3_slime_tackle_east_3, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_3_slime_tackle_south_0, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_3_slime_tackle_south_1, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_3_slime_tackle_south_2, 0, -8, 0 },
    { &Chr_Slime::bnk_slime_3_slime_tackle_south_3, 0, -8, 0 }
};

static constexpr Character::Collisions::RelativeRect idle_up_frame_0_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -4, 18, 8),
};

static constexpr Character::Collisions::RelativeRect idle_up_frame_0_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> idle_up_frame_0_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    idle_up_frame_0_mask_hurtbox_collisions,
    idle_up_frame_0_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions idle_up_frame_0_collisions(idle_up_frame_0_collisions_spans);

static constexpr Character::Collisions::RelativeRect idle_up_frame_1_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -4, 18, 8),
};

static constexpr Character::Collisions::RelativeRect idle_up_frame_1_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> idle_up_frame_1_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    idle_up_frame_1_mask_hurtbox_collisions,
    idle_up_frame_1_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions idle_up_frame_1_collisions(idle_up_frame_1_collisions_spans);

static constexpr Character::Collisions::RelativeRect idle_up_frame_2_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -3, 18, 7),
};

static constexpr Character::Collisions::RelativeRect idle_up_frame_2_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> idle_up_frame_2_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    idle_up_frame_2_mask_hurtbox_collisions,
    idle_up_frame_2_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions idle_up_frame_2_collisions(idle_up_frame_2_collisions_spans);

static constexpr Character::Collisions::RelativeRect idle_up_frame_3_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -4, 18, 8),
};

static constexpr Character::Collisions::RelativeRect idle_up_frame_3_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> idle_up_frame_3_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    idle_up_frame_3_mask_hurtbox_collisions,
    idle_up_frame_3_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions idle_up_frame_3_collisions(idle_up_frame_3_collisions_spans);

static constexpr const Character::Collisions idle_up_collisions[] = {
    idle_up_frame_0_collisions,
    idle_up_frame_1_collisions,
    idle_up_frame_2_collisions,
    idle_up_frame_3_collisions,
};

static constexpr bn::span<const Character::Collisions> idle_right_collisions;

static constexpr bn::span<const Character::Collisions> idle_down_collisions;

static constexpr bn::span<const Character::Collisions> idle_left_collisions;

static constexpr Character::Collisions::RelativeRect walk_up_frame_0_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -6, 18, 8),
};

static constexpr Character::Collisions::RelativeRect walk_up_frame_0_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_up_frame_0_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_up_frame_0_mask_hurtbox_collisions,
    walk_up_frame_0_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions walk_up_frame_0_collisions(walk_up_frame_0_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_up_frame_1_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -6, 18, 8),
};

static constexpr Character::Collisions::RelativeRect walk_up_frame_1_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_up_frame_1_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_up_frame_1_mask_hurtbox_collisions,
    walk_up_frame_1_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions walk_up_frame_1_collisions(walk_up_frame_1_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_up_frame_2_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -6, 18, 8),
};

static constexpr Character::Collisions::RelativeRect walk_up_frame_2_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_up_frame_2_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_up_frame_2_mask_hurtbox_collisions,
    walk_up_frame_2_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions walk_up_frame_2_collisions(walk_up_frame_2_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_up_frame_3_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -6, 18, 8),
};

static constexpr Character::Collisions::RelativeRect walk_up_frame_3_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_up_frame_3_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_up_frame_3_mask_hurtbox_collisions,
    walk_up_frame_3_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions walk_up_frame_3_collisions(walk_up_frame_3_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_up_frame_4_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -6, 18, 9),
};

static constexpr Character::Collisions::RelativeRect walk_up_frame_4_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_up_frame_4_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_up_frame_4_mask_hurtbox_collisions,
    walk_up_frame_4_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions walk_up_frame_4_collisions(walk_up_frame_4_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_up_frame_5_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -6, 18, 9),
};

static constexpr Character::Collisions::RelativeRect walk_up_frame_5_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_up_frame_5_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_up_frame_5_mask_hurtbox_collisions,
    walk_up_frame_5_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions walk_up_frame_5_collisions(walk_up_frame_5_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_up_frame_6_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -6, 18, 9),
};

static constexpr Character::Collisions::RelativeRect walk_up_frame_6_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_up_frame_6_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_up_frame_6_mask_hurtbox_collisions,
    walk_up_frame_6_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions walk_up_frame_6_collisions(walk_up_frame_6_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_up_frame_7_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -5, 18, 8),
};

static constexpr Character::Collisions::RelativeRect walk_up_frame_7_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_up_frame_7_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_up_frame_7_mask_hurtbox_collisions,
    walk_up_frame_7_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions walk_up_frame_7_collisions(walk_up_frame_7_collisions_spans);

static constexpr const Character::Collisions walk_up_collisions[] = {
    walk_up_frame_0_collisions,
    walk_up_frame_1_collisions,
    walk_up_frame_2_collisions,
    walk_up_frame_3_collisions,
    walk_up_frame_4_collisions,
    walk_up_frame_5_collisions,
    walk_up_frame_6_collisions,
    walk_up_frame_7_collisions,
};

static constexpr Character::Collisions::RelativeRect walk_right_frame_0_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -5, 18, 8),
};

static constexpr Character::Collisions::RelativeRect walk_right_frame_0_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_right_frame_0_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_right_frame_0_mask_hurtbox_collisions,
    walk_right_frame_0_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions walk_right_frame_0_collisions(walk_right_frame_0_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_right_frame_1_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -5, 18, 8),
};

static constexpr Character::Collisions::RelativeRect walk_right_frame_1_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_right_frame_1_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_right_frame_1_mask_hurtbox_collisions,
    walk_right_frame_1_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions walk_right_frame_1_collisions(walk_right_frame_1_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_right_frame_2_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-8, -5, 17, 8),
};

static constexpr Character::Collisions::RelativeRect walk_right_frame_2_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_right_frame_2_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_right_frame_2_mask_hurtbox_collisions,
    walk_right_frame_2_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions walk_right_frame_2_collisions(walk_right_frame_2_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_right_frame_3_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-8, -5, 17, 8),
};

static constexpr Character::Collisions::RelativeRect walk_right_frame_3_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_right_frame_3_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_right_frame_3_mask_hurtbox_collisions,
    walk_right_frame_3_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions walk_right_frame_3_collisions(walk_right_frame_3_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_right_frame_4_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-8, -5, 17, 8),
};

static constexpr Character::Collisions::RelativeRect walk_right_frame_4_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_right_frame_4_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_right_frame_4_mask_hurtbox_collisions,
    walk_right_frame_4_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions walk_right_frame_4_collisions(walk_right_frame_4_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_right_frame_5_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-7, -5, 17, 8),
};

static constexpr Character::Collisions::RelativeRect walk_right_frame_5_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_right_frame_5_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_right_frame_5_mask_hurtbox_collisions,
    walk_right_frame_5_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions walk_right_frame_5_collisions(walk_right_frame_5_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_right_frame_6_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-8, -5, 17, 8),
};

static constexpr Character::Collisions::RelativeRect walk_right_frame_6_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_right_frame_6_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_right_frame_6_mask_hurtbox_collisions,
    walk_right_frame_6_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions walk_right_frame_6_collisions(walk_right_frame_6_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_right_frame_7_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-8, -5, 17, 8),
};

static constexpr Character::Collisions::RelativeRect walk_right_frame_7_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_right_frame_7_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_right_frame_7_mask_hurtbox_collisions,
    walk_right_frame_7_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions walk_right_frame_7_collisions(walk_right_frame_7_collisions_spans);

static constexpr const Character::Collisions walk_right_collisions[] = {
    walk_right_frame_0_collisions,
    walk_right_frame_1_collisions,
    walk_right_frame_2_collisions,
    walk_right_frame_3_collisions,
    walk_right_frame_4_collisions,
    walk_right_frame_5_collisions,
    walk_right_frame_6_collisions,
    walk_right_frame_7_collisions,
};

static constexpr Character::Collisions::RelativeRect walk_down_frame_0_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -5, 18, 8),
};

static constexpr Character::Collisions::RelativeRect walk_down_frame_0_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_down_frame_0_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_down_frame_0_mask_hurtbox_collisions,
    walk_down_frame_0_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions walk_down_frame_0_collisions(walk_down_frame_0_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_down_frame_1_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -5, 18, 8),
};

static constexpr Character::Collisions::RelativeRect walk_down_frame_1_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_down_frame_1_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_down_frame_1_mask_hurtbox_collisions,
    walk_down_frame_1_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions walk_down_frame_1_collisions(walk_down_frame_1_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_down_frame_2_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -5, 18, 8),
};

static constexpr Character::Collisions::RelativeRect walk_down_frame_2_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_down_frame_2_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_down_frame_2_mask_hurtbox_collisions,
    walk_down_frame_2_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions walk_down_frame_2_collisions(walk_down_frame_2_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_down_frame_3_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -5, 18, 8),
};

static constexpr Character::Collisions::RelativeRect walk_down_frame_3_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_down_frame_3_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_down_frame_3_mask_hurtbox_collisions,
    walk_down_frame_3_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions walk_down_frame_3_collisions(walk_down_frame_3_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_down_frame_4_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -5, 18, 8),
};

static constexpr Character::Collisions::RelativeRect walk_down_frame_4_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_down_frame_4_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_down_frame_4_mask_hurtbox_collisions,
    walk_down_frame_4_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions walk_down_frame_4_collisions(walk_down_frame_4_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_down_frame_5_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -6, 18, 8),
};

static constexpr Character::Collisions::RelativeRect walk_down_frame_5_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_down_frame_5_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_down_frame_5_mask_hurtbox_collisions,
    walk_down_frame_5_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions walk_down_frame_5_collisions(walk_down_frame_5_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_down_frame_6_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -6, 18, 8),
};

static constexpr Character::Collisions::RelativeRect walk_down_frame_6_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_down_frame_6_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_down_frame_6_mask_hurtbox_collisions,
    walk_down_frame_6_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions walk_down_frame_6_collisions(walk_down_frame_6_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_down_frame_7_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -6, 18, 8),
};

static constexpr Character::Collisions::RelativeRect walk_down_frame_7_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_down_frame_7_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_down_frame_7_mask_hurtbox_collisions,
    walk_down_frame_7_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions walk_down_frame_7_collisions(walk_down_frame_7_collisions_spans);

static constexpr const Character::Collisions walk_down_collisions[] = {
    walk_down_frame_0_collisions,
    walk_down_frame_1_collisions,
    walk_down_frame_2_collisions,
    walk_down_frame_3_collisions,
    walk_down_frame_4_collisions,
    walk_down_frame_5_collisions,
    walk_down_frame_6_collisions,
    walk_down_frame_7_collisions,
};

static constexpr bn::span<const Character::Collisions> walk_left_collisions;

static constexpr Character::Collisions::RelativeRect attack_up_frame_0_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -5, 18, 8),
};

static constexpr Character::Collisions::RelativeRect attack_up_frame_0_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_up_frame_0_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    attack_up_frame_0_mask_hurtbox_collisions,
    attack_up_frame_0_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions attack_up_frame_0_collisions(attack_up_frame_0_collisions_spans);

static constexpr Character::Collisions::RelativeRect attack_up_frame_1_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -4, 18, 7),
};

static constexpr Character::Collisions::RelativeRect attack_up_frame_1_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_up_frame_1_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    attack_up_frame_1_mask_hurtbox_collisions,
    attack_up_frame_1_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions attack_up_frame_1_collisions(attack_up_frame_1_collisions_spans);

static constexpr Character::Collisions::RelativeRect attack_up_frame_2_mask_hitbox_collisions[] = {
    Character::Collisions::RelativeRect(-5, -14, 10, 9),
    Character::Collisions::RelativeRect(-8, -10, 16, 5),
};

static constexpr Character::Collisions::RelativeRect attack_up_frame_2_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -5, 18, 8),
};

static constexpr Character::Collisions::RelativeRect attack_up_frame_2_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_up_frame_2_collisions_spans[] = {
    attack_up_frame_2_mask_hitbox_collisions,
    attack_up_frame_2_mask_hurtbox_collisions,
    attack_up_frame_2_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions attack_up_frame_2_collisions(attack_up_frame_2_collisions_spans);

static constexpr Character::Collisions::RelativeRect attack_up_frame_3_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -5, 18, 8),
};

static constexpr Character::Collisions::RelativeRect attack_up_frame_3_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_up_frame_3_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    attack_up_frame_3_mask_hurtbox_collisions,
    attack_up_frame_3_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions attack_up_frame_3_collisions(attack_up_frame_3_collisions_spans);

static constexpr const Character::Collisions attack_up_collisions[] = {
    attack_up_frame_0_collisions,
    attack_up_frame_1_collisions,
    attack_up_frame_2_collisions,
    attack_up_frame_3_collisions,
};

static constexpr Character::Collisions::RelativeRect attack_right_frame_0_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -5, 16, 8),
};

static constexpr Character::Collisions::RelativeRect attack_right_frame_0_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_right_frame_0_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    attack_right_frame_0_mask_hurtbox_collisions,
    attack_right_frame_0_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions attack_right_frame_0_collisions(attack_right_frame_0_collisions_spans);

static constexpr Character::Collisions::RelativeRect attack_right_frame_1_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -5, 14, 8),
};

static constexpr Character::Collisions::RelativeRect attack_right_frame_1_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_right_frame_1_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    attack_right_frame_1_mask_hurtbox_collisions,
    attack_right_frame_1_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions attack_right_frame_1_collisions(attack_right_frame_1_collisions_spans);

static constexpr Character::Collisions::RelativeRect attack_right_frame_2_mask_hitbox_collisions[] = {
    Character::Collisions::RelativeRect(6, -7, 10, 9),
    Character::Collisions::RelativeRect(6, -10, 5, 16),
};

static constexpr Character::Collisions::RelativeRect attack_right_frame_2_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-7, -5, 16, 8),
};

static constexpr Character::Collisions::RelativeRect attack_right_frame_2_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_right_frame_2_collisions_spans[] = {
    attack_right_frame_2_mask_hitbox_collisions,
    attack_right_frame_2_mask_hurtbox_collisions,
    attack_right_frame_2_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions attack_right_frame_2_collisions(attack_right_frame_2_collisions_spans);

static constexpr Character::Collisions::RelativeRect attack_right_frame_3_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -5, 16, 8),
};

static constexpr Character::Collisions::RelativeRect attack_right_frame_3_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_right_frame_3_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    attack_right_frame_3_mask_hurtbox_collisions,
    attack_right_frame_3_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions attack_right_frame_3_collisions(attack_right_frame_3_collisions_spans);

static constexpr const Character::Collisions attack_right_collisions[] = {
    attack_right_frame_0_collisions,
    attack_right_frame_1_collisions,
    attack_right_frame_2_collisions,
    attack_right_frame_3_collisions,
};

static constexpr Character::Collisions::RelativeRect attack_down_frame_0_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -5, 18, 8),
};

static constexpr Character::Collisions::RelativeRect attack_down_frame_0_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_down_frame_0_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    attack_down_frame_0_mask_hurtbox_collisions,
    attack_down_frame_0_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions attack_down_frame_0_collisions(attack_down_frame_0_collisions_spans);

static constexpr Character::Collisions::RelativeRect attack_down_frame_1_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -5, 18, 7),
};

static constexpr Character::Collisions::RelativeRect attack_down_frame_1_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_down_frame_1_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    attack_down_frame_1_mask_hurtbox_collisions,
    attack_down_frame_1_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions attack_down_frame_1_collisions(attack_down_frame_1_collisions_spans);

static constexpr Character::Collisions::RelativeRect attack_down_frame_2_mask_hitbox_collisions[] = {
    Character::Collisions::RelativeRect(-5, -1, 10, 9),
    Character::Collisions::RelativeRect(-8, -1, 16, 5),
};

static constexpr Character::Collisions::RelativeRect attack_down_frame_2_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -5, 18, 8),
};

static constexpr Character::Collisions::RelativeRect attack_down_frame_2_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_down_frame_2_collisions_spans[] = {
    attack_down_frame_2_mask_hitbox_collisions,
    attack_down_frame_2_mask_hurtbox_collisions,
    attack_down_frame_2_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions attack_down_frame_2_collisions(attack_down_frame_2_collisions_spans);

static constexpr Character::Collisions::RelativeRect attack_down_frame_3_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-9, -5, 18, 8),
};

static constexpr Character::Collisions::RelativeRect attack_down_frame_3_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-10, -5, 20, 10),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_down_frame_3_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    attack_down_frame_3_mask_hurtbox_collisions,
    attack_down_frame_3_mask_custom_0_collisions,
    bn::span<const Character::Collisions::RelativeRect>{},
};

static constexpr Character::Collisions attack_down_frame_3_collisions(attack_down_frame_3_collisions_spans);

static constexpr const Character::Collisions attack_down_collisions[] = {
    attack_down_frame_0_collisions,
    attack_down_frame_1_collisions,
    attack_down_frame_2_collisions,
    attack_down_frame_3_collisions,
};

static constexpr bn::span<const Character::Collisions> attack_left_collisions;

static constexpr const bn::span<const Character::Collisions> collisions[] = {
    idle_up_collisions,
    idle_right_collisions,
    idle_down_collisions,
    idle_left_collisions,
    walk_up_collisions,
    walk_right_collisions,
    walk_down_collisions,
    walk_left_collisions,
    attack_up_collisions,
    attack_right_collisions,
    attack_down_collisions,
    attack_left_collisions,
};

Chr_Slime::Chr_Slime() :
    Character(
        bn::span<const Chr_Slime::Animation>(animations, 12), 
        bn::span<const Chr_Slime::Frame>(frames, 40), 
        bn::span<const Chr_Slime::Sprite>(sprites, 40),
        collisions, _frameSprites, 0
    )
{
}

}
