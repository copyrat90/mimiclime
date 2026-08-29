#include "gm/ecs/sys/impl/critter_input_mob.h"

#include "ut/enum_utils.h"

#include "gm/ecs/sys/impl/critter_input_mob_butterfly.h"
#include "gm/ecs/sys/impl/critter_input_mob_eel.h"
#include "gm/ecs/sys/impl/critter_input_mob_lizard.h"

#include <bn_array.h>

#include <algorithm>

#include "ldtk_gen_enums.h"

namespace mc::gm::ecs::sys::impl
{

namespace
{

void critter_input_mob_invalid(const gba::entity critter, actor_registry& actor_reg)
{
    cpn::critter_states& states = actor_reg.get<cpn::critter_states>(critter);
    BN_ERROR("Invalid critter species: ", static_cast<int>(states.species()));
}

using mob_input_func_ptr = void (*)(const gba::entity, actor_registry&);

constexpr bn::array<mob_input_func_ptr, ut::size_of_enum<ldtk::gen::species_kind>()> MOB_INPUT_FUNC_LUT{
    critter_input_mob_invalid, // slime has no mob input (player only)
    critter_input_mob_lizard,
    critter_input_mob_eel,
    critter_input_mob_butterfly,
};

// Check if forgot to add mob input function in the LUT
static_assert(std::ranges::all_of(MOB_INPUT_FUNC_LUT, [](mob_input_func_ptr func_ptr) { return func_ptr != nullptr; }),
              "Missing mob input function for some critters");

} // namespace

void critter_input_mob(const gba::entity critter, actor_registry& actor_reg)
{
    cpn::critter_states& states = actor_reg.get<cpn::critter_states>(critter);

    const auto species_idx = static_cast<int>(states.species());
    BN_ASSERT(species_idx < ut::size_of_enum<ldtk::gen::species_kind>(), "Invalid critter species: ", species_idx);

    MOB_INPUT_FUNC_LUT[species_idx](critter, actor_reg);
}

} // namespace mc::gm::ecs::sys::impl
