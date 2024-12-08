add_library(
	core_headers INTERFACE
    include/core/game_state.hpp
    include/core/game.hpp
	include/core/input_manager.hpp
    include/core/game_object.hpp
    include/core/texture.hpp
    include/core/window.hpp
)

target_include_directories(
    core_headers 
    INTERFACE
    include/
)

add_library(
    core STATIC
    src/game_state.cpp
    src/game.cpp
    src/input_manager.cpp
    src/game_object.cpp
    src/texture.cpp
    src/window.cpp
)

target_link_libraries(
    core
    PUBLIC
    core_headers
)

target_link_libraries(
    core_headers
    INTERFACE
)

target_include_directories(
    core_headers INTERFACE 
    ${CMAKE_SOURCE_DIR}/dependencies/json/include
    ${CMAKE_SOURCE_DIR}/dependencies/SDL/include 
    ${CMAKE_SOURCE_DIR}/dependencies/SDL_Image/include 
)

target_link_libraries(core_headers INTERFACE utils_headers)

target_link_libraries(
    core 
    PRIVATE 
    utils
    nlohmann_json::nlohmann_json
    SDL3::SDL3
    SDL3_image::SDL3_image
)