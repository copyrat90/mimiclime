#pragma once

#include <bn_string_view.h>

#include <meta>
#include <string_view>
#include <type_traits>

namespace mc::ut
{

template <typename Enum>
    requires std::is_enum_v<Enum>
constexpr int size_of_enum()
{
    return static_cast<int>(std::meta::enumerators_of(^^Enum).size());
}

template <typename Enum>
    requires std::is_enum_v<Enum>
constexpr auto enum_to_string(Enum value) -> bn::string_view
{
    bn::string_view result;
    template for (constexpr auto e : std::define_static_array(std::meta::enumerators_of(^^Enum)))
    {
        if (value == [:e:])
        {
            std::string_view sv = std::meta::identifier_of(e);
            result = bn::string_view(sv.data(), sv.size());
        }
    }
    return result;
}

} // namespace mc::ut
