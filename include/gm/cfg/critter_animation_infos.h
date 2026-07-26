#pragma once

#include "gm/cfg/sprite_animate_action_info.h"

#include "gm/cfg/game_configs.h"
#include "gm/critter_animation_kind.h"
#include "gm/direction.h"
#include "ut/enum_utils.h"

#include <bn_array.h>
#include <bn_optional.h>
#include <bn_sprite_item.h>

#include <algorithm>
#include <cstdint>
#include <utility>

namespace ldtk::gen
{
enum class species_kind : std::uint8_t;
}

namespace mc::gm::cfg
{

class critter_animation_infos_builder final
{
public:
    friend class critter_animation_infos;

private:
    bn::array<bn::optional<sprite_animate_action_info>, ut::size_of_enum<critter_animation_kind>() * 4> _infos;

public:
    constexpr critter_animation_infos_builder()
    {
    }

    constexpr auto set_info(critter_animation_kind anim_kind, direction dir_4,
                            const bn::optional<sprite_animate_action_info>& info) -> critter_animation_infos_builder&
    {
        if (info.has_value())
            BN_ASSERT(info->graphics_indexes.size() > 1 && info->graphics_indexes.size() <= MAX_ANIM_FRAMES,
                      "Invalid number of graphics indexes");

        auto& dest = get_info(anim_kind, dir_4);
        dest = info;
        return *this;
    }

private:
    constexpr auto get_info(critter_animation_kind anim_kind, direction dir_4)
        -> bn::optional<sprite_animate_action_info>&
    {
        return _infos[calc_idx(anim_kind, dir_4)];
    }

    static constexpr int calc_idx(critter_animation_kind anim_kind, direction dir_4)
    {
        BN_ASSERT(dir_4 == direction::UP || dir_4 == direction::RIGHT || dir_4 == direction::DOWN ||
                      dir_4 == direction::LEFT,
                  "Invalid direction: ", static_cast<int>(dir_4));

        return 4 * std::to_underlying(anim_kind) + std::to_underlying(dir_4) / 2;
    }
};

class critter_animation_infos final
{
private:
    bn::array<sprite_animate_action_info, ut::size_of_enum<critter_animation_kind>() * 4> _infos;

public:
    static auto get(ldtk::gen::species_kind species) -> const critter_animation_infos&;

public:
    constexpr critter_animation_infos(const critter_animation_infos_builder& builder)
    {
        sprite_animate_action_info global_fallback = [&] {
            auto iter = std::ranges::find_if(
                builder._infos, [](const bn::optional<sprite_animate_action_info>& info) { return info.has_value(); });
            BN_ASSERT(iter != builder._infos.cend(), "No animation at all");
            return **iter;
        }();

        for (auto anim_kind = static_cast<critter_animation_kind>(0);
             anim_kind <= static_cast<critter_animation_kind>(ut::size_of_enum<critter_animation_kind>() - 1);
             anim_kind = static_cast<critter_animation_kind>(std::to_underlying(anim_kind) + 1))
        {
            bn::optional<sprite_animate_action_info> local_fallback = [&] {
                bn::optional<sprite_animate_action_info> result;
                const auto beg_iter = builder._infos.cbegin() + 4 * std::to_underlying(anim_kind);
                const auto end_iter = builder._infos.cbegin() + 4 * (std::to_underlying(anim_kind) + 1);
                auto iter = std::find_if(beg_iter, end_iter, [](const bn::optional<sprite_animate_action_info>& info) {
                    return info.has_value();
                });
                if (iter != end_iter)
                    result = *iter;
                return result;
            }();

            for (int idx = 4 * std::to_underlying(anim_kind); idx < 4 * (std::to_underlying(anim_kind) + 1); ++idx)
            {
                auto& dest = _infos[idx];
                const auto& src = builder._infos[idx];

                if (src.has_value())
                    dest = *src;
                else if (local_fallback.has_value())
                    dest = *local_fallback;
                else
                    dest = global_fallback;
            }
        }
    }

    constexpr auto get_info(critter_animation_kind anim_kind, direction dir_4) const
        -> const sprite_animate_action_info&
    {
        return _infos[calc_idx(anim_kind, dir_4)];
    }

private:
    static constexpr int calc_idx(critter_animation_kind anim_kind, direction dir_4)
    {
        BN_ASSERT(dir_4 == direction::UP || dir_4 == direction::RIGHT || dir_4 == direction::DOWN ||
                      dir_4 == direction::LEFT,
                  "Invalid direction: ", static_cast<int>(dir_4));

        return 4 * std::to_underlying(anim_kind) + std::to_underlying(dir_4) / 2;
    }
};

} // namespace mc::gm::cfg
