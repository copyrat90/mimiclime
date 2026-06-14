#include "gm/ecs/cpn/character_proxy.h"

namespace mc::gm::ecs::cpn
{

void character_proxy::change_species(ldtk::gen::species_kind species)
{
    auto& chara = character();
    BN_ASSERT(chara.camera().has_value());
    const bn::camera_ptr camera = chara.camera().value();
    const bn::fixed_point top_left_position = chara.top_left_position();

    destroy_character();
    construct_character(species, top_left_position, camera);
}

character_proxy::character_proxy(ldtk::gen::species_kind species, const bn::fixed_point& top_left_position,
                                 const bn::camera_ptr& camera)
{
    construct_character(species, top_left_position, camera);
}

character_proxy::~character_proxy()
{
    destroy_character();
}

void character_proxy::construct_character(ldtk::gen::species_kind species, const bn::fixed_point& top_left_position,
                                          const bn::camera_ptr& camera)
{
    switch (species)
    {
        using species_kind = ldtk::gen::species_kind;

    case species_kind::slime:
        ::new (static_cast<void*>(_character_buffer)) gbatool::Chr_Slime;
        break;

    default:
        BN_ERROR("Invalid species_kind: ", static_cast<int>(species));
    }

    _species = species;

    auto& chara = character();
    chara.set_top_left_position(top_left_position);
    chara.set_camera(camera);
    chara.set_blending_enabled(true);
    chara.set_mosaic_enabled(true);
}

void character_proxy::destroy_character()
{
    character().~Character();
}

} // namespace mc::gm::ecs::cpn
