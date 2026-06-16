#pragma once

#include "ldtk_gen_enums.h"
#include "ldtk_gen_project.h"

#include <bn_colors.h>

namespace mc::ut
{

constexpr auto get_config_entity(ldtk::gen::entity_ident config_entity_ident,
                                 ldtk::gen::layer_ident entities_layer = ldtk::gen::layer_ident::entities)
    -> const ldtk::entity&
{
    const auto config_entities =
        ldtk::gen::gen_project.get_level(ldtk::gen::level_ident::configs).get_layer(entities_layer).entity_instances();

    const auto iter = std::ranges::find_if(config_entities, [config_entity_ident](const ldtk::entity& entity) {
        return entity.identifier() == config_entity_ident;
    });

    BN_ASSERT(iter != config_entities.cend(), "config entity not found");
    return *iter;
}

inline constexpr bn::color TEXT_HIGHLIGHT_COLOR = bn::colors::yellow;
inline constexpr bn::color TEXT_NORMAL_COLOR = bn::colors::white;

} // namespace mc::ut
