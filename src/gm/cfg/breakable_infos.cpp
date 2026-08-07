#include "gm/cfg/breakable_infos.h"

#include "ut/enum_utils.h"

#include <bn_array.h>

#include <algorithm>

namespace mc::gm::cfg
{

namespace
{

constexpr bn::array<projectile_kind, 1> WOOD_FENCE_PROJECTILES{projectile_kind::fireball};

constexpr bn::array<breakable_infos, ut::size_of_enum<ldtk::gen::breakable_kind>()> INFOS{
    breakable_infos{
        .kind = ldtk::gen::breakable_kind::wood_fence,
        .projectiles = WOOD_FENCE_PROJECTILES,
    },
};

static_assert(
    [] {
        // Ensure no invalid order
        for (int idx = 0; idx < ut::size_of_enum<ldtk::gen::breakable_kind>(); ++idx)
        {
            if (static_cast<int>(INFOS[idx].kind) != idx)
                return false;
        }
        return true;
    }(),
    "Invalid breakable infos found");

} // namespace

auto breakable_infos::get(ldtk::gen::breakable_kind kind) -> const breakable_infos&
{
    BN_ASSERT(static_cast<int>(kind) < ut::size_of_enum<ldtk::gen::breakable_kind>(),
              "Invalid breakable kind: ", static_cast<int>(kind));

    return INFOS[static_cast<int>(kind)];
}

bool breakable_infos::broken_by(projectile_kind projectile) const
{
    return std::ranges::find(this->projectiles, projectile) != this->projectiles.cend();
}

} // namespace mc::gm::cfg
