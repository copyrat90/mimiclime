#pragma once

#include "gm/ecs/cpn/impl/character_buffer.h"

#include "gm/breakable_kind.h"
#include "gm/direction.h"
#include "gm/projectile_kind.h"

#include <limits>
#include <new>

#include "ldtk_gen_enums.h"

namespace mc::gm::ecs::cpn
{

/// @brief The GBATool character class wrapper.
///
/// @note "character" is not always a player/mob critter, it could be a projectile, breakable, etc.
/// Check `meta()` for which meta kind it is.
struct character_proxy final
{
public:
    static constexpr auto INVALID_SPECIES = static_cast<ldtk::gen::species_kind>(
        std::numeric_limits<std::underlying_type_t<ldtk::gen::species_kind>>::max());

    enum class meta_kind : std::uint8_t
    {
        critter,
        projectile,
        breakable,
    };

private:
    const meta_kind _meta_kind;
    union {
        ldtk::gen::species_kind _species;
        projectile_kind _projectile;
        breakable_kind _breakable;
    };

private:
    impl::character_buffer _character_buffer;

public:
    void change_species(ldtk::gen::species_kind);

public:
    auto meta() const -> meta_kind
    {
        return _meta_kind;
    }

    auto species() const -> ldtk::gen::species_kind
    {
        if (_meta_kind != meta_kind::critter)
            return INVALID_SPECIES;

        return _species;
    }

    auto projectile() const -> projectile_kind
    {
        if (_meta_kind != meta_kind::projectile)
            return projectile_kind::INVALID;

        return _projectile;
    }

    auto breakable() const -> breakable_kind
    {
        if (_meta_kind != meta_kind::breakable)
            return breakable_kind::INVALID;

        return _breakable;
    }

public:
    auto character() -> gbatool::Character&
    {
        return *std::launder(reinterpret_cast<gbatool::Character*>(&_character_buffer));
    }

    auto character() const -> const gbatool::Character&
    {
        return *std::launder(reinterpret_cast<const gbatool::Character*>(&_character_buffer));
    }

public:
    character_proxy(ldtk::gen::species_kind, const bn::fixed_point& top_left_position, const bn::camera_ptr&);
    character_proxy(projectile_kind, const bn::fixed_point& top_left_position, const bn::camera_ptr&);
    character_proxy(breakable_kind, const bn::fixed_point& top_left_position, const bn::camera_ptr&);
    ~character_proxy();

    character_proxy(const character_proxy&) = delete;
    character_proxy& operator=(const character_proxy&) = delete;

private:
    void construct_character(ldtk::gen::species_kind, const bn::fixed_point& top_left_position, const bn::camera_ptr&);
    void construct_character(projectile_kind, const bn::fixed_point& top_left_position, const bn::camera_ptr&);
    void construct_character(breakable_kind, const bn::fixed_point& top_left_position, const bn::camera_ptr&);

    void post_construct_character(const bn::fixed_point& top_left_position, const bn::camera_ptr&);

    void destroy_character();
};

} // namespace mc::gm::ecs::cpn
