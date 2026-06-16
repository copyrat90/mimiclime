#pragma once

#include "ldtk_entity.h"

#include <bn_fixed.h>

#include <cstdint>

#include "ldtk_gen_idents.h"

namespace ldtk::gen
{
enum class species_kind : std::uint8_t;
}

namespace mc::gm::cfg
{

class species_infos final
{
public:
    static auto get(ldtk::gen::species_kind) -> const species_infos&;

public:
    /// @brief Default constructor (invalid).
    /// @note We need this because array initialization requires default constructor without initializer-list.
    constexpr species_infos() : _entity(nullptr)
    {
    }

    constexpr species_infos(const ldtk::entity* entity) : _entity(entity)
    {
        BN_ASSERT(entity->identifier() == ldtk::gen::entity_ident::species_configs,
                  "Non `species_configs` entity provided for `species_infos`");
    }

public:
    constexpr auto species() const -> ldtk::gen::species_kind
    {
        return _entity->get_field(ldtk::gen::entity_field_ident::ENTITY_species_configs_FIELD_species)
            .get<ldtk::gen::species_kind>();
    }

    constexpr int hp() const
    {
        return static_cast<int>(
            _entity->get_field(ldtk::gen::entity_field_ident::ENTITY_species_configs_FIELD_hp).get<std::uint32_t>());
    }

    constexpr auto speed() const -> bn::fixed
    {
        return _entity->get_field(ldtk::gen::entity_field_ident::ENTITY_species_configs_FIELD_speed).get<bn::fixed>();
    }

private:
    const ldtk::entity* _entity;
};

} // namespace mc::gm::cfg
