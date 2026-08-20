#pragma once

#include "gm/cfg/room_entrance.h"

#include <bn_array.h>
#include <bn_bitset.h>

#include "ldtk_gen_enums.h"

namespace ibn
{
class bit_stream_measurer;
class bit_stream_writer;
class bit_stream_reader;
} // namespace ibn

namespace mc::gm
{

struct game_save final
{
public:
    const unsigned slot;

    cfg::room_entrance room_entrance;
    ldtk::gen::species_kind player_species;

private:
    static constexpr int MAX_GAME_FLAG_COUNT = 256;
    bn::array<bn::bitset_ref::element_t, MAX_GAME_FLAG_COUNT / 8> _game_flag_raw;
    bn::bitset_ref _game_flag;

public:
    game_save(unsigned slot);

    bool game_flag(ldtk::gen::game_flag) const;
    void set_game_flag(ldtk::gen::game_flag, bool value);

    void reset();

    bool load();
    void save();

    void measure(ibn::bit_stream_measurer& measurer) const;
    void write(ibn::bit_stream_writer& writer) const;
    void read(ibn::bit_stream_reader& reader);

private:
    auto save_location(bool secondary) const -> unsigned;
};

} // namespace mc::gm
