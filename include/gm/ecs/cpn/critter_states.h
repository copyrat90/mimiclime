#pragma once

#include "gm/ecs/cpn/impl/critter_substates_buffer.h"

#include "gm/critter_action.h"
#include "gm/critter_animation_kind.h"
#include "gm/direction.h"

#include <bn_fixed_point.h>

#include <gba/bits/ecs/entity.hpp>

#include <cstdint>
#include <new>

#include "ldtk_gen_enums.h"

namespace mc::gm::cfg
{
class sprite_datas;
}

namespace mc::gm::ecs::cpn
{

struct critter_states final
{
private:
    const bool _is_player;
    ldtk::gen::species_kind _species;

    std::uint16_t _hp;

public:
    std::uint8_t invincible_shared_counter;

    critter_action executing_action;
    critter_animation_kind executing_animation;
    direction facing_direction; // only 4 directions

    critter_action input_action;
    direction input_direction;
    bn::fixed_point input_velocity;

    bn::fixed_point target_position;

    bn::fixed_point knockback_velocity;
    std::uint8_t knockback_countdown;

    gba::entity devour_critter;

    std::uint16_t attack_countdown;
    std::uint16_t devour_countdown;

    impl::critter_substates_buffer substates_buffer;

public:
    bool is_player() const
    {
        return _is_player;
    }

    auto species() const -> ldtk::gen::species_kind
    {
        return _species;
    }

    void change_species(ldtk::gen::species_kind);

    auto sprite_datas() const -> const cfg::sprite_datas&;

    auto hp() const -> decltype(_hp)
    {
        return _hp;
    }

    bool alive() const
    {
        return _hp != 0;
    }

    bool invincible() const
    {
        return invincible_shared_counter != 0;
    }

    void change_hp(int diff);

    bool can_move() const;
    bool can_attack() const;
    bool can_devour() const;
    bool can_interact() const;

public:
    template <typename Substates>
    auto substates() -> Substates&;

    template <typename Substates>
    auto substates() const -> const Substates&;

public:
    critter_states(bool is_player_, ldtk::gen::species_kind);
    ~critter_states();

private:
    void construct_substates(ldtk::gen::species_kind);

    void destroy_substates();
};

} // namespace mc::gm::ecs::cpn

#include "gm/ecs/cpn/critter_states.inl"
