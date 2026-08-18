#pragma once

#include "ut/configs.h"
#include "ut/enum_utils.h"

#include <utility>

namespace mc::gm
{

constexpr auto get_ingame_text(ldtk::gen::ingame_text_kind text_kind, ldtk::gen::lang lang) -> bn::string_view
{
    static constexpr auto INGAME_TEXTS =
        mc::ut::get_config_entity(ldtk::gen::entity_ident::system_texts)
            .get_field(ldtk::gen::entity_field_ident::ENTITY_system_texts_FIELD_ingame_texts)
            .get<bn::span<const bn::string_view>>();

    static_assert(INGAME_TEXTS.size() ==
                      ut::size_of_enum<ldtk::gen::lang>() * ut::size_of_enum<ldtk::gen::ingame_text_kind>(),
                  "Missing ingame text for some language(s)");

    const auto text_kind_idx = std::to_underlying(text_kind);
    const auto lang_idx = std::to_underlying(lang);

    BN_ASSERT(text_kind_idx < ut::size_of_enum<ldtk::gen::ingame_text_kind>(),
              "Invalid ingame text kind: ", text_kind_idx);
    BN_ASSERT(lang_idx < ut::size_of_enum<ldtk::gen::lang>(), "Invalid lang: ", lang_idx);

    return INGAME_TEXTS[text_kind_idx * ut::size_of_enum<ldtk::gen::lang>() + lang_idx];
}

} // namespace mc::gm
