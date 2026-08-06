#pragma once

#include <cstdint>

namespace mc::gm
{

enum class projectile_kind : std::uint8_t
{
#include "projectile_kind.txt"
};

} // namespace mc::gm
