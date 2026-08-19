#include "gm/ecs/cpn/critter_states.h"

#include "gm/cfg/species_infos.h"
#include "gm/cfg/sprite_datas.h"
#include "ut/enum_utils.h"

#include <algorithm>
#include <functional>
#include <memory>
#include <meta>
#include <utility>

#include "gen/sprite_kind.h"

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

// I don't think I would ever need to pass additional parameters, probably??
using construct_substates_func_ptr = void (*)(impl::critter_substates_buffer* buffer);

constexpr bn::array<construct_substates_func_ptr, ut::size_of_enum<ldtk::gen::species_kind>()>
    CONSTRUCT_SUBSTATES_FUNC_LUT{
        construct_substates_at<impl::critter_substates_slime>,
        construct_substates_at<impl::critter_substates_lizard>,
    };

static_assert(std::ranges::all_of(CONSTRUCT_SUBSTATES_FUNC_LUT,
                                  [](construct_substates_func_ptr func_ptr) { return func_ptr != nullptr; }),
              "Missing substate construct function for some critters");

// For `critter_states::destroy_substates()`, ugly because no easy way to select non-const variant
constexpr bn::array<std::meta::info, ut::size_of_enum<ldtk::gen::species_kind>()> SUBSTATES_GETTER_FUNC_PTR_INFO_LUT{
    std::meta::reflect_constant(static_cast<impl::critter_substates_slime& (critter_states::*)()>(
        &critter_states::substates<impl::critter_substates_slime>)),
    std::meta::reflect_constant(static_cast<impl::critter_substates_lizard& (critter_states::*)()>(
        &critter_states::substates<impl::critter_substates_lizard>)),
};

static_assert(std::ranges::all_of(SUBSTATES_GETTER_FUNC_PTR_INFO_LUT,
                                  [](std::meta::info info) { return info != std::meta::info{}; }),
              "Missing substate getter function for some critters");

} // namespace

void critter_states::change_species(ldtk::gen::species_kind species_)
{
    destroy_substates();
    construct_substates(species_);
}

auto critter_states::sprite_datas() const -> const cfg::sprite_datas&
{
    const auto spr_kind = ut::enum_to_enum<cfg::gen::sprite_kind>(_species);

    return cfg::sprite_datas::get(spr_kind);
}

void critter_states::change_hp(int diff)
{
    _hp = static_cast<decltype(_hp)>(std::max(0, _hp + diff));
}

bool critter_states::can_move() const
{
    return this->executing_action == critter_action::NONE || this->executing_action == critter_action::ATTACK;
}

bool critter_states::can_attack() const
{
    return this->executing_action == critter_action::NONE && this->attack_countdown == 0;
}

bool critter_states::can_devour() const
{
    return (this->executing_action == critter_action::NONE && this->devour_countdown == 0) ||
           this->executing_action == critter_action::WANT_TO_DEVOUR;
}

critter_states::critter_states(bool is_player_, ldtk::gen::species_kind species_)
    : _is_player(is_player_), invincible_shared_counter(0), executing_action(critter_action::NONE),
      executing_animation(critter_animation_kind::IDLE), facing_direction(direction::DOWN),
      input_action(critter_action::NONE), input_direction(direction::NONE), knockback_countdown(0), attack_countdown(0),
      devour_countdown(0)
{
    construct_substates(species_);
}

critter_states::~critter_states()
{
    destroy_substates();
}

void critter_states::construct_substates(ldtk::gen::species_kind species_)
{
    const auto species_idx = static_cast<int>(species_);
    BN_ASSERT(species_idx < ut::size_of_enum<ldtk::gen::species_kind>(), "Invalid species_kind: ", species_idx);

    CONSTRUCT_SUBSTATES_FUNC_LUT[species_idx](&substates_buffer);

    _species = species_;

    _hp = static_cast<decltype(_hp)>(cfg::species_infos::get(species_).hp());
}

void critter_states::destroy_substates()
{
    const auto species_idx = static_cast<int>(_species);

// GCC 16.1 warning bug: `substates_getter_fptr_info` shadows itself with template for expansion
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
    template for (int substates_idx = 0;
                  constexpr std::meta::info substates_getter_fptr_info : SUBSTATES_GETTER_FUNC_PTR_INFO_LUT)
    {
        if (species_idx == substates_idx++)
        {
            auto& substates = std::invoke([:substates_getter_fptr_info:], *this);
            std::destroy_at(&substates);
            return;
        }
    }
#pragma GCC diagnostic pop

    BN_ERROR("Invalid species_kind: ", species_idx);
}

} // namespace mc::gm::ecs::cpn
