#include "scn/game.h"

#include "scn/scene_context.h"
#include "ut/configs.h"

#include "gm/ecs/sys/auto_destroy.h"
#include "gm/ecs/sys/camera_target_update.h"
#include "gm/ecs/sys/camera_update.h"
#include "gm/ecs/sys/clear_critter_input.h"
#include "gm/ecs/sys/critter_act.h"
#include "gm/ecs/sys/critter_input.h"
#include "gm/ecs/sys/projectile_generate.h"
#include "gm/ecs/sys/room_change.h"
#include "gm/ecs/sys/room_exit_collide.h"
#include "gm/ecs/sys/sprite_animation_update.h"
#include "gm/ecs/sys/sprites_y_sort.h"
#include "gm/ecs/sys/velocity_movement.h"
#include "gm/ecs/ut/critter_factories.h"

namespace mc::scn
{

game::game(scene_context& ctx) : scene(ctx), _singleton_entity(_singleton_registry.create())
{
    ctx.transitions().set_alpha(ibn::transitions::kinds::FADE, 1);

    gm::cfg::room_entrance initial_entrance = get_initial_entrance();

    auto& camera = _singleton_registry.emplace<bn::camera_ptr>(_singleton_entity, bn::camera_ptr::create());
    _singleton_registry.emplace<gm::ecs::cpn::room>(_singleton_entity, initial_entrance.room_id(), camera);
    _singleton_registry.emplace<gm::ecs::cpn::room_change_states>(
        _singleton_entity, initial_entrance, gm::ecs::cpn::room_change_states::fade_state::FADING_OUT);

    const bn::fixed_point player_position = initial_entrance.position();

    gm::ecs::ut::create_player_critter(ldtk::gen::species_kind::slime, player_position, _actor_registry,
                                       _singleton_registry, _singleton_entity);
}

bool game::update()
{
    gm::ecs::sys::room_change(_singleton_registry, _singleton_entity, context().transitions(), _actor_registry);
    gm::ecs::sys::critter_input(_actor_registry, _singleton_registry, _singleton_entity);
    gm::ecs::sys::critter_act(_actor_registry);
    gm::ecs::sys::projectile_generate(_actor_registry, _singleton_registry, _singleton_entity);
    gm::ecs::sys::sprite_animation_update(_actor_registry);
    gm::ecs::sys::velocity_movement(_actor_registry, _singleton_registry, _singleton_entity);
    gm::ecs::sys::auto_destroy(_actor_registry);
    gm::ecs::sys::camera_target_update(_actor_registry);
    gm::ecs::sys::camera_update(_singleton_registry, _singleton_entity, _actor_registry);
    gm::ecs::sys::sprites_y_sort(_actor_registry);
    gm::ecs::sys::room_exit_collide(_actor_registry, _singleton_registry, _singleton_entity);
    gm::ecs::sys::clear_critter_input(_actor_registry);

    return false;
}

auto game::get_initial_entrance() const -> gm::cfg::room_entrance
{
    static constexpr const ldtk::entity& GAME_INIT_EXIT =
        ut::get_config_entity(ldtk::gen::entity_ident::exit, ldtk::gen::layer_ident::exits);

    return gm::cfg::room_entrance::from_exit(GAME_INIT_EXIT);
}

} // namespace mc::scn
