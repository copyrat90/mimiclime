// Dear ImGui: standalone example application for SDL3 + SDL_Renderer
// (SDL is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context
// creation, etc.)

// Learn about Dear ImGui:
// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).
// - Introduction, links and more at the top of imgui.cpp

// Important to understand: SDL_Renderer is an _optional_ component of SDL3.
// For a multi-platform app consider using e.g. SDL+DirectX on Windows and SDL+OpenGL on Linux/OSX.

#include "ctrl/resources_edits.h"
#include "model/resources.h"
#include "view/main_menu_bar.h"
#include "view/popup_modals.h"
#include "view/select_sprite_window.h"
#include "view/sprite_collision_editor_window.h"

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

#include <IconsFontAwesome6.h>
#include <ImGuiNotify.hpp>
#include <fa-solid-900.h>

#include <SDL3/SDL.h>

#include <iostream>
#include <random>

#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif

// Main code
int main(int, char**)
{
    // Setup SDL
    // [If using SDL_MAIN_USE_CALLBACKS: all code below until the main loop starts would likely be your SDL_AppInit()
    // function]
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD))
    {
        std::cerr << "Error: SDL_Init(): " << SDL_GetError() << std::endl;
        return 1;
    }

    struct sdl_quitter_t final
    {
        ~sdl_quitter_t()
        {
            SDL_Quit();
        }
    } sdl_quitter;

    // Create window with SDL_Renderer graphics context
    float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    SDL_WindowFlags window_flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN | SDL_WINDOW_HIGH_PIXEL_DENSITY;
    SDL_Window* window =
        SDL_CreateWindow("mimiclime editor", (int)(1280 * main_scale), (int)(800 * main_scale), window_flags);
    if (window == nullptr)
    {
        std::cerr << "Error: SDL_CreateWindow(): " << SDL_GetError() << std::endl;
        return 1;
    }

    struct window_destroyer_t final
    {
        SDL_Window& _window;
        ~window_destroyer_t()
        {
            SDL_DestroyWindow(&_window);
        }
    } window_destroyer(*window);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    SDL_SetRenderVSync(renderer, 1);
    if (renderer == nullptr)
    {
        std::cerr << "Error: SDL_CreateRenderer(): " << SDL_GetError() << std::endl;
        return 1;
    }

    struct renderer_destroyer_t final
    {
        SDL_Renderer& _renderer;
        ~renderer_destroyer_t()
        {
            SDL_DestroyRenderer(&_renderer);
        }
    } renderer_destroyer(*renderer);

    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(window);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();

    // Setup scaling
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale); // Bake a fixed style scale. (until we have a solution for dynamic style scaling,
                                     // changing this requires resetting Style + calling this again)
    style.FontScaleDpi = main_scale; // Set initial font scale. (in docking branch: using io.ConfigDpiScaleFonts=true
                                     // automatically overrides this for every window depending on the current monitor)

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    // resources should be alive when finalizing imgui to store project directory.
    mcedit::model::resources resources;

    struct imgui_finalizer_t final
    {
        ~imgui_finalizer_t()
        {
            // Cleanup
            // [If using SDL_MAIN_USE_CALLBACKS: all code below would likely be your SDL_AppQuit() function]
            ImGui_ImplSDLRenderer3_Shutdown();
            ImGui_ImplSDL3_Shutdown();
            ImGui::DestroyContext();
        }
    } imgui_finalizer;

    io.Fonts->AddFontDefault();

    static constexpr ImWchar iconsRanges[] = {ICON_MIN_FA, ICON_MAX_16_FA, 0};
    ImFontConfig iconsConfig;
    iconsConfig.MergeMode = true;
    iconsConfig.PixelSnapH = true;
    io.Fonts->AddFontFromMemoryCompressedTTF(fa_solid_900_compressed_data, fa_solid_900_compressed_size, 0,
                                             &iconsConfig, iconsRanges);

    // Our state
    std::mt19937 rng(std::random_device{}());
    mcedit::ctrl::resources_edits resources_edits(resources);
    mcedit::view::popup_modals popup_modals;
    mcedit::view::main_menu_bar main_menu_bar;
    mcedit::view::select_sprite_window select_sprite_collision_window(
        "Select sprite collision", ImVec2(50, 50) * main_scale, ImVec2(250, 400) * main_scale);
    mcedit::view::sprite_collision_editor_window sprite_collision_editor_window(
        ImVec2(350, 100) * main_scale, ImVec2(800, 650) * main_scale, resources_edits);

    // Main loop
    bool done = false;
#ifdef __EMSCRIPTEN__
    // For an Emscripten build we are disabling file-system access, so let's not attempt to do a fopen() of the
    // imgui.ini file. You may manually call LoadIniSettingsFromMemory() to load settings from your own storage.
    io.IniFilename = nullptr;
    EMSCRIPTEN_MAINLOOP_BEGIN
#else
    while (!done)
#endif
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use
        // your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or
        // clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or
        // clear/overwrite your copy of the keyboard data. Generally you may always pass all inputs to dear imgui,
        // and hide them from your application based on those two flags. [If using SDL_MAIN_USE_CALLBACKS: call
        // ImGui_ImplSDL3_ProcessEvent() from your SDL_AppEvent() function]
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT ||
                (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(window)))
            {
                if (resources.has_changes())
                    popup_modals.notify_unsaved_changes(
                        mcedit::view::popup_modals::unsaved_changes_op_kind::EXIT_PROGRAM);
                else
                    done = true;
            }
        }

        // [If using SDL_MAIN_USE_CALLBACKS: all code below would likely be your SDL_AppIterate() function]
        if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED)
        {
            SDL_Delay(10);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        // Update our models
        resources.update(resources_edits, *renderer);
        resources_edits.update();

        // Show our views
        popup_modals.update(resources, *window, done);
        main_menu_bar.update(select_sprite_collision_window, popup_modals, resources, resources_edits, *window);
        select_sprite_collision_window.update(resources);
        sprite_collision_editor_window.update(resources, resources_edits, select_sprite_collision_window, rng);

        rng.discard(1);

        // Notifications style setup
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.f);   // Disable round borders
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f); // Disable borders

        // Notifications color setup
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.10f, 0.10f, 0.10f, 1.00f)); // Background color

        // Main rendering function
        ImGui::RenderNotifications();

        // ——————————————————————————————— WARNING ———————————————————————————————
        //  Argument MUST match the amount of ImGui::PushStyleVar() calls
        ImGui::PopStyleVar(2);
        // Argument MUST match the amount of ImGui::PushStyleColor() calls
        ImGui::PopStyleColor(1);

        // Rendering
        ImGui::Render();
        SDL_SetRenderScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif

    return 0;
}
