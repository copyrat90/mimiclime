#pragma once

#include <nlohmann/json.hpp>

namespace mcedit::model
{

using json_t = nlohmann::basic_json<nlohmann::ordered_map, std::vector, std::string, bool, std::int32_t, std::uint32_t, float,
                                    std::allocator, nlohmann::adl_serializer, std::vector<std::uint8_t>, void>;

}
