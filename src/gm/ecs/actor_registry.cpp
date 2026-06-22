#include "gm/ecs/actor_registry.h"

#include "ldtk_gen_project.h"

namespace mc::gm::ecs
{

namespace
{

constexpr int MAX_PLAYER_COUNT = 1;
constexpr int MAX_MOBS_COUNT = ldtk::gen::gen_project.defs().get_entity_def(ldtk::gen::entity_ident::mob).max_count();
constexpr int MIN_PROJECTILES_COUNT = 2 * (MAX_PLAYER_COUNT + MAX_MOBS_COUNT);

constexpr int MIN_ACTORS_COUNT = MAX_PLAYER_COUNT + MAX_MOBS_COUNT + MIN_PROJECTILES_COUNT;

static_assert(MAX_ACTORS_COUNT >= MIN_ACTORS_COUNT, "Not enough actors in actor_registry");

} // namespace

} // namespace mc::gm::ecs
