#include "gm/cfg/species_infos.h"

#include <bn_array.h>

#include <algorithm>

#include "ldtk_gen_project.h"

namespace mc::gm::cfg
{

namespace
{

constexpr bn::array<species_infos, ut::size_of_enum<ldtk::gen::species_kind>()> SPECIES_INFOS = [] {
    static constexpr auto CONFIGS_ENTITIES = ldtk::gen::gen_project.get_level(ldtk::gen::level_ident::actor_configs)
                                                 .get_layer(ldtk::gen::layer_ident::entities)
                                                 .entity_instances();

    bn::array<species_infos, ut::size_of_enum<ldtk::gen::species_kind>()> result;
    bn::array<bool, ut::size_of_enum<ldtk::gen::species_kind>()> defined = {};

    for (const ldtk::entity& entity : CONFIGS_ENTITIES)
    {
        if (entity.identifier() != ldtk::gen::entity_ident::species_configs)
            continue;

        const ldtk::gen::species_kind kind =
            entity.get_field(ldtk::gen::entity_field_ident::ENTITY_species_configs_FIELD_species)
                .get<ldtk::gen::species_kind>();

        BN_ASSERT((int)kind < result.size());
        species_infos& elem = result[(int)kind];

        BN_ASSERT(!defined[(int)kind], "`species_configs` is duplicated");
        defined[(int)kind] = true;

        const auto names = entity.get_field(ldtk::gen::entity_field_ident::ENTITY_species_configs_FIELD_names)
                               .get<bn::span<const bn::string_view>>();
        BN_ASSERT(names.size() == ut::size_of_enum<ldtk::gen::lang>(), "Missing name(s) for some language(s)");

        elem = species_infos(&entity);
    }

    BN_ASSERT(std::ranges::all_of(defined, [](bool def) { return def; }), "Missing `species_configs` for some kind");

    return result;
}();

} // namespace

auto species_infos::get(ldtk::gen::species_kind kind) -> const species_infos&
{
    BN_ASSERT(static_cast<int>(kind) < ut::size_of_enum<ldtk::gen::species_kind>(),
              "Invalid species_kind: ", static_cast<int>(kind));

    return SPECIES_INFOS.data()[(int)kind];
}

} // namespace mc::gm::cfg
