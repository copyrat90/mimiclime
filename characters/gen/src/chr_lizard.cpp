// This file is auto generated!
// Exported by GBATool
// Version 1.0.0.0
// https://github.com/DarkKodKod/GBATool

#include "chr_lizard.h"

namespace gbatool
{

static constexpr Chr_Lizard::Animation animations[9] = {{1, 5, 1}, {4, 4, 0}, {7, 2, 1}, {1, 5, 1}, {4, 4, 0}, {7, 2, 1}, {1, 5, 1}, {4, 4, 0}, {7, 2, 1}};

static constexpr Chr_Lizard::Frame frames[36] = {{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10}, {11, 11}, {12, 12}, {13, 13}, {14, 14}, {15, 15}, {16, 16}, {17, 17}, {18, 18}, {19, 19}, {20, 20}, {21, 21}, {22, 22}, {23, 23}, {24, 24}, {25, 25}, {26, 26}, {27, 27}, {28, 28}, {29, 29}, {30, 30}, {31, 31}, {32, 32}, {33, 33}, {34, 34}, {35, 35}};

static constexpr Chr_Lizard::Sprite sprites[36] = {
    { &Chr_Lizard::bnk_lizard_0_lizard_idle_0, 0, 2, 0 },
    { &Chr_Lizard::bnk_lizard_0_lizard_walk_0, 0, 2, 0 },
    { &Chr_Lizard::bnk_lizard_0_lizard_walk_1, 0, 2, 0 },
    { &Chr_Lizard::bnk_lizard_0_lizard_walk_2, 0, 2, 0 },
    { &Chr_Lizard::bnk_lizard_0_lizard_walk_3, 0, 2, 0 },
    { &Chr_Lizard::bnk_lizard_0_lizard_attack_0, 0, 2, 0 },
    { &Chr_Lizard::bnk_lizard_0_lizard_attack_1, 0, 2, 0 },
    { &Chr_Lizard::bnk_lizard_0_lizard_attack_2, 0, 2, 0 },
    { &Chr_Lizard::bnk_lizard_0_lizard_attack_3, 0, 2, 0 },
    { &Chr_Lizard::bnk_lizard_0_lizard_attack_2, 0, 2, 0 },
    { &Chr_Lizard::bnk_lizard_0_lizard_attack_1, 0, 2, 0 },
    { &Chr_Lizard::bnk_lizard_0_lizard_attack_0, 0, 2, 0 },
    { &Chr_Lizard::bnk_lizard_1_lizard_idle_0, 2, 0, -2 },
    { &Chr_Lizard::bnk_lizard_1_lizard_walk_0, 2, 0, -2 },
    { &Chr_Lizard::bnk_lizard_1_lizard_walk_1, 2, 0, -2 },
    { &Chr_Lizard::bnk_lizard_1_lizard_walk_2, 2, 0, -2 },
    { &Chr_Lizard::bnk_lizard_1_lizard_walk_3, 2, 0, -2 },
    { &Chr_Lizard::bnk_lizard_1_lizard_attack_0, 2, 0, -2 },
    { &Chr_Lizard::bnk_lizard_1_lizard_attack_1, 2, 0, -2 },
    { &Chr_Lizard::bnk_lizard_1_lizard_attack_2, 2, 0, -2 },
    { &Chr_Lizard::bnk_lizard_1_lizard_attack_3, 2, 0, -2 },
    { &Chr_Lizard::bnk_lizard_1_lizard_attack_2, 2, 0, -2 },
    { &Chr_Lizard::bnk_lizard_1_lizard_attack_1, 2, 0, -2 },
    { &Chr_Lizard::bnk_lizard_1_lizard_attack_0, 2, 0, -2 },
    { &Chr_Lizard::bnk_lizard_2_lizard_north_idle_0, 0, -2, 0 },
    { &Chr_Lizard::bnk_lizard_2_lizard_north_walk_0, 0, -2, 0 },
    { &Chr_Lizard::bnk_lizard_2_lizard_north_walk_1, 0, -2, 0 },
    { &Chr_Lizard::bnk_lizard_2_lizard_north_walk_2, 0, -2, 0 },
    { &Chr_Lizard::bnk_lizard_2_lizard_north_walk_3, 0, -2, 0 },
    { &Chr_Lizard::bnk_lizard_2_lizard_north_attack_0, 0, -2, 0 },
    { &Chr_Lizard::bnk_lizard_2_lizard_north_attack_1, 0, -2, 0 },
    { &Chr_Lizard::bnk_lizard_2_lizard_north_attack_2, 0, -2, 0 },
    { &Chr_Lizard::bnk_lizard_2_lizard_north_attack_3, 0, -2, 0 },
    { &Chr_Lizard::bnk_lizard_2_lizard_north_attack_2, 0, -2, 0 },
    { &Chr_Lizard::bnk_lizard_2_lizard_north_attack_1, 0, -2, 0 },
    { &Chr_Lizard::bnk_lizard_2_lizard_north_attack_0, 0, -2, 0 }
};

static constexpr Character::Collisions::RelativeRect idle_south_frame_0_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-3, -11, 6, 25),
};

