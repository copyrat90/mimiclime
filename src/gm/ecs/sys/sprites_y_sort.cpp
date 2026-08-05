#include "gm/ecs/sys/sprites_y_sort.h"

#include <bn_vector.h>

#include <algorithm>

namespace mc::gm::ecs::sys
{

void sprites_y_sort(actor_registry& actor_reg)
{
    bn::vector<bn::sprite_ptr*, MAX_ACTORS_COUNT> sprites;

    actor_reg.view<bn::sprite_ptr>().each([&](bn::sprite_ptr& sprite) { sprites.push_back(&sprite); });

    std::ranges::sort(sprites, [](const bn::sprite_ptr* s1, const bn::sprite_ptr* s2) {
        const bn::fixed_point& p1 = s1->position();
        const bn::fixed_point& p2 = s2->position();
        if (p1.y() != p2.y()) [[likely]]
            return p1.y() < p2.y();
        else if (p1.x() != p2.x())
            return p1.x() < p2.x();
        else [[unlikely]]
            return s1 < s2;
    });
    for (bn::sprite_ptr* sprite : sprites)
        sprite->put_above();
}

} // namespace mc::gm::ecs::sys
