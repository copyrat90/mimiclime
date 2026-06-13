#pragma once

#include <meta>
#include <type_traits>

namespace mc::ut
{

template <typename Enum>
    requires std::is_enum_v<Enum>
constexpr int size_of_enum() {
    return static_cast<int>(std::meta::enumerators_of(^^Enum).size());
}

}
