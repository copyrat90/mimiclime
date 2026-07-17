#pragma once

#include "model/sprite_frame.h"

#include <cstdint>
#include <filesystem>
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
    std::filesystem::path image_path;
    SDL_Texture& texture;
    unsigned texture_width;
    unsigned texture_height;
    unsigned frame_width;
    unsigned frame_height;

    std::vector<sprite_frame> frames;

    sprite_sheet(const std::filesystem::path& img_path, SDL_Renderer&);
    ~sprite_sheet();

    sprite_sheet(const sprite_sheet&) = delete;
    sprite_sheet& operator=(const sprite_sheet&) = delete;
};

} // namespace mcedit::model
