#include "gm/ecs/ut/critter_factories.h"

#include "gm/cfg/species_infos.h"

namespace mc::gm::ecs::ut
{

namespace
{

auto create_critter_base(ldtk::gen::species_kind species, const bn::fixed_point& position, actor_registry& actor_reg,
                         singleton_registry& singleton_reg, const gba::entity singleton_entity) -> const gba::entity
{
    const auto* camera = singleton_reg.try_get<bn::camera_ptr>(singleton_entity);
    BN_ASSERT(camera);

    const gba::entity critter = actor_reg.create();
    actor_reg.emplace<cpn::character_proxy>(critter, species, position, *camera);
    actor_reg.emplace<cpn::velocity>(critter);
    actor_reg.emplace<cpn::collision_events>(critter);

    return critter;
}

} // namespace

auto create_player_critter(ldtk::gen::species_kind species, const bn::fixed_point& position, actor_registry& actor_reg,
                           singleton_registry& singleton_reg, const gba::entity singleton_entity) -> const gba::entity
{
    const gba::entity player = create_critter_base(species, position, actor_reg, singleton_reg, singleton_entity);
    actor_reg.emplace<cpn::critter_states>(player, true, species);
    actor_reg.emplace<cpn::camera_target>(player, gm::ecs::cpn::camera_target::tracking_priority::LOW, position);

    return player;
}

auto create_mob_critter(ldtk::gen::species_kind species, const bn::fixed_point& position, actor_registry& actor_reg,
                        singleton_registry& singleton_reg, const gba::entity singleton_entity) -> const gba::entity
{
    const gba::entity mob = create_critter_base(species, position, actor_reg, singleton_reg, singleton_entity);
    actor_reg.emplace<cpn::critter_states>(mob, false, species);

    return mob;
}

} // namespace mc::gm::ecs::ut
