#include "scn/game.h"

#include "scn/scene_context.h"
#include "ut/configs.h"

#include "gm/ecs/sys/character_update.h"
#include "gm/ecs/sys/room_change.h"

namespace mc::scn
{

game::game(scene_context& ctx) : scene(ctx), _singleton_entity(_singleton_registry.create())
{
    ctx.transitions().set_alpha(ibn::transitions::kinds::FADE, 1);

    gm::cfg::room_entrance initial_entrance = get_initial_entrance();

    auto& camera = _singleton_registry.emplace<bn::camera_ptr>(_singleton_entity, bn::camera_ptr::create());
    _singleton_registry.emplace<gm::ecs::cpn::room>(_singleton_entity, initial_entrance.room_id(), camera);
    _singleton_registry.emplace<gm::ecs::cpn::room_change_states>(
        _singleton_entity, initial_entrance, ctx.transitions(), gm::ecs::cpn::room_change_states::fade_state::FADE_OUT,
        1);

    const gba::entity player = _actor_registry.create();
    auto& chara_proxy = _actor_registry.emplace<gm::ecs::cpn::character_proxy>(player, ldtk::gen::species_kind::slime,
                                                                               initial_entrance.position(), camera);
    chara_proxy.character().load_animation(gbatool::Chr_Slime::AnimationID::IDLE);
}

bool game::update()
{
    gm::ecs::sys::room_change(_singleton_registry, _singleton_entity);
    gm::ecs::sys::character_update(_actor_registry);

    return false;
}

auto game::get_initial_entrance() const -> gm::cfg::room_entrance
{
    static constexpr const ldtk::entity& GAME_INIT_EXIT =
        ut::get_config_entity(ldtk::gen::entity_ident::exit, ldtk::gen::layer_ident::exits);

    return gm::cfg::room_entrance::from_exit(GAME_INIT_EXIT);
}

} // namespace mc::scn
