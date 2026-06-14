#include "gm/ecs/sys/character_update.h"

#include <bn_math.h>

namespace mc::gm::ecs::sys
{

namespace
{

void update_movement(gbatool::Character& character, const cpn::velocity& velocity, singleton_registry& singleton_reg,
                     const gba::entity singleton_entity)
{
    // Collision check is actually done for slightly smaller collision rect
    // to avoid false positives for edge-edge meet
    static constexpr bn::fixed COLL_EPSILON = 0.01f;

    static constexpr const ldtk::layer_definition& TERRAIN_LAYER_DEF =
        ldtk::gen::gen_project.defs().get_layer_def(ldtk::gen::layer_ident::terrain);
    static constexpr int TERRAIN_GRID_SIZE = TERRAIN_LAYER_DEF.grid_size();

    // Resolve collisions for each axis seperately

    const auto* room = singleton_reg.try_get<cpn::room>(singleton_entity);
    BN_ASSERT(room);
    const auto& character_relative_collisions =
        character.current_frame_collisions().get_rects_with_mask(gbatool::Character::Mask::CUSTOM_0);

    // X-axis first
    if (velocity.velocity.x() != 0)
    {
        const int grid_dig_limit = (bn::abs(velocity.velocity.x()) / TERRAIN_GRID_SIZE).ceil_integer();

        // Move x-axis without considering collisions first
        character.set_x(character.x() + velocity.velocity.x());

        for (int push_x_count = 0; push_x_count < grid_dig_limit; ++push_x_count)
        {
            bn::fixed push_out = 0;

            // Detect x-axis collision
            for (const auto& character_relative_collision : character_relative_collisions)
            {
                const bn::top_left_fixed_rect character_collision =
                    character_relative_collision.get_absolute_rect(character);

                const bn::fixed x =
                    (velocity.velocity.x() > 0) ? character_collision.right() : character_collision.left();
                const bn::fixed top = character_collision.top();
                const bn::fixed bottom = character_collision.bottom();

                auto update_push_out = [&](bn::fixed y, int epsilon_dir) {
                    const bn::fixed coll_x = x + ((velocity.velocity.x() > 0) ? -COLL_EPSILON : COLL_EPSILON);
                    const bn::fixed coll_y = y + ((epsilon_dir == 0)  ? bn::fixed(0)
                                                  : (epsilon_dir > 0) ? COLL_EPSILON
                                                                      : -COLL_EPSILON);

                    if (room->collide_with_wall({coll_x, coll_y}))
                    {
                        // If moving right,
                        if (velocity.velocity.x() > 0)
                        {
                            // Snap out to the terrain grid on the left
                            const int snapped_x = ((x / TERRAIN_GRID_SIZE).ceil_integer() - 1) * TERRAIN_GRID_SIZE;
                            push_out = bn::min(push_out, snapped_x - x);
                        }
                        else // If moving left,
                        {
                            // Snap out to the terrain grid on the right
                            const int snapped_x = ((x / TERRAIN_GRID_SIZE).floor_integer() + 1) * TERRAIN_GRID_SIZE;
                            push_out = bn::max(push_out, snapped_x - x);
                        }
                    }
                };

                update_push_out(top, +1);
                for (bn::fixed y = top + TERRAIN_GRID_SIZE; y < bottom; y += TERRAIN_GRID_SIZE)
                    update_push_out(y, 0);
                update_push_out(bottom, -1);
            }

            // Resolve x-axis collision
            if (push_out == 0)
                break;
            else
                character.set_x(character.x() + push_out);
        }
    }

    // Y-axis next
    if (velocity.velocity.y() != 0)
    {
        const int grid_dig_limit = (bn::abs(velocity.velocity.y()) / TERRAIN_GRID_SIZE).ceil_integer();

        // Move y-axis without considering collisions first
        character.set_y(character.y() + velocity.velocity.y());

        for (int push_y_count = 0; push_y_count < grid_dig_limit; ++push_y_count)
        {
            bn::fixed push_out = 0;

            // Detect y-axis collision
            for (const auto& character_relative_collision : character_relative_collisions)
            {
                const bn::top_left_fixed_rect character_collision =
                    character_relative_collision.get_absolute_rect(character);

                const bn::fixed y =
                    (velocity.velocity.y() > 0) ? character_collision.bottom() : character_collision.top();
                const bn::fixed left = character_collision.left();
                const bn::fixed right = character_collision.right();

                auto update_push_out = [&](bn::fixed x, int epsilon_dir) {
                    const bn::fixed coll_y = y + ((velocity.velocity.y() > 0) ? -COLL_EPSILON : COLL_EPSILON);
                    const bn::fixed coll_x = x + ((epsilon_dir == 0)  ? bn::fixed(0)
                                                  : (epsilon_dir > 0) ? COLL_EPSILON
                                                                      : -COLL_EPSILON);

                    if (room->collide_with_wall({coll_x, coll_y}))
                    {
                        // If moving down,
                        if (velocity.velocity.y() > 0)
                        {
                            // Snap out to the terrain grid on the up
                            const int snapped_y = ((y / TERRAIN_GRID_SIZE).ceil_integer() - 1) * TERRAIN_GRID_SIZE;
                            push_out = bn::min(push_out, snapped_y - y);
                        }
                        else // If moving up,
                        {
                            // Snap out to the terrain grid on the down
                            const int snapped_y = ((y / TERRAIN_GRID_SIZE).floor_integer() + 1) * TERRAIN_GRID_SIZE;
                            push_out = bn::max(push_out, snapped_y - y);
                        }
                    }
                };

                update_push_out(left, +1);
                for (bn::fixed x = left + TERRAIN_GRID_SIZE; x < right; x += TERRAIN_GRID_SIZE)
                    update_push_out(x, 0);
                update_push_out(right, -1);
            }

            // Resolve y-axis collision
            if (push_out == 0)
                break;
            else
                character.set_y(character.y() + push_out);
        }
    }
}

} // namespace

void character_update(actor_registry& registry, singleton_registry& singleton_reg, const gba::entity singleton_entity)
{
    registry.view<cpn::character_proxy>().each([&](const gba::entity entity, cpn::character_proxy& chara_proxy) {
        auto& chara = chara_proxy.character();

        if (auto* velocity = registry.try_get<cpn::velocity>(entity); velocity != nullptr)
        {
            static constexpr bn::fixed FLIP_EPSILON = 0.01f;
            if (bn::abs(velocity->velocity.x()) > FLIP_EPSILON)
                chara.set_facing_right(velocity->velocity.x() > 0);

            update_movement(chara, *velocity, singleton_reg, singleton_entity);

            registry.remove_unchecked(*velocity);
        }

        chara.update_animation();
        chara.set_z_order(-chara.top_left_y().floor_integer());
    });
}

} // namespace mc::gm::ecs::sys