static constexpr Character::Collisions::RelativeRect idle_south_frame_0_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-4, -12, 8, 27),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> idle_south_frame_0_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    idle_south_frame_0_mask_hurtbox_collisions,
    idle_south_frame_0_mask_custom_0_collisions,
};

static constexpr Character::Collisions idle_south_frame_0_collisions(idle_south_frame_0_collisions_spans);

static constexpr const Character::Collisions idle_south_collisions[] = {
    idle_south_frame_0_collisions,
};

static constexpr Character::Collisions::RelativeRect walk_south_frame_0_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-3, -11, 6, 25),
};

static constexpr Character::Collisions::RelativeRect walk_south_frame_0_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-4, -12, 8, 27),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_south_frame_0_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_south_frame_0_mask_hurtbox_collisions,
    walk_south_frame_0_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_south_frame_0_collisions(walk_south_frame_0_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_south_frame_1_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-3, -11, 6, 25),
};

static constexpr Character::Collisions::RelativeRect walk_south_frame_1_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-4, -12, 8, 27),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_south_frame_1_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_south_frame_1_mask_hurtbox_collisions,
    walk_south_frame_1_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_south_frame_1_collisions(walk_south_frame_1_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_south_frame_2_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-3, -11, 6, 25),
};

static constexpr Character::Collisions::RelativeRect walk_south_frame_2_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-4, -12, 8, 27),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_south_frame_2_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_south_frame_2_mask_hurtbox_collisions,
    walk_south_frame_2_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_south_frame_2_collisions(walk_south_frame_2_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_south_frame_3_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-3, -11, 6, 25),
};

static constexpr Character::Collisions::RelativeRect walk_south_frame_3_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-4, -12, 8, 27),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_south_frame_3_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_south_frame_3_mask_hurtbox_collisions,
    walk_south_frame_3_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_south_frame_3_collisions(walk_south_frame_3_collisions_spans);

static constexpr const Character::Collisions walk_south_collisions[] = {
    walk_south_frame_0_collisions,
    walk_south_frame_1_collisions,
    walk_south_frame_2_collisions,
    walk_south_frame_3_collisions,
};

static constexpr Character::Collisions::RelativeRect attack_south_frame_0_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-3, -11, 6, 25),
};

static constexpr Character::Collisions::RelativeRect attack_south_frame_0_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-4, -12, 8, 27),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_south_frame_0_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    attack_south_frame_0_mask_hurtbox_collisions,
    attack_south_frame_0_mask_custom_0_collisions,
};

static constexpr Character::Collisions attack_south_frame_0_collisions(attack_south_frame_0_collisions_spans);

static constexpr Character::Collisions::RelativeRect attack_south_frame_1_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-3, -11, 6, 25),
};

static constexpr Character::Collisions::RelativeRect attack_south_frame_1_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-4, -12, 8, 27),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_south_frame_1_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    attack_south_frame_1_mask_hurtbox_collisions,
    attack_south_frame_1_mask_custom_0_collisions,
};

static constexpr Character::Collisions attack_south_frame_1_collisions(attack_south_frame_1_collisions_spans);

static constexpr Character::Collisions::RelativeRect attack_south_frame_2_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-3, -11, 6, 25),
};

