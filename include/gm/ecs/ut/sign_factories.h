#pragma once

#include "gm/ecs/actor_registry.h"
#include "gm/ecs/singleton_registry.h"

#include <bn_fixed_point_fwd.h>
#include <bn_span.h>
#include <bn_string_view.h>

namespace mc::gm::ecs::ut
{

auto create_sign(const bn::fixed_point& position, const bn::span<const bn::string_view>& descriptions, actor_registry&,
                 singleton_registry&, const gba::entity singleton_entity) -> const gba::entity;

}
