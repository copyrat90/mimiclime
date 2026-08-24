#pragma once

#include "gm/ecs/cpn/impl/critter_substates_buffer.h"

#include "ut/enum_utils.h"

#include <bn_array.h>
#include <bn_type_id.h>

#include <algorithm>

#include "ldtk_gen_enums.h"

namespace mc::gm::ecs::cpn
{

namespace details
{

inline constexpr bn::array<bn::type_id_t, ut::size_of_enum<ldtk::gen::species_kind>()> CRIT_SUBST_TYPE_IDS = {
    bn::type_id<impl::critter_substates_slime>(),
    bn::type_id<impl::critter_substates_lizard>(),
    bn::type_id<impl::critter_substates_eel>(),
    bn::type_id<impl::critter_substates_butterfly>(),
};

static_assert(std::ranges::all_of(CRIT_SUBST_TYPE_IDS,
                                  [](bn::type_id_t substates_id) { return substates_id != bn::type_id_t{}; }),
              "Type id(s) are missing for some critter substates");

static_assert(
    [] {
        for (int left_idx = 0; left_idx < CRIT_SUBST_TYPE_IDS.size() - 1; ++left_idx)
        {
            for (int right_idx = left_idx + 1; right_idx < CRIT_SUBST_TYPE_IDS.size(); ++right_idx)
            {
                const bn::type_id_t left_id = CRIT_SUBST_TYPE_IDS[left_idx];
                const bn::type_id_t right_id = CRIT_SUBST_TYPE_IDS[right_idx];

                if (left_id == right_id)
                    return false;
            }
        }

        return true;
    }(),
    "Type id(s) are duplicated for some critter substates");

} // namespace details

template <typename Substates>
auto critter_states::substates() -> Substates&
{
    BN_ASSERT(bn::type_id<Substates>() == details::CRIT_SUBST_TYPE_IDS[static_cast<int>(_species)],
              "Incorrect substates type for species: ", static_cast<int>(_species));

    return *std::launder(reinterpret_cast<Substates*>(&substates_buffer));
}

template <typename Substates>
auto critter_states::substates() const -> const Substates&
{
    BN_ASSERT(bn::type_id<Substates>() == details::CRIT_SUBST_TYPE_IDS[static_cast<int>(_species)],
              "Incorrect substates type for species: ", static_cast<int>(_species));

    return *std::launder(reinterpret_cast<const Substates*>(&substates_buffer));
}

} // namespace mc::gm::ecs::cpn
