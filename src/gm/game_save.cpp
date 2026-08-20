#include "gm/game_save.h"

#include "ut/configs.h"
#include "ut/enum_utils.h"

#include "ibn_sram_rw.h"

#include <utility>

namespace mc::gm
{

namespace
{

constexpr bn::string_view SAVE_MAGIC = "MICLa";

constexpr unsigned MAX_GAME_SAVE_SIZE = 4096;
constexpr unsigned MAX_SLOTS = (bn::sram::size() - 512) / (2 * MAX_GAME_SAVE_SIZE);

constexpr std::uint32_t FOOTER = 0x5A7EF001; // SAVE FOOT

auto get_initial_entrance() -> gm::cfg::room_entrance
{
    static constexpr const ldtk::entity& GAME_INIT_EXIT =
        ut::get_config_entity(ldtk::gen::entity_ident::exit, ldtk::gen::layer_ident::exits);

    return gm::cfg::room_entrance::from_exit(GAME_INIT_EXIT);
}

} // namespace

game_save::game_save(unsigned slot_)
    : slot(slot_), room_entrance(static_cast<ldtk::gen::level_ident>(0), static_cast<ldtk::gen::entity_iid>(0)),
      player_species(static_cast<ldtk::gen::species_kind>(0)), _game_flag_raw{}, _game_flag(_game_flag_raw)
{
    static_assert(ut::size_of_enum<ldtk::gen::game_flag>() <= MAX_GAME_FLAG_COUNT, "Too many game flags");

    BN_ASSERT(slot_ < MAX_SLOTS, "OOB slot: ", slot_, " (max ", MAX_SLOTS - 1, ")");

    reset();
}

bool game_save::game_flag(ldtk::gen::game_flag flag) const
{
    const auto flag_idx = std::to_underlying(flag);
    BN_ASSERT(flag_idx < ut::size_of_enum<ldtk::gen::game_flag>(), "Invalid game flag: ", static_cast<int>(flag_idx));

    return _game_flag[flag_idx];
}

void game_save::set_game_flag(ldtk::gen::game_flag flag, bool value)
{
    const auto flag_idx = std::to_underlying(flag);
    BN_ASSERT(flag_idx < ut::size_of_enum<ldtk::gen::game_flag>(), "Invalid game flag: ", static_cast<int>(flag_idx));

    _game_flag[flag_idx] = value;
}

void game_save::reset()
{
    this->room_entrance = get_initial_entrance();
    this->player_species = ldtk::gen::species_kind::slime;
    this->_game_flag.reset();
}

bool game_save::load()
{
    ibn::sram_rw rw(SAVE_MAGIC, save_location(false), save_location(true));

    const bool loaded = rw.read(*this);

    // If read fails, it might be halfway-loaded (inconsistent state),
    // so we reset again.
    if (!loaded)
        reset();

    return loaded;
}

void game_save::save()
{
    ibn::sram_rw rw(SAVE_MAGIC, save_location(false), save_location(true));
    rw.write(*this);
}

void game_save::measure(ibn::bit_stream_measurer& measurer) const
{
    measurer
        .write(this->room_entrance.room_id())                 // 4 bytes
        .write(this->room_entrance.entrance_id())             // 4 bytes
        .write(this->player_species)                          // 1 byte
        .write(_game_flag.data(), _game_flag.elements_size()) // 32 bytes
        .write(FOOTER);                                       // 4 bytes

    BN_ASSERT(measurer.used_bytes() <= MAX_GAME_SAVE_SIZE, "game save size overflow");
}

void game_save::write(ibn::bit_stream_writer& writer) const
{
    writer
        .write(this->room_entrance.room_id())                 // 4 bytes
        .write(this->room_entrance.entrance_id())             // 4 bytes
        .write(this->player_species)                          // 1 byte
        .write(_game_flag.data(), _game_flag.elements_size()) // 32 bytes
        .write(FOOTER);                                       // 4 bytes
}

void game_save::read(ibn::bit_stream_reader& reader)
{
    std::uint32_t footer = 0;

    ldtk::gen::level_ident room_entrance_room_id = static_cast<ldtk::gen::level_ident>(0);
    ldtk::gen::entity_iid room_entrance_entrance_id = static_cast<ldtk::gen::entity_iid>(0);

    reader
        .read(room_entrance_room_id)                        // 4 bytes
        .read(room_entrance_entrance_id)                    // 4 bytes
        .read(this->player_species)                         // 1 byte
        .read(_game_flag_raw.data(), _game_flag_raw.size()) // 32 bytes
        .read(footer);                                      // 4 bytes

    if (footer != FOOTER)
        reader.set_fail();
    else
    {
        this->room_entrance = cfg::room_entrance(room_entrance_room_id, room_entrance_entrance_id);
    }
}

auto game_save::save_location(bool secondary) const -> unsigned
{
    return this->slot * 2 * MAX_GAME_SAVE_SIZE + (secondary ? MAX_GAME_SAVE_SIZE : 0);
}

} // namespace mc::gm
