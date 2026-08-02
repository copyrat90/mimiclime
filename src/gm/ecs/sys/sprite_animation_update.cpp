#include "gm/ecs/sys/sprite_animation_update.h"

#include "gm/cfg/sprite_animation_info.h"
#include "gm/cfg/sprite_datas.h"

namespace mc::gm::ecs::sys
{

void sprite_animation_update(actor_registry& actor_reg)
{
    actor_reg.view<cpn::sprite_animation, bn::sprite_ptr>().each(
        [&](cpn::sprite_animation& spr_anim, bn::sprite_ptr& spr) {
            if (spr_anim.current_wait_updates != 0)
                --spr_anim.current_wait_updates;
            else
            {
                BN_ASSERT(spr_anim.info);

                if (spr_anim.current_graphics_indexes_index < spr_anim.info->graphics_indexes.size() - 1)
                    ++spr_anim.current_graphics_indexes_index;
                else if (spr_anim.info->forever)
                    spr_anim.current_graphics_indexes_index = 0;
                else
                    return;

                const auto& spr_datas = cfg::sprite_datas::get(spr_anim.sprite_kind);
                spr.set_tiles(spr_datas.sprite_item().tiles_item(), spr_anim.current_graphics_index());

                spr_anim.current_wait_updates = spr_anim.info->wait_updates;
            }
        });
}

} // namespace mc::gm::ecs::sys
