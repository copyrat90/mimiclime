#include "gm/cfg/interactable_infos.h"

#include "ut/enum_utils.h"

#include <bn_array.h>

namespace mc::gm::cfg
{

namespace
{

constexpr bn::array<interactable_infos, ut::size_of_enum<interactable_kind>()> INFOS{
    interactable_infos{
        .kind = interactable_kind::devourable_mob,
        .text = ldtk::gen::ingame_text_kind::tooltip_devour,
    },
    interactable_infos{
        .kind = interactable_kind::save_point,
        .text = ldtk::gen::ingame_text_kind::tooltip_save,
    },
};

static_assert(
    [] {
        // Ensure no invalid order
        for (int idx = 0; idx < ut::size_of_enum<interactable_kind>(); ++idx)
        {
            if (static_cast<int>(INFOS[idx].kind) != idx)
                return false;
        }
        return true;
    }(),
    "Invalid interactable infos found");

} // namespace

auto interactable_infos::get(interactable_kind kind) -> const interactable_infos&
{
    const auto kind_idx = static_cast<int>(kind);
    BN_ASSERT(kind_idx < ut::size_of_enum<interactable_kind>(), "Invalid interactable kind: ", kind_idx);

    return INFOS[kind_idx];
}

} // namespace mc::gm::cfg
