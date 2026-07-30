#pragma once

#include "model/sprite_frame.h"

#include "model/json_t.h"

#include <cstdint>
#include <filesystem>
#include <string_view>
#include <unordered_set>
#include <vector>

extern "C"
{
struct SDL_Texture;
struct SDL_Renderer;
}

namespace mcedit::model
{

struct sprite_sheet final
{
    bool has_changes;

    std::filesystem::path image_path;
    json_t json;

    SDL_Texture& texture;
    unsigned texture_width;
    unsigned texture_height;
    unsigned frame_width;
    unsigned frame_height;

    std::vector<sprite_frame> frames;

    sprite_sheet(const std::filesystem::path& img_path, SDL_Renderer&,
                 const std::unordered_set<std::string_view>& projectile_kind_set);
    ~sprite_sheet();

    sprite_sheet(const sprite_sheet&) = delete;
    sprite_sheet& operator=(const sprite_sheet&) = delete;

    void save_changes();
};

} // namespace mcedit::model
