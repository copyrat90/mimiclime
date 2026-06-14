#include "gm/ecs/sys/character_update.h"

namespace mc::gm::ecs::sys
{

void character_update(actor_registry& registry)
{
    for (auto [chara_proxy] : registry.view<cpn::character_proxy>())
    {
        auto& chara = chara_proxy.character();
        chara.update_animation();
        chara.set_z_order(-chara.top_left_y().floor_integer());
    }
}

} // namespace mc::gm::ecs::sys
