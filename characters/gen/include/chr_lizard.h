// This file is auto generated!
// Exported by GBATool
// Version 1.0.0.0
// https://github.com/DarkKodKod/GBATool

#ifndef GBATOOL_SPRITE_CHR_LIZARD
#define GBATOOL_SPRITE_CHR_LIZARD

#include "bn_sprite_item.h"
#include "bn_array.h"
#include "bn_vector.h"
#include "bn_sprite_builder.h"
#include "bn_sprite_ptr.h"

#include "bank_bnk_lizard_0.h"
#include "bank_bnk_lizard_1.h"

#include ".h"

#include "character.h"

namespace gbatool
{
    class Chr_Lizard;
}

class gbatool::Chr_Lizard : public Character
{
public:
    enum AnimationID
    {
        NONE = Character::AnimationID::NONE
        , IDLE = 0
        , WALK = 1
        , ATTACK = 2
        , IDLE_HORIZONTALLY = 3
        , WALK_HORIZONTALLY = 4
        , ATTACK_HORIZONTALLY = 5
    };

    Chr_Lizard();

protected:
    bn::vector<bn::sprite_ptr, 1> _frameSprites;

public: // Sprite items
    // idle_frame_1
    static constexpr bn::sprite_item bnk_lizard_0_lizard_idle_0 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_lizard_0_lizard_idle_0Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(Pal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // walk_frame_1
    static constexpr bn::sprite_item bnk_lizard_0_lizard_walk_0 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_lizard_0_lizard_walk_0Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(Pal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // walk_frame_2
    static constexpr bn::sprite_item bnk_lizard_0_lizard_walk_1 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_lizard_0_lizard_walk_1Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(Pal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // walk_frame_3
    static constexpr bn::sprite_item bnk_lizard_0_lizard_walk_2 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_lizard_0_lizard_walk_2Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(Pal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // walk_frame_4
    static constexpr bn::sprite_item bnk_lizard_0_lizard_walk_3 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_lizard_0_lizard_walk_3Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(Pal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // attack_frame_1
    static constexpr bn::sprite_item bnk_lizard_0_lizard_attack_0 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_lizard_0_lizard_attack_0Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(Pal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // attack_frame_2
    static constexpr bn::sprite_item bnk_lizard_0_lizard_attack_1 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_lizard_0_lizard_attack_1Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(Pal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // attack_frame_3
    static constexpr bn::sprite_item bnk_lizard_0_lizard_attack_2 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_lizard_0_lizard_attack_2Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(Pal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // attack_frame_4
    static constexpr bn::sprite_item bnk_lizard_0_lizard_attack_3 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_lizard_0_lizard_attack_3Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(Pal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // attack_frame_5
    // sprite_item, bnk_lizard_0_lizard_attack_2, already declared in a previous frame

    // attack_frame_6
    // sprite_item, bnk_lizard_0_lizard_attack_1, already declared in a previous frame

    // attack_frame_7
    // sprite_item, bnk_lizard_0_lizard_attack_0, already declared in a previous frame

    // idle_horizontally_frame_1
    static constexpr bn::sprite_item bnk_lizard_1_lizard_idle_0 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_lizard_1_lizard_idle_0Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(Pal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // walk_horizontally_frame_1
    static constexpr bn::sprite_item bnk_lizard_1_lizard_walk_0 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_lizard_1_lizard_walk_0Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(Pal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // walk_horizontally_frame_2
    static constexpr bn::sprite_item bnk_lizard_1_lizard_walk_1 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_lizard_1_lizard_walk_1Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(Pal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // walk_horizontally_frame_3
    static constexpr bn::sprite_item bnk_lizard_1_lizard_walk_2 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_lizard_1_lizard_walk_2Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(Pal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // walk_horizontally_frame_4
    static constexpr bn::sprite_item bnk_lizard_1_lizard_walk_3 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_lizard_1_lizard_walk_3Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(Pal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // attack_horizontally_frame_1
    static constexpr bn::sprite_item bnk_lizard_1_lizard_attack_0 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_lizard_1_lizard_attack_0Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(Pal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // attack_horizontally_frame_2
    static constexpr bn::sprite_item bnk_lizard_1_lizard_attack_1 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_lizard_1_lizard_attack_1Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(Pal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // attack_horizontally_frame_3
    static constexpr bn::sprite_item bnk_lizard_1_lizard_attack_2 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_lizard_1_lizard_attack_2Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(Pal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // attack_horizontally_frame_4
    static constexpr bn::sprite_item bnk_lizard_1_lizard_attack_3 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_lizard_1_lizard_attack_3Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(Pal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // attack_horizontally_frame_5
    // sprite_item, bnk_lizard_1_lizard_attack_2, already declared in a previous frame

    // attack_horizontally_frame_6
    // sprite_item, bnk_lizard_1_lizard_attack_1, already declared in a previous frame

    // attack_horizontally_frame_7
    // sprite_item, bnk_lizard_1_lizard_attack_0, already declared in a previous frame

};

#endif // GBATOOL_SPRITE_CHR_LIZARD
