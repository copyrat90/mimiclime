#pragma once

#include <meta>
#include <optional>
#include <string_view>
#include <type_traits>

namespace mcedit::util
{

template <typename Enum>
    requires std::is_enum_v<Enum>
constexpr int size_of_enum()
{
    return static_cast<int>(std::meta::enumerators_of(^^Enum).size());
}

template <typename Enum>
    requires std::is_enum_v<Enum>
constexpr auto enum_to_string(Enum value) -> std::string_view
{
    std::string_view result;
    template for (constexpr auto e : std::define_static_array(std::meta::enumerators_of(^^Enum)))
    {
        if (value == [:e:])
            result = std::meta::identifier_of(e);
    }
    return result;
}

template <typename Enum>
    requires std::is_enum_v<Enum>
constexpr auto string_to_enum(std::string_view str) -> std::optional<Enum>
{
    std::optional<Enum> result;
    template for (constexpr auto e : std::define_static_array(std::meta::enumerators_of(^^Enum)))
    {
        if (str == std::meta::identifier_of(e))
            result = [:e:];
    }
    return result;
}

} // namespace mcedit
