#include "model/sprite_sheet.h"

#include "util/enum_utils.h"

#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>

#include <format>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <string>

namespace mcedit::model
{

sprite_sheet::sprite_sheet(const std::filesystem::path& img_path, SDL_Renderer& renderer)
    : has_changes(false), image_path(img_path), texture([&] -> SDL_Texture& {
          SDL_Surface* surface = IMG_Load(img_path.string().c_str());
          if (!surface)
              throw std::runtime_error(SDL_GetError());

          struct surface_destroyer_t final
          {
              SDL_Surface& _surface;
              ~surface_destroyer_t()
              {
                  SDL_DestroySurface(&_surface);
              }
          } surface_destroyer(*surface);

          if (surface->w <= 0)
              throw std::runtime_error(std::format("Invalid width: {}", surface->w));
          if (surface->h <= 0)
              throw std::runtime_error(std::format("Invalid height: {}", surface->h));

          this->texture_width = surface->w;
          this->texture_height = surface->h;

          SDL_Color transparent_color(0, 255, 0, 255);
          SDL_Palette* palette = SDL_GetSurfacePalette(surface);
          if (palette && palette->ncolors > 0)
              transparent_color = palette->colors[0];
          SDL_SetSurfaceColorKey(surface, true,
                                 SDL_MapSurfaceRGBA(surface, transparent_color.r, transparent_color.g,
                                                    transparent_color.b, transparent_color.a));

          SDL_Texture* texture = SDL_CreateTextureFromSurface(&renderer, surface);
          if (!texture)
              throw std::runtime_error(SDL_GetError());

          return *texture;
      }())
{
    struct texture_destroyer_t
    {
        SDL_Texture* texture;
        ~texture_destroyer_t()
        {
            if (texture)
                SDL_DestroyTexture(texture);
        }
        texture_destroyer_t(SDL_Texture& tex) : texture(&tex)
        {
        }
    } texture_destroyer(this->texture);

    std::filesystem::path json_path(img_path);
    json_path.replace_extension(".json");

    {
        std::ifstream json_file(json_path);
        const auto prev_except = json_file.exceptions();
        json_file.exceptions(std::ios_base::failbit);
        json_file.exceptions(prev_except);

        json_file >> this->json;
    }

    if (this->json["type"] != "sprite")
    {
        throw std::runtime_error("Not a sprite type");
    }

    if (this->json.contains("height"))
    {
        if (!this->json["height"].is_number_unsigned() || this->json["height"] == 0)
            throw std::runtime_error("Invalid height");
        this->frame_height = this->json["height"];
    }
    else
        this->frame_height = this->texture_height;

    if (this->json.contains("width"))
    {
        if (!this->json["width"].is_number_unsigned() || this->json["width"] == 0)
            throw std::runtime_error("Invalid width");
        this->frame_width = this->json["width"];
    }
    else
        this->frame_width = this->texture_width;

    const unsigned total_frames = this->texture_width * this->texture_height / this->frame_width / this->frame_height;
    this->frames.resize(total_frames);

    if (this->json.contains("mcedit"))
    {
        json_t& root = this->json["mcedit"];

        if (root.contains("collisions"))
        {
            json_t& colls_arr = root["collisions"];

            for (std::size_t i = 0; i < colls_arr.size(); ++i)
            {
                json_t& colls = colls_arr[i];
                sprite_frame& frame = this->frames[i];

                if (colls.contains("wallboxes"))
                {
                    frame.wallboxes.reserve(colls["wallboxes"].size());
                    for (json_t& box : colls["wallboxes"])
                    {
                        frame.wallboxes.push_back(collision_box{
                            .x = box["x"].get<std::int8_t>(),
                            .y = box["y"].get<std::int8_t>(),
                            .width = box["width"].get<std::uint8_t>(),
                            .height = box["height"].get<std::uint8_t>(),
                        });
                    }
                }

                if (colls.contains("hurtboxes"))
                {
                    frame.hurtboxes.reserve(colls["hurtboxes"].size());
                    for (json_t& box : colls["hurtboxes"])
                    {
                        frame.hurtboxes.push_back(collision_box{
                            .x = box["x"].get<std::int8_t>(),
                            .y = box["y"].get<std::int8_t>(),
                            .width = box["width"].get<std::uint8_t>(),
                            .height = box["height"].get<std::uint8_t>(),
                        });
                    }
                }

                if (colls.contains("hitboxes"))
                {
                    frame.hitboxes.reserve(colls["hitboxes"].size());
                    for (json_t& box : colls["hitboxes"])
                    {
                        frame.hitboxes.push_back(collision_box{
                            .x = box["x"].get<std::int8_t>(),
                            .y = box["y"].get<std::int8_t>(),
                            .width = box["width"].get<std::uint8_t>(),
                            .height = box["height"].get<std::uint8_t>(),
                        });
                    }
                }

                if (colls.contains("projectiles"))
                {
                    frame.projectiles.reserve(colls["projectiles"].size());
                    for (json_t& proj : colls["projectiles"])
                    {
                        const std::string proj_kind_str = proj["kind"].get<std::string>();
                        const auto projectile_kind = util::sv_to_enum<decltype(projectile::kind)>(proj_kind_str);
                        if (!projectile_kind.has_value())
                            throw std::runtime_error(std::format("Invalid projectile kind string: {}", proj_kind_str));

                        const std::string dir_str = proj["direction"].get<std::string>();
                        const auto direction = util::sv_to_enum<decltype(projectile::direction)>(dir_str);
                        if (!direction.has_value())
                            throw std::runtime_error(std::format("Invalid direction string: {}", dir_str));

                        frame.projectiles.push_back(projectile{
                            .kind = *projectile_kind,
                            .x = proj["x"].get<std::int8_t>(),
                            .y = proj["y"].get<std::int8_t>(),
                            .direction = *direction,
                            .speed = proj["speed"].get<float>(),
                        });
                    }
                }
            }
        }
    }

    texture_destroyer.texture = nullptr;
}

sprite_sheet::~sprite_sheet()
{
    SDL_DestroyTexture(&texture);
}

void sprite_sheet::save_changes()
{
    if (!this->has_changes)
        return;

    json_t& root = this->json["mcedit"];
    json_t& colls = root["collisions"];

    colls.clear();

    for (const sprite_frame& frame : this->frames)
    {
        json_t& col = colls.emplace_back();

        static constexpr auto add_boxes = [](decltype((frame.wallboxes)) boxes, std::string_view boxes_identifier,
                                             json_t& col) {
            for (const auto& box : boxes)
            {
                json_t& bx = col[boxes_identifier].emplace_back();
                bx["x"] = box.x;
                bx["y"] = box.y;
                bx["width"] = box.width;
                bx["height"] = box.height;
            }
        };

        add_boxes(frame.wallboxes, "wallboxes", col);
        add_boxes(frame.hurtboxes, "hurtboxes", col);
        add_boxes(frame.hitboxes, "hitboxes", col);

        for (const auto& proj : frame.projectiles)
        {
            json_t& pj = col["projectiles"].emplace_back();
            pj["kind"] = util::enum_to_sv(proj.kind);
            pj["x"] = proj.x;
            pj["y"] = proj.y;
            pj["direction"] = util::enum_to_sv(proj.direction);
            pj["speed"] = proj.speed;
        }
    }

    std::filesystem::path json_path(this->image_path);
    json_path.replace_extension(".json");
    {
        std::ofstream json_file(json_path);
        json_file.exceptions(std::ios_base::failbit);

        json_file << std::setw(4) << this->json << "\n";
    }

    this->has_changes = false;
}

} // namespace mcedit::model
