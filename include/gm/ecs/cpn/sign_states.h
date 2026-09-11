#pragma once

#include <bn_string_view.h>
#include <bn_span.h>

namespace mc::gm::ecs::cpn
{

struct sign_states final
{
    bn::span<const bn::string_view> descriptions;
};

} // namespace mc::gm::ecs::cpn
