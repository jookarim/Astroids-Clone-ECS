cmake_minimum_required(VERSION 3.26)

project(Astroids_Clone_ECS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------- ImGui ----------------
add_library(imgui STATIC
    External/include/imgui/imgui.cpp
    External/include/imgui/imgui_draw.cpp
    External/include/imgui/imgui_tables.cpp
    External/include/imgui/imgui_widgets.cpp
    External/include/imgui/imgui_demo.cpp
    External/include/imgui/backends/imgui_impl_sdl2.cpp
    External/include/imgui/backends/imgui_impl_sdlrenderer2.cpp
)

target_include_directories(imgui PUBLIC
    External/include/imgui
    External/include/imgui/backends
    External/include        
)

target_link_libraries(imgui PUBLIC SDL2)

# ---------------- Game ----------------
add_executable(Astroids_Clone_ECS
    src/main.cpp
    src/Action.cpp
    src/ActionManager.cpp
    src/AssetManager.cpp
    src/AudioSystem.cpp
    src/Collision.cpp
    src/EntityManager.cpp
    src/Game.cpp
    src/Gui.cpp
    src/Input.cpp
    src/LivesSystem.cpp
    src/MovementSystem.cpp
    src/Music.cpp
    src/PhysicsSystem.cpp
    src/Renderer.cpp
    src/RenderSystem.cpp
    src/SceneGame.cpp
    src/ScoreSystem.cpp
    src/Sound.cpp
    src/Text.cpp
    src/Texture.cpp
    src/Timer.cpp
    src/Window.cpp
    src/SceneStart.cpp
    src/SceneRestart.cpp
    src/VertexArray.cpp
)

target_include_directories(Astroids_Clone_ECS PRIVATE
    include
    External/include
)

target_link_directories(Astroids_Clone_ECS PRIVATE
    External/lib/SDL2
)

target_link_libraries(Astroids_Clone_ECS PRIVATE
    SDL2
    SDL2main
    SDL2_image
    SDL2_mixer
    SDL2_ttf
    imgui
)

# ---------------- Assets ----------------
add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:Astroids_Clone_ECS>/assets
)
add_dependencies(Astroids_Clone_ECS copy_assets)

# ---------------- SDL DLLs ----------------
file(GLOB SDL_DLLS
    "${CMAKE_SOURCE_DIR}/External/lib/SDL2/*.dll"
)

add_custom_command(TARGET Astroids_Clone_ECS POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SDL_DLLS}
        $<TARGET_FILE_DIR:Astroids_Clone_ECS>
)
