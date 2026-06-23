// This file is auto generated!
// Exported by GBATool
// Version 1.0.0.0
// https://github.com/DarkKodKod/GBATool

#ifndef GBATOOL_SPRITE_CHR_FIREBALL
#define GBATOOL_SPRITE_CHR_FIREBALL

#include "bn_sprite_item.h"
#include "bn_array.h"
#include "bn_vector.h"
#include "bn_sprite_builder.h"
#include "bn_sprite_ptr.h"

#include "bank_bnk_fireball_0.h"

#include "palette_pal_default.h"

#include "character.h"

namespace gbatool
{
    class Chr_Fireball;
}

class gbatool::Chr_Fireball : public Character
{
public:
    enum AnimationID
    {
        NONE = Character::AnimationID::NONE
        , ANIMATION_1 = 0
    };

    Chr_Fireball();

protected:
    bn::vector<bn::sprite_ptr, 1> _frameSprites;

public: // Sprite items
    // Animation_1_frame_1
    static constexpr bn::sprite_item bnk_fireball_0_fireball_fly_0 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::SMALL),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_fireball_0_fireball_fly_0Tiles, 1), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // Animation_1_frame_2
    static constexpr bn::sprite_item bnk_fireball_0_fireball_fly_1 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::SMALL),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_fireball_0_fireball_fly_1Tiles, 1), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // Animation_1_frame_3
    static constexpr bn::sprite_item bnk_fireball_0_fireball_fly_2 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::SMALL),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_fireball_0_fireball_fly_2Tiles, 1), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

    // Animation_1_frame_4
    static constexpr bn::sprite_item bnk_fireball_0_fireball_fly_3 = bn::sprite_item(
        bn::sprite_shape_size(bn::sprite_shape::SQUARE, bn::sprite_size::SMALL),
        bn::sprite_tiles_item(bn::span<const bn::tile>(bnk_fireball_0_fireball_fly_3Tiles, 1), bn::bpp_mode::BPP_4, bn::compression_type::NONE, 1),
        bn::sprite_palette_item(bn::span<const bn::color>(palette_pal_defaultPal, 16), bn::bpp_mode::BPP_4, bn::compression_type::NONE));

};

#endif // GBATOOL_SPRITE_CHR_FIREBALL
