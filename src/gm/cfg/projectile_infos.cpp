#include "gm/cfg/projectile_infos.h"

#include "ut/enum_utils.h"

#include <bn_array.h>

namespace mc::gm::cfg
{

namespace
{

constexpr bn::array<projectile_infos, ut::size_of_enum<projectile_kind>()> INFOS{
    projectile_infos{
        .kind = projectile_kind::fireball,
        .timeout = 180,
    },
    projectile_infos{
        .kind = projectile_kind::elecball,
        .timeout = 120,
    },
};

static_assert(
    [] {
        // Ensure no invalid order
        for (int idx = 0; idx < ut::size_of_enum<projectile_kind>(); ++idx)
            if (static_cast<int>(INFOS[idx].kind) != idx)
                return false;
        return true;
    }(),
    "Invalid projectile infos found");

} // namespace

auto projectile_infos::get(projectile_kind kind) -> const projectile_infos&
{
    BN_ASSERT(static_cast<int>(kind) < ut::size_of_enum<projectile_kind>(),
              "Invalid projectile kind: ", static_cast<int>(kind));

    return INFOS[static_cast<int>(kind)];
}

} // namespace mc::gm::cfg