static constexpr Character::Collisions::RelativeRect attack_south_frame_2_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-4, -12, 8, 27),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_south_frame_2_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    attack_south_frame_2_mask_hurtbox_collisions,
    attack_south_frame_2_mask_custom_0_collisions,
};

static constexpr Character::Collisions attack_south_frame_2_collisions(attack_south_frame_2_collisions_spans);

static constexpr Character::Collisions::RelativeRect attack_south_frame_3_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-3, -11, 6, 25),
};

static constexpr Character::Collisions::RelativeRect attack_south_frame_3_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-4, -12, 8, 27),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_south_frame_3_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    attack_south_frame_3_mask_hurtbox_collisions,
    attack_south_frame_3_mask_custom_0_collisions,
};

static constexpr Character::Collisions attack_south_frame_3_collisions(attack_south_frame_3_collisions_spans);

static constexpr Character::Collisions::RelativeRect attack_south_frame_4_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-3, -11, 6, 25),
};

static constexpr Character::Collisions::RelativeRect attack_south_frame_4_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-4, -12, 8, 27),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_south_frame_4_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    attack_south_frame_4_mask_hurtbox_collisions,
    attack_south_frame_4_mask_custom_0_collisions,
};

static constexpr Character::Collisions attack_south_frame_4_collisions(attack_south_frame_4_collisions_spans);

static constexpr Character::Collisions::RelativeRect attack_south_frame_5_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-3, -11, 6, 25),
};

static constexpr Character::Collisions::RelativeRect attack_south_frame_5_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-4, -12, 8, 27),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_south_frame_5_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    attack_south_frame_5_mask_hurtbox_collisions,
    attack_south_frame_5_mask_custom_0_collisions,
};

static constexpr Character::Collisions attack_south_frame_5_collisions(attack_south_frame_5_collisions_spans);

static constexpr Character::Collisions::RelativeRect attack_south_frame_6_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-3, -11, 6, 25),
};

static constexpr Character::Collisions::RelativeRect attack_south_frame_6_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-4, -12, 8, 27),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_south_frame_6_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    attack_south_frame_6_mask_hurtbox_collisions,
    attack_south_frame_6_mask_custom_0_collisions,
};

static constexpr Character::Collisions attack_south_frame_6_collisions(attack_south_frame_6_collisions_spans);

static constexpr const Character::Collisions attack_south_collisions[] = {
    attack_south_frame_0_collisions,
    attack_south_frame_1_collisions,
    attack_south_frame_2_collisions,
    attack_south_frame_3_collisions,
    attack_south_frame_4_collisions,
    attack_south_frame_5_collisions,
    attack_south_frame_6_collisions,
};

static constexpr Character::Collisions::RelativeRect idle_horizontally_frame_0_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-11, -3, 25, 6),
};

static constexpr Character::Collisions::RelativeRect idle_horizontally_frame_0_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-12, -4, 27, 8),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> idle_horizontally_frame_0_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    idle_horizontally_frame_0_mask_hurtbox_collisions,
    idle_horizontally_frame_0_mask_custom_0_collisions,
};

static constexpr Character::Collisions idle_horizontally_frame_0_collisions(idle_horizontally_frame_0_collisions_spans);

static constexpr const Character::Collisions idle_horizontally_collisions[] = {
    idle_horizontally_frame_0_collisions,
};

static constexpr Character::Collisions::RelativeRect walk_horizontally_frame_0_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-11, -3, 25, 6),
};

static constexpr Character::Collisions::RelativeRect walk_horizontally_frame_0_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-12, -4, 27, 8),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_horizontally_frame_0_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_horizontally_frame_0_mask_hurtbox_collisions,
    walk_horizontally_frame_0_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_horizontally_frame_0_collisions(walk_horizontally_frame_0_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_horizontally_frame_1_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-11, -3, 25, 6),
};

static constexpr Character::Collisions::RelativeRect walk_horizontally_frame_1_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-12, -4, 27, 8),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_horizontally_frame_1_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_horizontally_frame_1_mask_hurtbox_collisions,
    walk_horizontally_frame_1_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_horizontally_frame_1_collisions(walk_horizontally_frame_1_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_horizontally_frame_2_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-11, -3, 25, 6),
};

