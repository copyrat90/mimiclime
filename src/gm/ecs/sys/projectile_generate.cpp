#include "gm/ecs/sys/projectile_generate.h"

#include "gm/cfg/linear_sprite_animation_infos.h"
#include "gm/cfg/sprite_datas.h"
#include "ut/enum_utils.h"

#include <bn_array.h>
#include <bn_sprite_builder.h>

#include <cstdint>

#include "gen/sprite_kind.h"

namespace mc::gm::ecs::sys
{

namespace
{

constexpr decltype(cpn::auto_destroyer::delay) PROJECTILE_AUTO_DESTROY_DELAY = 180;

} // namespace

void projectile_generate(actor_registry& actor_reg, singleton_registry& singleton_reg,
                         const gba::entity singleton_entity)
{
    actor_reg.view<cpn::critter_states>().each([&](const gba::entity shooter, cpn::critter_states& states) {
        const auto* camera = singleton_reg.try_get<bn::camera_ptr>(singleton_entity);
        BN_ASSERT(camera);
        const auto* shooter_sprite = actor_reg.try_get<bn::sprite_ptr>(shooter);
        BN_ASSERT(shooter_sprite);
        const auto* shooter_spr_anim = actor_reg.try_get<cpn::sprite_animation>(shooter);
        BN_ASSERT(shooter_spr_anim);

        // Projectile is only generated on the first update of the animation frame.
        BN_ASSERT(shooter_spr_anim->info);
        if (shooter_spr_anim->current_wait_updates != shooter_spr_anim->info->wait_updates)
            return;

        // Generate projectiles
        const auto& projectiles = states.sprite_datas().frame(shooter_spr_anim->current_graphics_index()).projectiles;
        for (const auto& proj_data : projectiles)
        {
            const auto spr_kind = ut::enum_to_enum<cfg::gen::sprite_kind>(proj_data.kind);
            const auto& spr_item = cfg::sprite_datas::get(spr_kind).sprite_item();
            const auto& anim_info = cfg::linear_sprite_animation_infos::get(spr_kind);

            // Calculate the position of the projectile.
            bn::fixed_point proj_pos_diff(shooter_sprite->horizontal_flip() ? -proj_data.x : proj_data.x,
                                          shooter_sprite->vertical_flip() ? -proj_data.y : proj_data.y);
            proj_pos_diff -= bn::fixed_point(spr_item.shape_size().width() / 2, spr_item.shape_size().height() / 2);
            const bn::fixed_point proj_position =
                shooter_sprite->top_left_position() +
                bn::fixed_point(shooter_sprite->shape_size().width() / 2, shooter_sprite->shape_size().height() / 2) +
                proj_pos_diff;

            // Calculate the velocity of the projectile.
            bn::fixed_point proj_velocity = to_normal_vector(proj_data.direction) * proj_data.speed;
            if (shooter_sprite->horizontal_flip())
                proj_velocity.set_x(-proj_velocity.x());
            if (shooter_sprite->vertical_flip())
                proj_velocity.set_y(-proj_velocity.y());

            // Create the projectile.
            const gba::entity projectile = actor_reg.create();

            // Velocity component.
            actor_reg.emplace<cpn::velocity>(projectile, proj_velocity);

            // Sprite and animation components.
            bn::sprite_builder spr_builder(spr_item);
            spr_builder.set_top_left_position(proj_position)
                .set_camera(*camera)
                .set_horizontal_flip(anim_info.horizontal_flip)
                .set_vertical_flip(anim_info.vertical_flip);
            auto& spr = actor_reg.emplace<bn::sprite_ptr>(projectile, spr_builder.release_build());
            actor_reg.emplace<cpn::sprite_animation>(projectile, spr, spr_item.tiles_item(), anim_info);

            // Collisions and destroyer components.
            auto& collision_events = actor_reg.emplace<cpn::collision_events>(projectile);
            collision_events.ignore_entity = shooter;

            actor_reg.emplace<cpn::auto_destroyer>(projectile, PROJECTILE_AUTO_DESTROY_DELAY);
        }
    });
}

} // namespace mc::gm::ecs::sys
