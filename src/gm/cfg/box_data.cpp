#include "gm/cfg/box_data.h"

namespace mc::gm::cfg
{

auto box_data::absolute_rect(const bn::fixed_point& origin, bool horizontal_flip, bool vertical_flip) const
    -> bn::top_left_fixed_rect
{
    return {
        origin.x() + ((horizontal_flip) ? -(this->x + this->width) : this->x),
        origin.y() + ((vertical_flip) ? -(this->y + this->height) : this->y),
        this->width,
        this->height,
    };
}

} // namespace mc::gm::cfg
