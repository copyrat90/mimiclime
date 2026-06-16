#pragma once

#include <gba/ecs>

#include <concepts>

namespace mc::gm::ecs
{

template <typename T>
concept registry_concept = requires(T reg, const gba::entity e) {
    { reg.create() } -> std::same_as<const gba::entity>;
    { reg.destroy(e) } -> std::same_as<void>;
    { reg.valid(e) } -> std::same_as<bool>;
    { reg.size() } -> std::same_as<std::size_t>;
    { reg.clear() } -> std::same_as<void>;
};

} // namespace mc::gm::ecs
