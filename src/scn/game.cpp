#include "scn/game.h"

#include "scn/scene_context.h"
#include "ut/configs.h"

#include "gm/ecs/sys/breakable_update.h"
#include "gm/ecs/sys/camera_target_update.h"
#include "gm/ecs/sys/camera_update.h"
#include "gm/ecs/sys/collision_detect.h"
#include "gm/ecs/sys/critter_act.h"
#include "gm/ecs/sys/critter_input.h"
#include "gm/ecs/sys/critter_knockback.h"
#include "gm/ecs/sys/critter_take_damage.h"
#include "gm/ecs/sys/critter_ui_update.h"
#include "gm/ecs/sys/projectile_generate.h"
#include "gm/ecs/sys/projectile_update.h"
#include "gm/ecs/sys/room_change.h"
#include "gm/ecs/sys/room_exit_collide.h"
#include "gm/ecs/sys/sprite_animation_update.h"
#include "gm/ecs/sys/sprites_y_sort.h"
#include "gm/ecs/sys/terrain_collide.h"
#include "gm/ecs/sys/velocity_movement.h"
#include "gm/ecs/ut/critter_factories.h"

#include "dev/stats.h"

namespace mc::scn
{

game::game(scene_context& ctx) : scene(ctx), _singleton_entity(_singleton_registry.create())
{
    ctx.transitions().set_alpha(ibn::transitions::kinds::FADE, 1);

    auto& game_save = ctx.game_save();
    game_save.load();

    const gm::cfg::room_entrance& initial_entrance = game_save.room_entrance;

    auto& camera = _singleton_registry.emplace<bn::camera_ptr>(_singleton_entity, bn::camera_ptr::create());
    _singleton_registry.emplace<gm::ecs::cpn::room>(_singleton_entity, initial_entrance.room_id(), camera);
    _singleton_registry.emplace<gm::ecs::cpn::room_change_states>(
        _singleton_entity, initial_entrance, gm::ecs::cpn::room_change_states::fade_state::FADING_OUT);
    _singleton_registry.emplace<gm::ecs::cpn::ui_states>(_singleton_entity);
    _singleton_registry.emplace<gm::ecs::cpn::focused_actor>(_singleton_entity);

    const bn::fixed_point player_position = initial_entrance.position();

    gm::ecs::ut::create_player_critter(game_save.player_species, player_position, _actor_registry, _singleton_registry,
                                       _singleton_entity);
}

bool game::update()
{
    gm::ecs::sys::room_change(_singleton_registry, _singleton_entity, context().transitions(), _actor_registry);
    gm::ecs::sys::critter_input_clear(_actor_registry);
    gm::ecs::sys::critter_input(_actor_registry, _singleton_registry, _singleton_entity);
    gm::ecs::sys::critter_act(_actor_registry);
    gm::ecs::sys::sprite_animation_update(_actor_registry);
    gm::ecs::sys::critter_knockback(_actor_registry);
    gm::ecs::sys::velocity_movement(_actor_registry);
    gm::ecs::sys::projectile_generate(_actor_registry, _singleton_registry, _singleton_entity);
    gm::ecs::sys::collision_detect_clear(_actor_registry);
    gm::ecs::sys::collision_detect(_actor_registry);
    gm::ecs::sys::room_exit_collide(_actor_registry, _singleton_registry, _singleton_entity);
    gm::ecs::sys::terrain_collide(_actor_registry, _singleton_registry, _singleton_entity);
    gm::ecs::sys::critter_take_damage(_actor_registry, _singleton_registry, _singleton_entity);
    gm::ecs::sys::projectile_update(_actor_registry);
    gm::ecs::sys::breakable_update(_actor_registry);
    gm::ecs::sys::camera_target_update(_actor_registry);
    gm::ecs::sys::camera_update(_singleton_registry, _singleton_entity, _actor_registry);
    gm::ecs::sys::sprites_y_sort(_actor_registry);
    gm::ecs::sys::critter_ui_update(_singleton_registry, _singleton_entity, _actor_registry,
                                    context().text_generators());

#if IBN_CFG_STATS_ENABLED
    auto& stats = dev::stats::instance();
    stats.alive_actors = _actor_registry.size();
#endif

    return false;
}

} // namespace mc::scn