static constexpr Character::Collisions::RelativeRect walk_horizontally_frame_2_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-12, -4, 27, 8),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_horizontally_frame_2_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_horizontally_frame_2_mask_hurtbox_collisions,
    walk_horizontally_frame_2_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_horizontally_frame_2_collisions(walk_horizontally_frame_2_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_horizontally_frame_3_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-11, -3, 25, 6),
};

static constexpr Character::Collisions::RelativeRect walk_horizontally_frame_3_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-12, -4, 27, 8),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_horizontally_frame_3_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_horizontally_frame_3_mask_hurtbox_collisions,
    walk_horizontally_frame_3_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_horizontally_frame_3_collisions(walk_horizontally_frame_3_collisions_spans);

static constexpr const Character::Collisions walk_horizontally_collisions[] = {
    walk_horizontally_frame_0_collisions,
    walk_horizontally_frame_1_collisions,
    walk_horizontally_frame_2_collisions,
    walk_horizontally_frame_3_collisions,
};

static constexpr Character::Collisions::RelativeRect attack_horizontally_frame_0_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-11, -3, 25, 6),
};

static constexpr Character::Collisions::RelativeRect attack_horizontally_frame_0_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-12, -4, 27, 8),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_horizontally_frame_0_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    attack_horizontally_frame_0_mask_hurtbox_collisions,
    attack_horizontally_frame_0_mask_custom_0_collisions,
};

static constexpr Character::Collisions attack_horizontally_frame_0_collisions(attack_horizontally_frame_0_collisions_spans);

static constexpr Character::Collisions::RelativeRect attack_horizontally_frame_1_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-11, -3, 25, 6),
};

static constexpr Character::Collisions::RelativeRect attack_horizontally_frame_1_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-12, -4, 27, 8),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_horizontally_frame_1_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    attack_horizontally_frame_1_mask_hurtbox_collisions,
    attack_horizontally_frame_1_mask_custom_0_collisions,
};

static constexpr Character::Collisions attack_horizontally_frame_1_collisions(attack_horizontally_frame_1_collisions_spans);

static constexpr Character::Collisions::RelativeRect attack_horizontally_frame_2_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-11, -3, 25, 6),
};

static constexpr Character::Collisions::RelativeRect attack_horizontally_frame_2_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-12, -4, 27, 8),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_horizontally_frame_2_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    attack_horizontally_frame_2_mask_hurtbox_collisions,
    attack_horizontally_frame_2_mask_custom_0_collisions,
};

static constexpr Character::Collisions attack_horizontally_frame_2_collisions(attack_horizontally_frame_2_collisions_spans);

static constexpr Character::Collisions::RelativeRect attack_horizontally_frame_3_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-11, -3, 25, 6),
};

static constexpr Character::Collisions::RelativeRect attack_horizontally_frame_3_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-12, -4, 27, 8),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_horizontally_frame_3_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    attack_horizontally_frame_3_mask_hurtbox_collisions,
    attack_horizontally_frame_3_mask_custom_0_collisions,
};

static constexpr Character::Collisions attack_horizontally_frame_3_collisions(attack_horizontally_frame_3_collisions_spans);

static constexpr Character::Collisions::RelativeRect attack_horizontally_frame_4_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-11, -3, 25, 6),
};

static constexpr Character::Collisions::RelativeRect attack_horizontally_frame_4_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-12, -4, 27, 8),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_horizontally_frame_4_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    attack_horizontally_frame_4_mask_hurtbox_collisions,
    attack_horizontally_frame_4_mask_custom_0_collisions,
};

static constexpr Character::Collisions attack_horizontally_frame_4_collisions(attack_horizontally_frame_4_collisions_spans);

static constexpr Character::Collisions::RelativeRect attack_horizontally_frame_5_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-11, -3, 25, 6),
};

static constexpr Character::Collisions::RelativeRect attack_horizontally_frame_5_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-12, -4, 27, 8),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_horizontally_frame_5_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    attack_horizontally_frame_5_mask_hurtbox_collisions,
    attack_horizontally_frame_5_mask_custom_0_collisions,
};

