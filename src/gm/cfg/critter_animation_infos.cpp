#include "gm/cfg/critter_animation_infos.h"

#include "ldtk_gen_enums.h"

#include <limits>

namespace mc::gm::cfg
{

namespace
{

constexpr std::uint16_t SLIME_IDLE_GFX_IDXES[] = {16, 17, 18, 17};
constexpr std::uint16_t SLIME_WALK_UP_GFX_IDXES[] = {15, 14, 13, 12, 11, 10, 9, 8};
constexpr std::uint16_t SLIME_WALK_DOWN_GFX_IDXES[] = {8, 9, 10, 11, 12, 13, 14, 15};
constexpr std::uint16_t SLIME_WALK_SIDE_GFX_IDXES[] = {0, 1, 2, 3, 4, 5, 6, 7};
constexpr std::uint16_t SLIME_ATTACK_UP_GFX_IDXES[] = {28, 29, 30, 31};
constexpr std::uint16_t SLIME_ATTACK_DOWN_GFX_IDXES[] = {24, 25, 26, 27};
constexpr std::uint16_t SLIME_ATTACK_SIDE_GFX_IDXES[] = {19, 20, 21, 22, 23};

constexpr std::uint16_t LIZARD_IDLE_VERT_GFX_IDXES[] = {0};
constexpr std::uint16_t LIZARD_IDLE_SIDE_GFX_IDXES[] = {9};
constexpr std::uint16_t LIZARD_WALK_VERT_GFX_IDXES[] = {1, 2, 3, 4};
constexpr std::uint16_t LIZARD_WALK_SIDE_GFX_IDXES[] = {10, 11, 12, 13};
constexpr std::uint16_t LIZARD_ATTACK_VERT_GFX_IDXES[] = {5, 6, 7, 8, 7};
constexpr std::uint16_t LIZARD_ATTACK_SIDE_GFX_IDXES[] = {14, 15, 16, 17, 16};

constexpr std::uint16_t EEL_WAIT_UPDATES = 2;
constexpr std::uint16_t EEL_IDLE_VERT_GFX_IDXES[] = {7};
constexpr std::uint16_t EEL_IDLE_SIDE_GFX_IDXES[] = {3};
constexpr std::uint16_t EEL_WALK_VERT_GFX_IDXES[] = {4, 5, 6, 7};
constexpr std::uint16_t EEL_WALK_SIDE_GFX_IDXES[] = {0, 1, 2, 3};

constexpr std::uint16_t BUTTERFLY_WAIT_UPDATES = 3;
constexpr std::uint16_t BUTTERFLY_IDLE_GFX_IDXES[] = {0, 1, 2, 3};
constexpr std::uint16_t BUTTERFLY_ATTACK_GFX_IDXES[] = {4, 5};

constexpr bn::array<critter_animation_infos, ut::size_of_enum<ldtk::gen::species_kind>()> INFOS{
    // slime
    critter_animation_infos(
        critter_animation_infos_builder()
            .set_info(critter_animation_kind::IDLE, direction::DOWN,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = false,
                          .vertical_flip = false,
                          .wait_updates = 5,
                          .graphics_indexes = SLIME_IDLE_GFX_IDXES,
                      })
            .set_info(critter_animation_kind::DEAD, direction::DOWN,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = false,
                          .vertical_flip = false,
                          .wait_updates = std::numeric_limits<decltype(sprite_animation_info::wait_updates)>::max(),
                          .graphics_indexes = bn::span(SLIME_IDLE_GFX_IDXES, 1),
                      })
            .set_info(critter_animation_kind::WALK, direction::UP,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = false,
                          .vertical_flip = false,
                          .wait_updates = 0,
                          .graphics_indexes = SLIME_WALK_UP_GFX_IDXES,
                      })
            .set_info(critter_animation_kind::WALK, direction::DOWN,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = false,
                          .vertical_flip = false,
                          .wait_updates = 0,
                          .graphics_indexes = SLIME_WALK_DOWN_GFX_IDXES,
                      })
            .set_info(critter_animation_kind::WALK, direction::LEFT,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = false,
                          .vertical_flip = false,
                          .wait_updates = 0,
                          .graphics_indexes = SLIME_WALK_SIDE_GFX_IDXES,
                      })
            .set_info(critter_animation_kind::WALK, direction::RIGHT,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = true,
                          .vertical_flip = false,
                          .wait_updates = 0,
                          .graphics_indexes = SLIME_WALK_SIDE_GFX_IDXES,
                      })
            .set_info(critter_animation_kind::ATTACK, direction::UP,
                      sprite_animation_info{
                          .forever = false,
                          .horizontal_flip = false,
                          .vertical_flip = false,
                          .wait_updates = 3,
                          .graphics_indexes = SLIME_ATTACK_UP_GFX_IDXES,
                      })
            .set_info(critter_animation_kind::ATTACK, direction::DOWN,
                      sprite_animation_info{
                          .forever = false,
                          .horizontal_flip = false,
                          .vertical_flip = false,
                          .wait_updates = 3,
                          .graphics_indexes = SLIME_ATTACK_DOWN_GFX_IDXES,
                      })
            .set_info(critter_animation_kind::ATTACK, direction::LEFT,
                      sprite_animation_info{
                          .forever = false,
                          .horizontal_flip = true,
                          .vertical_flip = false,
                          .wait_updates = 3,
                          .graphics_indexes = SLIME_ATTACK_SIDE_GFX_IDXES,
                      })
            .set_info(critter_animation_kind::ATTACK, direction::RIGHT,
                      sprite_animation_info{
                          .forever = false,
                          .horizontal_flip = false,
                          .vertical_flip = false,
                          .wait_updates = 3,
                          .graphics_indexes = SLIME_ATTACK_SIDE_GFX_IDXES,
                      })),
    // lizard
    critter_animation_infos(
        critter_animation_infos_builder()
            .set_info(critter_animation_kind::IDLE, direction::UP,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = false,
                          .vertical_flip = true,
                          .wait_updates = std::numeric_limits<decltype(sprite_animation_info::wait_updates)>::max(),
                          .graphics_indexes = LIZARD_IDLE_VERT_GFX_IDXES,
                      })
            .set_info(critter_animation_kind::IDLE, direction::DOWN,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = false,
                          .vertical_flip = false,
                          .wait_updates = std::numeric_limits<decltype(sprite_animation_info::wait_updates)>::max(),
                          .graphics_indexes = LIZARD_IDLE_VERT_GFX_IDXES,
                      })
            .set_info(critter_animation_kind::IDLE, direction::LEFT,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = true,
                          .vertical_flip = false,
                          .wait_updates = std::numeric_limits<decltype(sprite_animation_info::wait_updates)>::max(),
                          .graphics_indexes = LIZARD_IDLE_SIDE_GFX_IDXES,
                      })
            .set_info(critter_animation_kind::IDLE, direction::RIGHT,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = false,
                          .vertical_flip = false,
                          .wait_updates = std::numeric_limits<decltype(sprite_animation_info::wait_updates)>::max(),
                          .graphics_indexes = LIZARD_IDLE_SIDE_GFX_IDXES,
                      })
            .set_info(critter_animation_kind::DEAD, direction::UP,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = false,
                          .vertical_flip = true,
                          .wait_updates = std::numeric_limits<decltype(sprite_animation_info::wait_updates)>::max(),
                          .graphics_indexes = bn::span(LIZARD_IDLE_VERT_GFX_IDXES, 1),
                      })
            .set_info(critter_animation_kind::DEAD, direction::DOWN,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = false,
                          .vertical_flip = false,
                          .wait_updates = std::numeric_limits<decltype(sprite_animation_info::wait_updates)>::max(),
                          .graphics_indexes = bn::span(LIZARD_IDLE_VERT_GFX_IDXES, 1),
                      })
            .set_info(critter_animation_kind::DEAD, direction::LEFT,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = true,
                          .vertical_flip = false,
                          .wait_updates = std::numeric_limits<decltype(sprite_animation_info::wait_updates)>::max(),
                          .graphics_indexes = bn::span(LIZARD_IDLE_SIDE_GFX_IDXES, 1),
                      })
            .set_info(critter_animation_kind::DEAD, direction::RIGHT,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = false,
                          .vertical_flip = false,
                          .wait_updates = std::numeric_limits<decltype(sprite_animation_info::wait_updates)>::max(),
                          .graphics_indexes = bn::span(LIZARD_IDLE_SIDE_GFX_IDXES, 1),
                      })
            .set_info(critter_animation_kind::WALK, direction::UP,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = false,
                          .vertical_flip = true,
                          .wait_updates = 3,
                          .graphics_indexes = LIZARD_WALK_VERT_GFX_IDXES,
                      })
            .set_info(critter_animation_kind::WALK, direction::DOWN,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = false,
                          .vertical_flip = false,
                          .wait_updates = 3,
                          .graphics_indexes = LIZARD_WALK_VERT_GFX_IDXES,
                      })
            .set_info(critter_animation_kind::WALK, direction::LEFT,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = true,
                          .vertical_flip = false,
                          .wait_updates = 3,
                          .graphics_indexes = LIZARD_WALK_SIDE_GFX_IDXES,
                      })
            .set_info(critter_animation_kind::WALK, direction::RIGHT,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = false,
                          .vertical_flip = false,
                          .wait_updates = 3,
                          .graphics_indexes = LIZARD_WALK_SIDE_GFX_IDXES,
                      })
            .set_info(critter_animation_kind::ATTACK, direction::UP,
                      sprite_animation_info{
                          .forever = false,
                          .horizontal_flip = false,
                          .vertical_flip = true,
                          .wait_updates = 1,
                          .graphics_indexes = LIZARD_ATTACK_VERT_GFX_IDXES,
                      })
            .set_info(critter_animation_kind::ATTACK, direction::DOWN,
                      sprite_animation_info{
                          .forever = false,
                          .horizontal_flip = false,
                          .vertical_flip = false,
                          .wait_updates = 1,
                          .graphics_indexes = LIZARD_ATTACK_VERT_GFX_IDXES,
                      })
            .set_info(critter_animation_kind::ATTACK, direction::LEFT,
                      sprite_animation_info{
                          .forever = false,
                          .horizontal_flip = true,
                          .vertical_flip = false,
                          .wait_updates = 1,
                          .graphics_indexes = LIZARD_ATTACK_SIDE_GFX_IDXES,
                      })
            .set_info(critter_animation_kind::ATTACK, direction::RIGHT,
                      sprite_animation_info{
                          .forever = false,
                          .horizontal_flip = false,
                          .vertical_flip = false,
                          .wait_updates = 1,
                          .graphics_indexes = LIZARD_ATTACK_SIDE_GFX_IDXES,
                      })),
    // eel
    critter_animation_infos(
        critter_animation_infos_builder()
            .set_info(critter_animation_kind::IDLE, direction::LEFT,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = false,
                          .vertical_flip = false,
                          .wait_updates = std::numeric_limits<decltype(sprite_animation_info::wait_updates)>::max(),
                          .graphics_indexes = EEL_IDLE_SIDE_GFX_IDXES,
                      })
            .set_info(critter_animation_kind::IDLE, direction::RIGHT,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = true,
                          .vertical_flip = false,
                          .wait_updates = std::numeric_limits<decltype(sprite_animation_info::wait_updates)>::max(),
                          .graphics_indexes = EEL_IDLE_SIDE_GFX_IDXES,
                      })
            .set_info(critter_animation_kind::IDLE, direction::UP,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = false,
                          .vertical_flip = false,
                          .wait_updates = std::numeric_limits<decltype(sprite_animation_info::wait_updates)>::max(),
                          .graphics_indexes = EEL_IDLE_VERT_GFX_IDXES,
                      })
            .set_info(critter_animation_kind::IDLE, direction::DOWN,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = false,
                          .vertical_flip = true,
                          .wait_updates = std::numeric_limits<decltype(sprite_animation_info::wait_updates)>::max(),
                          .graphics_indexes = EEL_IDLE_VERT_GFX_IDXES,
                      })
            .set_info(critter_animation_kind::DEAD, direction::LEFT,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = false,
                          .vertical_flip = false,
                          .wait_updates = std::numeric_limits<decltype(sprite_animation_info::wait_updates)>::max(),
                          .graphics_indexes = bn::span(EEL_IDLE_SIDE_GFX_IDXES, 1),
                      })
            .set_info(critter_animation_kind::DEAD, direction::RIGHT,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = true,
                          .vertical_flip = false,
                          .wait_updates = std::numeric_limits<decltype(sprite_animation_info::wait_updates)>::max(),
                          .graphics_indexes = bn::span(EEL_IDLE_SIDE_GFX_IDXES, 1),
                      })
            .set_info(critter_animation_kind::DEAD, direction::UP,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = false,
                          .vertical_flip = false,
                          .wait_updates = std::numeric_limits<decltype(sprite_animation_info::wait_updates)>::max(),
                          .graphics_indexes = bn::span(EEL_IDLE_VERT_GFX_IDXES, 1),
                      })
            .set_info(critter_animation_kind::DEAD, direction::DOWN,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = false,
                          .vertical_flip = true,
                          .wait_updates = std::numeric_limits<decltype(sprite_animation_info::wait_updates)>::max(),
                          .graphics_indexes = bn::span(EEL_IDLE_VERT_GFX_IDXES, 1),
                      })
            .set_info(critter_animation_kind::WALK, direction::LEFT,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = false,
                          .vertical_flip = false,
                          .wait_updates = EEL_WAIT_UPDATES,
                          .graphics_indexes = EEL_WALK_SIDE_GFX_IDXES,
                      })
            .set_info(critter_animation_kind::WALK, direction::RIGHT,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = true,
                          .vertical_flip = false,
                          .wait_updates = EEL_WAIT_UPDATES,
                          .graphics_indexes = EEL_WALK_SIDE_GFX_IDXES,
                      })
            .set_info(critter_animation_kind::WALK, direction::UP,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = false,
                          .vertical_flip = false,
                          .wait_updates = EEL_WAIT_UPDATES,
                          .graphics_indexes = EEL_WALK_VERT_GFX_IDXES,
                      })
            .set_info(critter_animation_kind::WALK, direction::DOWN,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = false,
                          .vertical_flip = true,
                          .wait_updates = EEL_WAIT_UPDATES,
                          .graphics_indexes = EEL_WALK_VERT_GFX_IDXES,
                      })
            .set_info(critter_animation_kind::ATTACK, direction::LEFT,
                      sprite_animation_info{
                          .forever = false,
                          .horizontal_flip = false,
                          .vertical_flip = false,
                          .wait_updates = EEL_WAIT_UPDATES,
                          .graphics_indexes = EEL_WALK_SIDE_GFX_IDXES,
                      })
            .set_info(critter_animation_kind::ATTACK, direction::RIGHT,
                      sprite_animation_info{
                          .forever = false,
                          .horizontal_flip = true,
                          .vertical_flip = false,
                          .wait_updates = EEL_WAIT_UPDATES,
                          .graphics_indexes = EEL_WALK_SIDE_GFX_IDXES,
                      })
            .set_info(critter_animation_kind::ATTACK, direction::UP,
                      sprite_animation_info{
                          .forever = false,
                          .horizontal_flip = false,
                          .vertical_flip = false,
                          .wait_updates = EEL_WAIT_UPDATES,
                          .graphics_indexes = EEL_WALK_VERT_GFX_IDXES,
                      })
            .set_info(critter_animation_kind::ATTACK, direction::DOWN,
                      sprite_animation_info{
                          .forever = false,
                          .horizontal_flip = false,
                          .vertical_flip = true,
                          .wait_updates = EEL_WAIT_UPDATES,
                          .graphics_indexes = EEL_WALK_VERT_GFX_IDXES,
                      })),
    // butterfly
    critter_animation_infos(
        critter_animation_infos_builder()
            .set_info(critter_animation_kind::IDLE, direction::DOWN,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = false,
                          .vertical_flip = false,
                          .wait_updates = BUTTERFLY_WAIT_UPDATES,
                          .graphics_indexes = BUTTERFLY_IDLE_GFX_IDXES,
                      })
            .set_info(critter_animation_kind::DEAD, direction::DOWN,
                      sprite_animation_info{
                          .forever = true,
                          .horizontal_flip = false,
                          .vertical_flip = false,
                          .wait_updates = std::numeric_limits<decltype(sprite_animation_info::wait_updates)>::max(),
                          .graphics_indexes = bn::span(BUTTERFLY_IDLE_GFX_IDXES, 1),
                      })
            .set_info(critter_animation_kind::ATTACK, direction::DOWN,
                      sprite_animation_info{
                          .forever = false,
                          .horizontal_flip = false,
                          .vertical_flip = false,
                          .wait_updates = BUTTERFLY_WAIT_UPDATES,
                          .graphics_indexes = BUTTERFLY_ATTACK_GFX_IDXES,
                      })),
};

} // namespace

auto critter_animation_infos::get(ldtk::gen::species_kind species) -> const critter_animation_infos&
{
    BN_ASSERT(static_cast<int>(species) < ut::size_of_enum<decltype(species)>(),
              "Invalid species kind: ", static_cast<int>(species));

    return INFOS[static_cast<int>(species)];
}

} // namespace mc::gm::cfg
