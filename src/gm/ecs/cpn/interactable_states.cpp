#include "gm/ecs/cpn/interactable_states.h"

namespace mc::gm::ecs::cpn
{

interactable_states::interactable_states(interactable_kind kind_) : kind(kind_)
{
    BN_ASSERT(kind_ == interactable_kind::devourable_mob, "Invalid interactable kind: ", static_cast<int>(kind_));
}

interactable_states::interactable_states(interactable_kind kind_, const cfg::room_entrance& entrance_)
    : kind(kind_), entrance(entrance_)
{
    BN_ASSERT(kind_ == interactable_kind::save_point, "Invalid interactable kind: ", static_cast<int>(kind_));
}

} // namespace mc::gm::ecs::cpn
