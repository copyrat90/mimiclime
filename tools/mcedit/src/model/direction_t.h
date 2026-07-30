#pragma once

#include <imgui.h>

#include <cstdint>

namespace mcedit::model
{

enum class direction_t : std::int8_t
{
#include "direction.txt"
};

auto to_normal_vector(direction_t dir) -> ImVec2;

} // namespace mcedit::model
