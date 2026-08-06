#include "gm/ecs/cpn/projectile_states.h"

#include "gm/cfg/projectile_infos.h"

namespace mc::gm::ecs::cpn
{

projectile_states::projectile_states(projectile_kind kind_)
    : kind(kind_), state(state_t::FLY), timeout(cfg::projectile_infos::get(kind_).timeout)
{
}

} // namespace mc::gm::ecs::cpn
