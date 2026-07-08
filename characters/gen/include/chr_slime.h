// This file is auto generated!
// Exported by GBAForge
// Version 1.0.0.0
// https://github.com/DarkKodKod/GBAForge

#ifndef GBATOOL_SPRITE_CHR_SLIME
#define GBATOOL_SPRITE_CHR_SLIME

#include "bn_sprite_item.h"
#include "bn_array.h"
#include "bn_vector.h"
#include "bn_sprite_builder.h"
#include "bn_sprite_ptr.h"

#include "bank_bnk_slime_2.h"
#include "bank_bnk_slime_1.h"
#include "bank_bnk_slime_0.h"
#include "bank_bnk_slime_3.h"

#include "palette_pal_default.h"

#include "character.h"

namespace gbatool
{
    class Chr_Slime;
}

class gbatool::Chr_Slime : public Character
{
public:
    enum AnimationID
    {
        NONE = Character::AnimationID::NONE
        , IDLE_UP = 0
        , IDLE_RIGHT = 1
        , IDLE_DOWN = 2
        , IDLE_LEFT = 3
        , WALK_UP = 4
        , WALK_RIGHT = 5
        , WALK_DOWN = 6
        , WALK_LEFT = 7
        , ATTACK_UP = 8
        , ATTACK_RIGHT = 9
        , ATTACK_DOWN = 10
        , ATTACK_LEFT = 11
    };

    Chr_Slime();

protected:
    bn::vector<bn::sprite_ptr, 1> _frameSprites;

public: // Sprite items
    // idle_up_frame_1
    static constexpr bn::sprite_item bnk_slime_2_slime_idle_0 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_slime_2_slime_idle_0Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // idle_up_frame_2
    static constexpr bn::sprite_item bnk_slime_2_slime_idle_1 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_slime_2_slime_idle_1Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // idle_up_frame_3
    static constexpr bn::sprite_item bnk_slime_2_slime_idle_2 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_slime_2_slime_idle_2Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // idle_up_frame_4
    // sprite_item, bnk_slime_2_slime_idle_1, already declared in a previous frame




    // walk_up_frame_1
    static constexpr bn::sprite_item bnk_slime_1_slime_walk_vertically_7 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_slime_1_slime_walk_vertically_7Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // walk_up_frame_2
    static constexpr bn::sprite_item bnk_slime_1_slime_walk_vertically_6 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_slime_1_slime_walk_vertically_6Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // walk_up_frame_3
    static constexpr bn::sprite_item bnk_slime_1_slime_walk_vertically_5 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_slime_1_slime_walk_vertically_5Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // walk_up_frame_4
    static constexpr bn::sprite_item bnk_slime_1_slime_walk_vertically_4 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_slime_1_slime_walk_vertically_4Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // walk_up_frame_5
    static constexpr bn::sprite_item bnk_slime_1_slime_walk_vertically_3 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_slime_1_slime_walk_vertically_3Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // walk_up_frame_6
    static constexpr bn::sprite_item bnk_slime_1_slime_walk_vertically_2 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_slime_1_slime_walk_vertically_2Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // walk_up_frame_7
    static constexpr bn::sprite_item bnk_slime_1_slime_walk_vertically_1 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_slime_1_slime_walk_vertically_1Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // walk_up_frame_8
    static constexpr bn::sprite_item bnk_slime_1_slime_walk_vertically_0 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_slime_1_slime_walk_vertically_0Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // walk_right_frame_1
    static constexpr bn::sprite_item bnk_slime_0_slime_walk_0 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_slime_0_slime_walk_0Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // walk_right_frame_2
    static constexpr bn::sprite_item bnk_slime_0_slime_walk_1 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_slime_0_slime_walk_1Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // walk_right_frame_3
    static constexpr bn::sprite_item bnk_slime_0_slime_walk_2 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_slime_0_slime_walk_2Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // walk_right_frame_4
    static constexpr bn::sprite_item bnk_slime_0_slime_walk_3 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_slime_0_slime_walk_3Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // walk_right_frame_5
    static constexpr bn::sprite_item bnk_slime_0_slime_walk_4 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_slime_0_slime_walk_4Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // walk_right_frame_6
    static constexpr bn::sprite_item bnk_slime_0_slime_walk_5 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_slime_0_slime_walk_5Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // walk_right_frame_7
    static constexpr bn::sprite_item bnk_slime_0_slime_walk_6 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_slime_0_slime_walk_6Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // walk_right_frame_8
    static constexpr bn::sprite_item bnk_slime_0_slime_walk_7 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_slime_0_slime_walk_7Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // walk_down_frame_1
    // sprite_item, bnk_slime_1_slime_walk_vertically_0, already declared in a previous frame

    // walk_down_frame_2
    // sprite_item, bnk_slime_1_slime_walk_vertically_1, already declared in a previous frame

    // walk_down_frame_3
    // sprite_item, bnk_slime_1_slime_walk_vertically_2, already declared in a previous frame

    // walk_down_frame_4
    // sprite_item, bnk_slime_1_slime_walk_vertically_3, already declared in a previous frame

    // walk_down_frame_5
    // sprite_item, bnk_slime_1_slime_walk_vertically_4, already declared in a previous frame

    // walk_down_frame_6
    // sprite_item, bnk_slime_1_slime_walk_vertically_5, already declared in a previous frame

    // walk_down_frame_7
    // sprite_item, bnk_slime_1_slime_walk_vertically_6, already declared in a previous frame

    // walk_down_frame_8
    // sprite_item, bnk_slime_1_slime_walk_vertically_7, already declared in a previous frame


    // attack_up_frame_1
    static constexpr bn::sprite_item bnk_slime_3_slime_tackle_north_0 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_slime_3_slime_tackle_north_0Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // attack_up_frame_2
    static constexpr bn::sprite_item bnk_slime_3_slime_tackle_north_1 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_slime_3_slime_tackle_north_1Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // attack_up_frame_3
    static constexpr bn::sprite_item bnk_slime_3_slime_tackle_north_2 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_slime_3_slime_tackle_north_2Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // attack_up_frame_4
    static constexpr bn::sprite_item bnk_slime_3_slime_tackle_north_3 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_slime_3_slime_tackle_north_3Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // attack_right_frame_1
    static constexpr bn::sprite_item bnk_slime_3_slime_tackle_east_0 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_slime_3_slime_tackle_east_0Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // attack_right_frame_2
    static constexpr bn::sprite_item bnk_slime_3_slime_tackle_east_1 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_slime_3_slime_tackle_east_1Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // attack_right_frame_3
    static constexpr bn::sprite_item bnk_slime_3_slime_tackle_east_2 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_slime_3_slime_tackle_east_2Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // attack_right_frame_4
    static constexpr bn::sprite_item bnk_slime_3_slime_tackle_east_3 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_slime_3_slime_tackle_east_3Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // attack_down_frame_1
    static constexpr bn::sprite_item bnk_slime_3_slime_tackle_south_0 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_slime_3_slime_tackle_south_0Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // attack_down_frame_2
    static constexpr bn::sprite_item bnk_slime_3_slime_tackle_south_1 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_slime_3_slime_tackle_south_1Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // attack_down_frame_3
    static constexpr bn::sprite_item bnk_slime_3_slime_tackle_south_2 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_slime_3_slime_tackle_south_2Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // attack_down_frame_4
    static constexpr bn::sprite_item bnk_slime_3_slime_tackle_south_3 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::BIG),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_slime_3_slime_tackle_south_3Tiles, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));


};

#endif // GBATOOL_SPRITE_CHR_SLIME
