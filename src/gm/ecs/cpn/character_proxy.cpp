#include "gm/ecs/cpn/character_proxy.h"

#include "gm/critter_animation_kind.h"
#include "ut/enum_utils.h"

#include <concepts>
#include <memory>
#include <utility>

namespace mc::gm::ecs::cpn
{

namespace
{

template <typename Chara, typename... Args>
    requires std::derived_from<Chara, gbatool::Character>
void construct_character_at(impl::character_buffer* buffer, Args&&... args)
{
    static_assert(sizeof(Chara) <= sizeof(impl::character_buffer), "Forgot to add `Chara` type in `MAX_CHR_SIZE`?");
    static_assert(alignof(Chara) <= alignof(impl::character_buffer), "Forgot to add `Chara` type in `MAX_CHR_ALIGN`?");

    std::construct_at(reinterpret_cast<Chara*>(buffer), std::forward<Args>(args)...);
}

} // namespace

void character_proxy::change_species(ldtk::gen::species_kind species)
{
    BN_ASSERT(_meta_kind == meta_kind::critter, "non-critter can't change species");

    auto& chara = character();
    BN_ASSERT(chara.camera().has_value());
    const bn::camera_ptr camera = chara.camera().value();
    const bn::fixed_point top_left_position = chara.top_left_position();

    destroy_character();
    construct_character(species, top_left_position, camera);
}

character_proxy::character_proxy(ldtk::gen::species_kind species, const bn::fixed_point& top_left_position,
                                 const bn::camera_ptr& camera)
    : _meta_kind(meta_kind::critter)
{
    static_assert(ut::size_of_enum<ldtk::gen::species_kind>() != std::to_underlying(INVALID_SPECIES) + 1,
                  "INVALID_SPECIES is actually a valid species");

    construct_character(species, top_left_position, camera);
}

character_proxy::character_proxy(projectile_kind projectile, const bn::fixed_point& top_left_position,
                                 const bn::camera_ptr& camera)
    : _meta_kind(meta_kind::projectile)
{
    construct_character(projectile, top_left_position, camera);
}

character_proxy::character_proxy(breakable_kind breakable, const bn::fixed_point& top_left_position,
                                 const bn::camera_ptr& camera)
    : _meta_kind(meta_kind::breakable)
{
    construct_character(breakable, top_left_position, camera);
}

character_proxy::~character_proxy()
{
    destroy_character();
}

void character_proxy::construct_character(const ldtk::gen::species_kind species,
                                          const bn::fixed_point& top_left_position, const bn::camera_ptr& camera)
{
    switch (species)
    {
        using species_kind = ldtk::gen::species_kind;

    case species_kind::slime:
        construct_character_at<gbatool::Chr_Slime>(&_character_buffer);
        break;
    case species_kind::lizard:
        construct_character_at<gbatool::Chr_Lizard>(&_character_buffer);
        break;

    default:
        BN_ERROR("Invalid species_kind: ", static_cast<int>(species));
    }

    // Do not load animation here, it would be handled on `sys::critter_act()`

    _species = species;

    post_construct_character(top_left_position, camera);
}

void character_proxy::construct_character(projectile_kind projectile, const bn::fixed_point& top_left_position,
                                          const bn::camera_ptr& camera)
{
    switch (projectile)
    {
    case projectile_kind::fireball:
        construct_character_at<gbatool::Chr_Fireball>(&_character_buffer);
        break;

    default:
        BN_ERROR("Invalid projectile_kind: ", static_cast<int>(projectile));
    }

    character().load_animation(0);

    _projectile = projectile;

    post_construct_character(top_left_position, camera);
}

void character_proxy::construct_character(breakable_kind breakable, const bn::fixed_point& top_left_position,
                                          const bn::camera_ptr& camera)
{
    switch (breakable)
    {
    case breakable_kind::WOOD_FENCE:
        // construct_character_at<gbatool::Chr_Wood_Fence>(&_character_buffer);
        // break;

    default:
        BN_ERROR("Invalid breakable_kind: ", static_cast<int>(breakable));
    }

    character().load_animation(0);

    _breakable = breakable;

    post_construct_character(top_left_position, camera);
}

void character_proxy::post_construct_character(const bn::fixed_point& top_left_position, const bn::camera_ptr& camera)
{
    auto& chara = character();
    chara.set_top_left_position(top_left_position);
    chara.set_camera(camera);
    chara.set_blending_enabled(true);
    chara.set_mosaic_enabled(true);
}

void character_proxy::destroy_character()
{
    std::destroy_at(&character());
}

} // namespace mc::gm::ecs::cpn