static constexpr Character::Collisions attack_horizontally_frame_5_collisions(attack_horizontally_frame_5_collisions_spans);

static constexpr Character::Collisions::RelativeRect attack_horizontally_frame_6_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-11, -3, 25, 6),
};

static constexpr Character::Collisions::RelativeRect attack_horizontally_frame_6_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-12, -4, 27, 8),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_horizontally_frame_6_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    attack_horizontally_frame_6_mask_hurtbox_collisions,
    attack_horizontally_frame_6_mask_custom_0_collisions,
};

static constexpr Character::Collisions attack_horizontally_frame_6_collisions(attack_horizontally_frame_6_collisions_spans);

static constexpr const Character::Collisions attack_horizontally_collisions[] = {
    attack_horizontally_frame_0_collisions,
    attack_horizontally_frame_1_collisions,
    attack_horizontally_frame_2_collisions,
    attack_horizontally_frame_3_collisions,
    attack_horizontally_frame_4_collisions,
    attack_horizontally_frame_5_collisions,
    attack_horizontally_frame_6_collisions,
};

static constexpr Character::Collisions::RelativeRect idle_north_frame_0_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-3, -14, 6, 25),
};

static constexpr Character::Collisions::RelativeRect idle_north_frame_0_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-4, -15, 8, 27),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> idle_north_frame_0_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    idle_north_frame_0_mask_hurtbox_collisions,
    idle_north_frame_0_mask_custom_0_collisions,
};

static constexpr Character::Collisions idle_north_frame_0_collisions(idle_north_frame_0_collisions_spans);

static constexpr const Character::Collisions idle_north_collisions[] = {
    idle_north_frame_0_collisions,
};

static constexpr Character::Collisions::RelativeRect walk_north_frame_0_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-3, -14, 6, 25),
};

static constexpr Character::Collisions::RelativeRect walk_north_frame_0_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-4, -15, 8, 27),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_north_frame_0_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_north_frame_0_mask_hurtbox_collisions,
    walk_north_frame_0_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_north_frame_0_collisions(walk_north_frame_0_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_north_frame_1_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-3, -14, 6, 25),
};

static constexpr Character::Collisions::RelativeRect walk_north_frame_1_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-4, -15, 8, 27),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_north_frame_1_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_north_frame_1_mask_hurtbox_collisions,
    walk_north_frame_1_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_north_frame_1_collisions(walk_north_frame_1_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_north_frame_2_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-3, -14, 6, 25),
};

static constexpr Character::Collisions::RelativeRect walk_north_frame_2_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-4, -15, 8, 27),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_north_frame_2_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_north_frame_2_mask_hurtbox_collisions,
    walk_north_frame_2_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_north_frame_2_collisions(walk_north_frame_2_collisions_spans);

static constexpr Character::Collisions::RelativeRect walk_north_frame_3_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-3, -14, 6, 25),
};

static constexpr Character::Collisions::RelativeRect walk_north_frame_3_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-4, -15, 8, 27),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> walk_north_frame_3_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    walk_north_frame_3_mask_hurtbox_collisions,
    walk_north_frame_3_mask_custom_0_collisions,
};

static constexpr Character::Collisions walk_north_frame_3_collisions(walk_north_frame_3_collisions_spans);

static constexpr const Character::Collisions walk_north_collisions[] = {
    walk_north_frame_0_collisions,
    walk_north_frame_1_collisions,
    walk_north_frame_2_collisions,
    walk_north_frame_3_collisions,
};

static constexpr Character::Collisions::RelativeRect attack_north_frame_0_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-3, -14, 6, 25),
};

static constexpr Character::Collisions::RelativeRect attack_north_frame_0_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-4, -15, 8, 27),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_north_frame_0_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    attack_north_frame_0_mask_hurtbox_collisions,
    attack_north_frame_0_mask_custom_0_collisions,
};

static constexpr Character::Collisions attack_north_frame_0_collisions(attack_north_frame_0_collisions_spans);

static constexpr Character::Collisions::RelativeRect attack_north_frame_1_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-3, -14, 6, 25),
};

