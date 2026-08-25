#include "gm/cfg/triggerable_infos.h"

#include "ut/enum_utils.h"

#include <bn_array.h>

namespace mc::gm::cfg
{

namespace
{

constexpr bn::array<projectile_kind, 1> ELEC_SWITCH_PROJECTILES{projectile_kind::elecball};

constexpr bn::array<triggerable_infos, ut::size_of_enum<ldtk::gen::triggerable_kind>()> INFOS{
    triggerable_infos{
        .kind = ldtk::gen::triggerable_kind::elec_switch,
        .projectiles = ELEC_SWITCH_PROJECTILES,
    },
};

static_assert(
    [] {
        // Ensure no invalid order
        for (int idx = 0; idx < ut::size_of_enum<ldtk::gen::triggerable_kind>(); ++idx)
        {
            if (static_cast<int>(INFOS[idx].kind) != idx)
                return false;
        }
        return true;
    }(),
    "Invalid triggerable infos found");

} // namespace

auto triggerable_infos::get(ldtk::gen::triggerable_kind kind) -> const triggerable_infos&
{
    BN_ASSERT(static_cast<int>(kind) < ut::size_of_enum<ldtk::gen::triggerable_kind>(),
              "Invalid triggerable kind: ", static_cast<int>(kind));

    return INFOS[static_cast<int>(kind)];
}

bool triggerable_infos::triggered_by(projectile_kind projectile) const
{
    return std::ranges::find(this->projectiles, projectile) != this->projectiles.cend();
}

} // namespace mc::gm::cfg
