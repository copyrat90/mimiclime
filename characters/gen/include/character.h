// This file is auto generated!
// Exported by GBATool
// Version 1.0.0.0
// https://github.com/DarkKodKod/GBATool

#ifndef GBATOOL_CHARACTER
#define GBATOOL_CHARACTER

#include "bn_sprite_item.h"
#include "bn_array.h"
#include "bn_vector.h"
#include "bn_sprite_builder.h"
#include "bn_sprite_ptr.h"
#include "bn_span.h"
#include "bn_optional.h"
#include "bn_top_left_fixed_rect.h"

namespace gbatool
{

class Character
{
public:
    enum AnimationID
    {
        NONE = -1
    };

    enum class Mask : unsigned
    {
        HITBOX,
        HURTBOX,
        CUSTOM_0,
    };

    struct Animation
    {
        constexpr Animation(int total, int duration, int rep) :
            totalFrames(total)
            , frameDuration(duration)
            , repeats(rep)
        {
        }
        int totalFrames;
        int frameDuration;
        int repeats;
    };

    struct Frame
    {
        constexpr Frame(int starts, int ends) :
            spriteStarts(starts)
            , spriteEnds(ends)
        {
        }
        int spriteStarts;
        int spriteEnds;
    };

    struct Sprite
    {
        constexpr Sprite(const bn::sprite_item* item, int x, int y, int xFlipped) :
            sprite_item(item)
            , position(bn::fixed_point(x, y))
            , position_horizontal_flipped(bn::fixed_point(xFlipped, y))
        {
        }
        const bn::sprite_item* sprite_item;
        bn::fixed_point position;
        bn::fixed_point position_horizontal_flipped;
    };

    class Collisions
    {
    public:
        class RelativeRect
        {
        public:
            constexpr RelativeRect(short x, short y, unsigned short width, unsigned short height)
                : _x(x), _y(y), _width(width), _height(height)
            {
            }

            auto get_absolute_rect(const Character& self) const -> bn::top_left_fixed_rect;

        private:
            short _x, _y;
            unsigned short _width, _height;
        };

        constexpr Collisions(const bn::span<const bn::span<const RelativeRect>>& rects_per_mask)
            : _rects_per_mask(rects_per_mask)
        {
        }

        auto get_rects_with_mask(Mask) const -> const bn::span<const RelativeRect>&;

    private:
        bn::span<const bn::span<const RelativeRect>> _rects_per_mask;
    };

    virtual ~Character() = default;
    void update_animation();
    void load_animation(int animation);
    void set_position(bn::fixed x, bn::fixed y);
    void set_position(const bn::fixed_point& position);
    void set_x(bn::fixed x);
    void set_y(bn::fixed y);
    void set_top_left_position(bn::fixed top_left_x, bn::fixed top_left_y);
    void set_top_left_position(const bn::fixed_point& top_left_position);
    void set_top_left_x(bn::fixed top_left_x);
    void set_top_left_y(bn::fixed top_left_y);
    void set_camera(const bn::camera_ptr& camera);
    void remove_camera();
    void set_priority(int priority);
    void set_facing_right(bool facingRight);
    void set_frame_counter(int frameCounter);
    void set_frame_index(int frameIndex);
    void set_z_order(int z_order);
    void set_visible(bool visible);
    void set_mosaic_enabled(bool mosaicEnabled);
    void set_blending_enabled(bool blendingEnabled);
    void put_above();
    void put_below();
    [[nodiscard]] bool is_facing_right() const;
    [[nodiscard]] bool is_facing_left() const;
    [[nodiscard]] bool is_animation_playing() const;
    [[nodiscard]] bool is_visible() const;
    [[nodiscard]] int current_animation_id() const;
    [[nodiscard]] int current_animation_frame_index() const;
    [[nodiscard]] int current_frame_counter() const;
    [[nodiscard]] int current_animation_total_frames() const;
    [[nodiscard]] int current_animation_frame_duration() const;
    [[nodiscard]] int current_animation_repeats() const;
    [[nodiscard]] auto current_frame_collisions() const -> const Collisions&;
    [[nodiscard]] const bn::fixed_point& position() const;
    [[nodiscard]] bn::fixed x() const;
    [[nodiscard]] bn::fixed y() const;
    [[nodiscard]] bn::fixed_point top_left_position() const;
    [[nodiscard]] bn::fixed top_left_x() const;
    [[nodiscard]] bn::fixed top_left_y() const;
    [[nodiscard]] const bn::optional<bn::camera_ptr>& camera() const;
    [[nodiscard]] int priority() const;
    [[nodiscard]] int z_order() const;
    [[nodiscard]] bool mosaic_enabled() const;
    [[nodiscard]] bool blending_enabled() const;

protected:
    using CollisionsPerFrame = bn::span<const Collisions>;

    Character(const bn::span<const Animation>& animations, const bn::span<const Frame>& frames,
        const bn::span<const Sprite>& sprites, const bn::span<const CollisionsPerFrame>& collisions_per_animation,
        bn::ivector<bn::sprite_ptr>& currentFrameSprites, int verticalAxis);
    Character(const Character&) = delete;
    Character(const Character&&) = delete;
    bn::fixed_point _position;
    bn::optional<bn::camera_ptr> _camera;
    int _currentAnimation;
    int _frameCounter;
    int _frameIndex;
    int _priority;
    int _z_order;
    int _animation_repeats;
    bool _facingRight;
    bool _visible;
    bool _mosaicEnabled;
    bool _blendingEnabled;

private:
    [[nodiscard]] bn::optional<bn::sprite_ptr> create_sprite(unsigned int spriteIndex);
    void load_next_frame();
    void load_current_frame(bool forceReload);

    bn::span<const Animation> _animations;
    bn::span<const Frame> _frames;
    bn::span<const Sprite> _sprites;
    bn::span<const CollisionsPerFrame> _collisions_per_animation;

    bn::ivector<bn::sprite_ptr>& _currentFrameSprites;
    const int _verticalAxis;

    int _current_sprite_start_index;
    bool _animation_running;
};

}

#endif // GBATOOL_CHARACTER
