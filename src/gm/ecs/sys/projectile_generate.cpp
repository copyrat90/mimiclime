#include "gm/ecs/sys/projectile_generate.h"

namespace mc::gm::ecs::sys
{

namespace
{

constexpr decltype(cpn::auto_destroyer::timeout_ticks) PROJECTILE_AUTO_DESTROY_TIMEOUT_TICKS = 180;

}

void projectile_generate(actor_registry& actor_reg, singleton_registry& singleton_reg,
                         const gba::entity singleton_entity)
{
    actor_reg.view<cpn::critter_states, cpn::character_proxy>().each(
        [&](const gba::entity shooter, cpn::critter_states& states, cpn::character_proxy& chara_proxy) {
            const auto& chara = chara_proxy.character();

            const bn::camera_ptr* camera = singleton_reg.try_get<bn::camera_ptr>(singleton_entity);
            BN_ASSERT(camera);

            // If no projectile rect is found, don't do anything
            const auto& projectile_rects =
                chara.current_frame_collisions().get_rects_with_mask(gbatool::Character::Mask::CUSTOM_1);
            if (projectile_rects.empty())
                return;

            // Set projectile kind considering the shooter's species.
            projectile_kind proj_kind;
            switch (states.species())
            {
                using species_kind = ldtk::gen::species_kind;

            case species_kind::lizard:
                proj_kind = projectile_kind::FIREBALL;
                break;

            default:
                BN_ERROR("Invalid shooter species: ", static_cast<int>(states.species()));
            }

            // Generate projectile in the rect positions,
            for (const auto& relative_rect : projectile_rects)
            {
                const auto rect = relative_rect.get_absolute_rect(chara);

                // (width - 2) denotes the initial direction the projectile would fly to.
                const direction projectile_direction = static_cast<direction>(rect.width().right_shift_integer() - 2);

                // (height / 10) denotes the initial speed of the projectile.
                const bn::fixed projectile_speed = rect.height() / 10;

                // Calculate the initial velocity of the projectile.
                bn::fixed_point projectile_velocity = to_normal_vector(projectile_direction) * projectile_speed;
                if (!chara.is_facing_right())
                    projectile_velocity.set_x(-projectile_velocity.x());

                // Create the projectile.
                const gba::entity projectile = actor_reg.create();

                actor_reg.emplace<cpn::velocity>(projectile, projectile_velocity);
                actor_reg.emplace<cpn::character_proxy>(projectile, proj_kind, rect.position(), *camera);

                auto& collision_events = actor_reg.emplace<cpn::collision_events>(projectile);
                collision_events.ignore_entity = shooter;

                auto& auto_destroyer = actor_reg.emplace<cpn::auto_destroyer>(projectile);
                auto_destroyer.destroy_on_timeout = true;
                auto_destroyer.timeout_ticks = PROJECTILE_AUTO_DESTROY_TIMEOUT_TICKS;
                auto_destroyer.destroy_on_collide_wall = true;
                auto_destroyer.destroy_on_collide_critter = true;
                auto_destroyer.destroy_on_collide_breakable = true;
            }
        });
}

} // namespace mc::gm::ecs::sys
