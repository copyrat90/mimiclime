#include "gm/ecs/cpn/critter_states.h"

#include "gm/cfg/species_infos.h"

#include <algorithm>
#include <memory>
#include <utility>

namespace mc::gm::ecs::cpn
{

namespace
{

template <typename Substates, typename... Args>
void construct_substates_at(impl::critter_substates_buffer* buffer, Args&&... args)
{
    static_assert(sizeof(Substates) <= sizeof(impl::critter_substates_buffer),
                  "Forgot to add `Substates` type in `MAX_CRIT_SUBST_SIZE`?");
    static_assert(alignof(Substates) <= alignof(impl::critter_substates_buffer),
                  "Forgot to add `Substates` type in `MAX_CRIT_SUBST_ALIGN`?");

    std::construct_at(reinterpret_cast<Substates*>(buffer), std::forward<Args>(args)...);
}

} // namespace

void critter_states::change_species(ldtk::gen::species_kind species_)
{
    destroy_substates();
    construct_substates(species_);
}

void critter_states::change_hp(int diff)
{
    _hp = static_cast<decltype(_hp)>(std::max(0, _hp + diff));
}

critter_states::critter_states(bool is_player_, ldtk::gen::species_kind species_)
    : _is_player(is_player_), executing_action(critter_action::NONE), facing_direction(direction::NONE),
      input_action(critter_action::NONE), input_direction(direction::NONE), attack_countdown(0), devour_countdown(0)
{
    construct_substates(species_);
}

critter_states::~critter_states()
{
    destroy_substates();
}

void critter_states::construct_substates(ldtk::gen::species_kind species_)
{
    switch (_species)
    {
        using species_kind = ldtk::gen::species_kind;

    case species_kind::slime:
        construct_substates_at<impl::critter_substates_slime>(&substates_buffer);
        break;
    case species_kind::fire_lizard:
        construct_substates_at<impl::critter_substates_lizard>(&substates_buffer);
        break;

    default:
        BN_ERROR("Invalid species_kind: ", static_cast<int>(_species));
    }

    _species = species_;

    // TODO: Apply previous hp ratio
    _hp = static_cast<decltype(_hp)>(cfg::species_infos::get(species_).hp());
}

void critter_states::destroy_substates()
{
    switch (_species)
    {
        using species_kind = ldtk::gen::species_kind;

    case species_kind::slime:
        std::destroy_at(&substates<impl::critter_substates_slime>());
        break;
    case species_kind::fire_lizard:
        std::destroy_at(&substates<impl::critter_substates_lizard>());
        break;

    default:
        BN_ERROR("Invalid species_kind: ", static_cast<int>(_species));
    }
}

} // namespace mc::gm::ecs::cpn
