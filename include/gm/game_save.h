#pragma once

#include "gm/cfg/room_entrance.h"

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
    const unsigned slot;

    cfg::room_entrance room_entrance;
    ldtk::gen::species_kind player_species;

    game_save(unsigned slot);

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
