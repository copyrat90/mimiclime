// This file is auto generated!
// Time-stamp 2026-6-17 20:05:51
// Exported by GBATool
// Version 1.0.0.0
// https://github.com/DarkKodKod/GBATool

#include "character.h"

#include "bn_display.h"

namespace gbatool
{

Character::Character(const bn::span<const Animation>& animations, const bn::span<const Frame>& frames,
    const bn::span<const Sprite>& sprites, const bn::span<const CollisionsPerFrame>& collisions_per_animation,
    bn::ivector<bn::sprite_ptr>& currentFrameSprites, int verticalAxis) :
    _currentAnimation(AnimationID::NONE)
    , _frameCounter(0)
    , _frameIndex(0)
    , _priority(1)
    , _z_order(1)
    , _animation_repeats(0)
    , _facingRight(true)
    , _visible(true)
    , _mosaicEnabled(false)
    , _blendingEnabled(false)
    , _animations(animations)
    , _frames(frames)
    , _sprites(sprites)
    , _collisions_per_animation(collisions_per_animation)
    , _currentFrameSprites(currentFrameSprites)
    , _verticalAxis(verticalAxis)
    , _animation_running(false)
{
}

void Character::load_animation(int animation)
{
    if (animation == _currentAnimation)
    {
        return;
    }

    _currentAnimation = animation;

    _frameIndex = -1;
    _animation_repeats = 0;
    _animation_running = true;

    load_next_frame();
}

void Character::update_animation()
{
    if (_currentAnimation < 0)
        return;

    if (!_animation_running)
        return;

    if (_animations[_currentAnimation].totalFrames <= 1)
        return;

    _frameCounter++;

    if (_animations[_currentAnimation].frameDuration != _frameCounter)
        return;

    load_next_frame();
}

void Character::load_next_frame()
{
    _frameCounter = 0;

    if (_currentAnimation < 0 || _animations[_currentAnimation].totalFrames == 0)
    {
        _currentFrameSprites.clear();
        return;
    }

    if (++_frameIndex >= _animations[_currentAnimation].totalFrames)
    {
        const int repeat = _animations[_currentAnimation].repeats;

        _animation_repeats++;

        if (repeat == 0 || _animation_repeats < repeat)
        {
            _frameIndex = 0;
        }
        else
        {
            --_frameIndex;
            _animation_running = false;
            return;
        }
    }

    load_current_frame(false);
}

void Character::load_current_frame(bool forceReload)
{
    int animationCount = 0;
    int frameCount = 0;

    while (animationCount < _currentAnimation)
    {
        frameCount += _animations[animationCount].totalFrames;
        animationCount++;
    }

    if (animationCount == _currentAnimation)
    {
        int starts = _frames[frameCount + _frameIndex].spriteStarts;
        int ends = _frames[frameCount + _frameIndex].spriteEnds;

        auto reload_sprites = [this](int s, int e) {
            _currentFrameSprites.clear();

            for (int i = s; i <= e; ++i)
            {
                bn::optional<bn::sprite_ptr> sprite = create_sprite(i);
                if (sprite.has_value())
                    _currentFrameSprites.push_back(std::move(sprite.value()));
            }

            _current_sprite_start_index = s;
        };

        if (starts >= 0)
        {
            reload_sprites(starts, ends);
        }
        else if (forceReload)
        {
            for (int nonHeldFrameIdx = _frameIndex - 1; nonHeldFrameIdx >= 0; --nonHeldFrameIdx)
            {
                starts = _frames[frameCount + nonHeldFrameIdx].spriteStarts;
                ends = _frames[frameCount + nonHeldFrameIdx].spriteEnds;

                if (starts >= 0)
                {
                    reload_sprites(starts, ends);
                    break;
                }
            }
        }
    }
}

void Character::set_position(bn::fixed x, bn::fixed y)
{
    bn::fixed_point position(x, y);
    set_position(position);
}

void Character::set_position(const bn::fixed_point& position)
{
    const bn::fixed_point diff(position - _position);

    _position = position;

    for (bn::sprite_ptr& sprite : _currentFrameSprites)
    {
        sprite.set_position(sprite.position() + diff);
    }
}

void Character::set_x(bn::fixed x)
{
    const bn::fixed diff(x - this->x());

    _position.set_x(x);

    for (bn::sprite_ptr& sprite : _currentFrameSprites)
    {
        sprite.set_x(sprite.x() + diff);
    }
}

void Character::set_y(bn::fixed y)
{
    const bn::fixed diff(y - this->y());

    _position.set_y(y);

    for (bn::sprite_ptr& sprite : _currentFrameSprites)
    {
        sprite.set_y(sprite.y() + diff);
    }
}

void Character::set_top_left_position(bn::fixed top_left_x, bn::fixed top_left_y)
{
    set_position(top_left_x - bn::display::width() / 2, top_left_y - bn::display::height() / 2);
}

void Character::set_top_left_position(const bn::fixed_point& top_left_position)
{
    set_top_left_position(top_left_position.x(), top_left_position.y());
}

void Character::set_top_left_x(bn::fixed top_left_x)
{
    set_x(top_left_x - bn::display::width() / 2);
}

void Character::set_top_left_y(bn::fixed top_left_y)
{
    set_y(top_left_y - bn::display::height() / 2);
}

const bn::optional<bn::camera_ptr>& Character::camera() const
{
    return _camera;
}

void Character::set_camera(const bn::camera_ptr& camera)
{
    _camera = camera;

    for (bn::sprite_ptr & sprite : _currentFrameSprites)
    {
        sprite.set_camera(camera);
    }
}

void Character::remove_camera()
{
    _camera.reset();

    for (bn::sprite_ptr & sprite : _currentFrameSprites)
    {
        sprite.remove_camera();
    }
}

const bn::fixed_point& Character::position() const
{
    return _position;
}

bn::fixed Character::x() const
{
    return _position.x();
}

bn::fixed Character::y() const
{
    return _position.y();
}

bn::fixed_point Character::top_left_position() const
{
    return position() + bn::fixed_point(bn::display::width() / 2, bn::display::height() / 2);
}

bn::fixed Character::top_left_x() const
{
    return x() + bn::display::width() / 2;
}

bn::fixed Character::top_left_y() const
{
    return y() + bn::display::height() / 2;
}

int Character::z_order() const
{
    return _z_order;
}

void Character::set_z_order(int z_order)
{
    _z_order = z_order;

    for (bn::sprite_ptr& sprite : _currentFrameSprites)
    {
        sprite.set_z_order(z_order);
    }
}

bool Character::is_visible() const
{
    return _visible;
}

void Character::set_visible(bool visible)
{
    _visible = visible;

    for (bn::sprite_ptr& sprite : _currentFrameSprites)
    {
        sprite.set_visible(visible);
    }
}

int Character::priority() const
{
    return _priority;
}

void Character::set_priority(int priority)
{
    _priority = priority;

    for (bn::sprite_ptr & sprite : _currentFrameSprites)
    {
        sprite.set_bg_priority(priority);
    }
}

bool Character::mosaic_enabled() const
{
    return _mosaicEnabled;
}

void Character::set_mosaic_enabled(bool mosaicEnabled)
{
    _mosaicEnabled = mosaicEnabled;

    for (bn::sprite_ptr& sprite : _currentFrameSprites)
    {
        sprite.set_mosaic_enabled(mosaicEnabled);
    }
}

bool Character::blending_enabled() const
{
    return _blendingEnabled;
}

void Character::set_blending_enabled(bool blendingEnabled)
{
    _blendingEnabled = blendingEnabled;

    for (bn::sprite_ptr& sprite : _currentFrameSprites)
    {
        sprite.set_blending_enabled(blendingEnabled);
    }
}

void Character::put_above()
{
    for (bn::sprite_ptr& sprite : _currentFrameSprites)
    {
        sprite.put_above();
    }
}

void Character::put_below()
{
    for (auto iter = _currentFrameSprites.rbegin(); iter != _currentFrameSprites.rend(); ++iter)
    {
        iter->put_below();
    }
}

int Character::current_animation_id() const
{
    return _currentAnimation;
}

int Character::current_animation_frame_index() const
{
    return _frameIndex;
}

int Character::current_frame_counter() const
{
    return _frameCounter;
}

int Character::current_animation_total_frames() const
{
    if (_currentAnimation < 0)
        return -1;

    return _animations[_currentAnimation].totalFrames;
}

int Character::current_animation_repeats() const
{
    if (_currentAnimation < 0)
        return -1;

    return _animations[_currentAnimation].repeats;
}

int Character::current_animation_frame_duration() const
{
    if (_currentAnimation < 0)
        return -1;

    return _animations[_currentAnimation].frameDuration;
}

bool Character::is_facing_right() const
{
    return _facingRight;
}

bool Character::is_animation_playing() const
{
    if (_currentAnimation < 0)
        return false;

    return _animation_running;
}

bool Character::is_facing_left() const
{
    return !_facingRight;
}

void Character::set_frame_counter(int frameCounter)
{
    _frameCounter = frameCounter;
}

void Character::set_frame_index(int frameIndex)
{
    if (frameIndex == _frameIndex)
        return;

    _frameIndex = frameIndex;

    load_current_frame(true);
}

void Character::set_facing_right(bool facingRight)
{
    if (_facingRight == facingRight)
        return;

    _facingRight = facingRight;

    int spriteCount = 0;
    for (bn::sprite_ptr& sprite : _currentFrameSprites)
    {
        sprite.set_horizontal_flip(!_facingRight);

        if (_facingRight)
            sprite.set_position(_position + _sprites[_current_sprite_start_index + spriteCount].position);
        else
            sprite.set_position(_position + _sprites[_current_sprite_start_index + spriteCount].position_horizontal_flipped);

        spriteCount++;
    }
}

bn::optional<bn::sprite_ptr> Character::create_sprite(unsigned int spriteIndex)
{
    bn::sprite_builder builder(*_sprites[spriteIndex].sprite_item, 0);

    if (_facingRight)
        builder.set_position(_position + _sprites[spriteIndex].position);
    else
        builder.set_position(_position + _sprites[spriteIndex].position_horizontal_flipped);

    builder.set_z_order(_z_order);
    builder.set_visible(_visible);
    builder.set_bg_priority(_priority);
    if (_camera.has_value())
    {
        builder.set_camera(_camera.value());
    }
    builder.set_horizontal_flip(!_facingRight);
    builder.set_mosaic_enabled(_mosaicEnabled);
    builder.set_blending_enabled(_blendingEnabled);

    return builder.release_build_optional();
}

auto Character::Collisions::RelativeRect::get_absolute_rect(const Character& self) const -> bn::top_left_fixed_rect
{
    const bn::fixed x = (self.is_facing_right() ? (int)_x : 2 * self._verticalAxis - ((int)_x + _width)) + self.top_left_x();

    return bn::top_left_fixed_rect(x, _y + self.top_left_y(), _width, _height);
}

auto Character::Collisions::get_rects_with_mask(Mask mask) const -> const bn::span<const RelativeRect>&
{
    static constexpr bn::span<const RelativeRect> NULL_RECTS;

    const unsigned idx = static_cast<unsigned>(mask);

    if (_rects_per_mask.empty())
        return NULL_RECTS;

    return _rects_per_mask[idx];
}

auto Character::current_frame_collisions() const -> const Collisions&
{
    static constexpr Collisions NULL_COLLISIONS{bn::span<const bn::span<const Collisions::RelativeRect>>()};

    if (_currentAnimation == AnimationID::NONE || _collisions_per_animation.empty())
        return NULL_COLLISIONS;

    const auto& collisions_per_frame = _collisions_per_animation[static_cast<int>(_currentAnimation)];

    if (collisions_per_frame.empty())
        return NULL_COLLISIONS;

    return collisions_per_frame[_frameIndex];
}

}
