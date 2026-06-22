#pragma once

#include "chr_fireball.h"
#include "chr_lizard.h"
#include "chr_slime.h"

#include <algorithm>
#include <cstddef>

namespace mc::gm::ecs::cpn::impl
{

inline constexpr auto MAX_CHR_SIZE =
    std::max({sizeof(gbatool::Chr_Slime), sizeof(gbatool::Chr_Lizard), sizeof(gbatool::Chr_Fireball)});
inline constexpr auto MAX_CHR_ALIGN =
    std::max({alignof(gbatool::Chr_Slime), alignof(gbatool::Chr_Lizard), alignof(gbatool::Chr_Fireball)});

struct character_buffer final
{
    alignas(MAX_CHR_ALIGN) std::byte buffer[MAX_CHR_SIZE];
};

} // namespace mc::gm::ecs::cpn::impl
