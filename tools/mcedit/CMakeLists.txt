cmake_minimum_required(VERSION 3.28)
project(mcedit LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

set(BUILD_SHARED_LIBS FALSE)
set(SDL_SHARED FALSE)
set(SDL_STATIC TRUE)

set(SDL3IMAGE_AVIF OFF)
set(SDL3IMAGE_INSTALL OFF)
set(SDL3IMAGE_BUILD_SHARED_LIBS OFF)

include(FetchContent)

FetchContent_Declare(SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.4.12
    GIT_SHALLOW TRUE
    EXCLUDE_FROM_ALL SYSTEM
)
FetchContent_MakeAvailable(SDL3)

FetchContent_Declare(SDL3_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG release-3.4.4
    GIT_SHALLOW TRUE
    EXCLUDE_FROM_ALL SYSTEM
)
FetchContent_MakeAvailable(SDL3_image)

FetchContent_Declare(imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.92.8
    GIT_SHALLOW TRUE
    EXCLUDE_FROM_ALL SYSTEM
)
FetchContent_MakeAvailable(imgui)

FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0
    GIT_SHALLOW TRUE
    EXCLUDE_FROM_ALL SYSTEM
)
FetchContent_MakeAvailable(json)

add_library(imgui STATIC EXCLUDE_FROM_ALL)
target_sources(imgui PRIVATE
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer3.cpp
)
target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)
target_link_libraries(imgui PRIVATE SDL3::SDL3-static)
target_compile_definitions(imgui PUBLIC IMGUI_DEFINE_MATH_OPERATORS)

add_executable(mcedit)
add_subdirectory(src)
target_include_directories(mcedit PRIVATE src)
target_link_libraries(mcedit PRIVATE
    imgui
    SDL3::SDL3-static
    SDL3_image::SDL3_image-static
    nlohmann_json::nlohmann_json
)

target_compile_options(mcedit PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /Zc:preprocessor /source-charset:utf-8>
    $<$<CXX_COMPILER_ID:GNU>:-freflection -Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Wpedantic>
)
