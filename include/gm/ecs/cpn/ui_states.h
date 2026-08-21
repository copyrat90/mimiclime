#pragma once

#include <bn_optional.h>
#include <bn_sprite_ptr.h>
#include <bn_vector.h>

#include <gba/bits/ecs/entity.hpp>

#include <cstdint>

#include "ldtk_gen_enums.h"

namespace mc::gm::ecs::cpn
{

struct ui_states final
{
    ldtk::gen::species_kind last_player_species = ldtk::gen::species_kind::slime;
    ldtk::gen::species_kind last_status_mob_species = ldtk::gen::species_kind::slime; // `slime` means INVALID for mob
    std::uint16_t last_player_hp = 0;
    std::uint16_t last_status_mob_hp = 0;

    gba::entity last_nearby_interactable;
    bn::fixed_point last_nearby_interactable_position;

    bn::optional<ldtk::gen::ingame_text_kind> reserved_interactable_tooltip;

    bn::vector<bn::sprite_ptr, 8> status_player_texts;
    bn::vector<bn::sprite_ptr, 8> status_mob_texts;

    bn::vector<bn::sprite_ptr, 8> interactable_tooltip_texts;
};

} // namespace mc::gm::ecs::cpn
