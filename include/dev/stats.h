#pragma once

#ifndef IBN_CFG_STATS_ENABLED
#define IBN_CFG_STATS_ENABLED true
#endif

#if IBN_CFG_STATS_ENABLED

#include "gm/ecs/actor_registry.h"

#include <bn_common.h>

#include <cstdint>

namespace mc::dev
{

struct stats final
{
    static auto instance() -> stats&
    {
        static BN_DATA_EWRAM stats inst;
        return inst;
    }

    volatile std::uint8_t alive_actors = 0;
    volatile std::uint8_t max_actors = gm::ecs::MAX_ACTORS_COUNT;

private:
    stats() = default;
};

} // namespace mc::dev

#endif // IBN_CFG_STATS_ENABLED