static constexpr Character::Collisions::RelativeRect attack_north_frame_1_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-4, -15, 8, 27),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_north_frame_1_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    attack_north_frame_1_mask_hurtbox_collisions,
    attack_north_frame_1_mask_custom_0_collisions,
};

static constexpr Character::Collisions attack_north_frame_1_collisions(attack_north_frame_1_collisions_spans);

static constexpr Character::Collisions::RelativeRect attack_north_frame_2_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-3, -14, 6, 25),
};

static constexpr Character::Collisions::RelativeRect attack_north_frame_2_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-4, -15, 8, 27),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_north_frame_2_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    attack_north_frame_2_mask_hurtbox_collisions,
    attack_north_frame_2_mask_custom_0_collisions,
};

static constexpr Character::Collisions attack_north_frame_2_collisions(attack_north_frame_2_collisions_spans);

static constexpr Character::Collisions::RelativeRect attack_north_frame_3_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-3, -14, 6, 25),
};

static constexpr Character::Collisions::RelativeRect attack_north_frame_3_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-4, -15, 8, 27),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_north_frame_3_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    attack_north_frame_3_mask_hurtbox_collisions,
    attack_north_frame_3_mask_custom_0_collisions,
};

static constexpr Character::Collisions attack_north_frame_3_collisions(attack_north_frame_3_collisions_spans);

static constexpr Character::Collisions::RelativeRect attack_north_frame_4_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-3, -14, 6, 25),
};

static constexpr Character::Collisions::RelativeRect attack_north_frame_4_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-4, -15, 8, 27),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_north_frame_4_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    attack_north_frame_4_mask_hurtbox_collisions,
    attack_north_frame_4_mask_custom_0_collisions,
};

static constexpr Character::Collisions attack_north_frame_4_collisions(attack_north_frame_4_collisions_spans);

static constexpr Character::Collisions::RelativeRect attack_north_frame_5_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-3, -14, 6, 25),
};

static constexpr Character::Collisions::RelativeRect attack_north_frame_5_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-4, -15, 8, 27),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_north_frame_5_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    attack_north_frame_5_mask_hurtbox_collisions,
    attack_north_frame_5_mask_custom_0_collisions,
};

static constexpr Character::Collisions attack_north_frame_5_collisions(attack_north_frame_5_collisions_spans);

static constexpr Character::Collisions::RelativeRect attack_north_frame_6_mask_hurtbox_collisions[] = {
    Character::Collisions::RelativeRect(-3, -14, 6, 25),
};

static constexpr Character::Collisions::RelativeRect attack_north_frame_6_mask_custom_0_collisions[] = {
    Character::Collisions::RelativeRect(-4, -15, 8, 27),
};

static constexpr bn::span<const Character::Collisions::RelativeRect> attack_north_frame_6_collisions_spans[] = {
    bn::span<const Character::Collisions::RelativeRect>{},
    attack_north_frame_6_mask_hurtbox_collisions,
    attack_north_frame_6_mask_custom_0_collisions,
};

static constexpr Character::Collisions attack_north_frame_6_collisions(attack_north_frame_6_collisions_spans);

static constexpr const Character::Collisions attack_north_collisions[] = {
    attack_north_frame_0_collisions,
    attack_north_frame_1_collisions,
    attack_north_frame_2_collisions,
    attack_north_frame_3_collisions,
    attack_north_frame_4_collisions,
    attack_north_frame_5_collisions,
    attack_north_frame_6_collisions,
};

static constexpr const bn::span<const Character::Collisions> collisions[] = {
    idle_south_collisions,
    walk_south_collisions,
    attack_south_collisions,
    idle_horizontally_collisions,
    walk_horizontally_collisions,
    attack_horizontally_collisions,
    idle_north_collisions,
    walk_north_collisions,
    attack_north_collisions,
};

Chr_Lizard::Chr_Lizard() :
    Character(
        bn::span<const Chr_Lizard::Animation>(animations, 9), 
        bn::span<const Chr_Lizard::Frame>(frames, 36), 
        bn::span<const Chr_Lizard::Sprite>(sprites, 36),
        collisions, _frameSprites, 0
    )
{
}

}
