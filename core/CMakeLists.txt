add_library(
	core_headers INTERFACE
    include/core/game_state.hpp
    include/core/game.hpp
	include/core/input.hpp
    include/core/interactive_renderable.hpp
    include/core/renderable.hpp
    include/core/texture.hpp
    include/core/vec.hpp
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
    src/input.cpp
    src/interactive_renderable.cpp
    src/renderable.cpp
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

add_subdirectory(test)
enable_testing()

target_include_directories(
    core_headers INTERFACE 
    ${CMAKE_SOURCE_DIR}/dependencies/json
    ${CMAKE_SOURCE_DIR}/dependencies/json/include
    ${SDL3_SOURCE_DIR}/include 
    ${SDL3_SOURCE_DIR}/include/SDL3 
    ${SDL3_image_SOURCE_DIR}/include 
    ${SDL3_image_SOURCE_DIR}/include/SDL3_image
)

target_link_libraries(
    core 
    PRIVATE 
    nlohmann_json::nlohmann_json
    SDL3::SDL3
    SDL3_image::SDL3_image
)