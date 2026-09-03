#include "gm/ecs/sys/camera_update.h"

#include "gm/lerp.h"

#include <bn_display.h>
#include <bn_math.h>

#include <limits>
#include <utility>

namespace mc::gm::ecs::sys
{

namespace
{

constexpr bn::fixed_point CAMERA_CENTER_OFFSET(-bn::display::width() / 2, -bn::display::height() / 2);

constexpr bn::fixed LERP_RATIO = 0.05f;
constexpr bn::fixed LERP_EPSILON_SQUARED = 0.5f;

} // namespace

void camera_update(singleton_registry& singleton_reg, const gba::entity singleton_entity, actor_registry& actor_reg)
{
    auto* camera = singleton_reg.try_get<bn::camera_ptr>(singleton_entity);
    BN_ASSERT(camera);
    auto* room = singleton_reg.try_get<cpn::room>(singleton_entity);
    BN_ASSERT(room);

    // Calculate target position
    bn::fixed_point target_pos;
    {
        int targets_count = 0;
        auto max_priority = static_cast<cpn::camera_target::tracking_priority>(
            std::numeric_limits<std::underlying_type_t<cpn::camera_target::tracking_priority>>::min());

        // Sum up all camera target positions w/ highest priority
        actor_reg.view<cpn::camera_target>().each([&](const cpn::camera_target& target) {
            if (target.priority < max_priority)
                return;
            else if (target.priority > max_priority)
            {
                target_pos = bn::fixed_point(0, 0);
                max_priority = target.priority;
                targets_count = 0;
            }

            ++targets_count;
            target_pos += target.position;
        });

        // Don't update camera if there's no target present
        if (targets_count == 0)
            return;

        // Average out all camera target positions w/ highest priority
        target_pos /= targets_count;

        target_pos += CAMERA_CENTER_OFFSET;
    }

    // Lerp from current position to target position
    const bn::fixed_point lerped_pos = lerp(camera->position(), target_pos, LERP_RATIO, LERP_EPSILON_SQUARED);

    // Apply edge-snapping
    bn::fixed_point snapped_pos = lerped_pos;
    {
        const bn::fixed_point level_dimensions = room->dimensions();

        if (level_dimensions.x() <= bn::display::width())
            snapped_pos.set_x(0);
        else if (lerped_pos.x() < 0)
            snapped_pos.set_x(0);
        else if (lerped_pos.x() > level_dimensions.x() - bn::display::width())
            snapped_pos.set_x(level_dimensions.x() - bn::display::width());

        if (level_dimensions.y() <= bn::display::height())
            snapped_pos.set_y(0);
        else if (lerped_pos.y() < 0)
            snapped_pos.set_y(0);
        else if (lerped_pos.y() > level_dimensions.y() - bn::display::height())
            snapped_pos.set_y(level_dimensions.y() - bn::display::height());
    }

    // Apply shake effect
    bn::fixed_point shaked_pos = snapped_pos;
    if (auto* shaker = singleton_reg.try_get<cpn::camera_shaker>(singleton_entity); shaker)
    {
        auto* rng = singleton_reg.try_get<bn::random>(singleton_entity);
        BN_ASSERT(rng);

        const int angle = rng->get_unbiased_int(bn::sin_lut_size - 1);
        const auto [nx, ny] = bn::lut_sin_and_cos(angle);

        const bn::fixed_point shake_diff(nx * shaker->amplitude, ny * shaker->amplitude);
        shaked_pos += shake_diff;

        shaker->amplitude = lerp(shaker->amplitude, 0, shaker->lerp_to_zero_ratio);
        if (shaker->amplitude == 0)
            singleton_reg.remove_unchecked(*shaker);
    }

    // Set the final result
    camera->set_position(shaked_pos);
}

} // namespace mc::gm::ecs::sys
