#pragma once

#include <bn_sprite_ptr.h>
#include <bn_vector.h>

#include <cstdint>

#include "ldtk_gen_enums.h"

namespace mc::gm::ecs::cpn
{

struct ui_states final
{
    ldtk::gen::species_kind last_player_species = ldtk::gen::species_kind::slime;
    ldtk::gen::species_kind last_mob_species = ldtk::gen::species_kind::slime; // `slime` means INVALID for mob
    std::uint16_t last_player_hp = 0;
    std::uint16_t last_mob_hp = 0;

    bn::vector<bn::sprite_ptr, 8> player_texts;
    bn::vector<bn::sprite_ptr, 8> mob_texts;
};

} // namespace mc::gm::ecs::cpn
