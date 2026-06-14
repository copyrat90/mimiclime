#pragma once

#include "chr_slime.h"

#include <algorithm>
#include <cstddef>
#include <new>

#include "ldtk_gen_enums.h"

namespace mc::gm::ecs::cpn
{

struct character_proxy final
{
public:
    void change_species(ldtk::gen::species_kind);

public:
    auto species() const -> ldtk::gen::species_kind
    {
        return _species;
    }

    auto character() -> gbatool::Character&
    {
        return *std::launder(reinterpret_cast<gbatool::Character*>(_character_buffer));
    }

    auto character() const -> const gbatool::Character&
    {
        return *std::launder(reinterpret_cast<const gbatool::Character*>(_character_buffer));
    }

public:
    character_proxy(ldtk::gen::species_kind, const bn::fixed_point& top_left_position, const bn::camera_ptr&);
    ~character_proxy();

    character_proxy(const character_proxy&) = delete;
    character_proxy& operator=(const character_proxy&) = delete;

private:
    void construct_character(ldtk::gen::species_kind, const bn::fixed_point& top_left_position, const bn::camera_ptr&);
    void destroy_character();

private:
    static constexpr auto MAX_CHR_SIZE = std::max({sizeof(gbatool::Chr_Slime)});
    static constexpr auto MAX_CHR_ALIGN = std::max({alignof(gbatool::Chr_Slime)});

    alignas(MAX_CHR_ALIGN) std::byte _character_buffer[MAX_CHR_SIZE];

    ldtk::gen::species_kind _species;
};

} // namespace mc::gm::ecs::cpn
