add_library(
	core_headers INTERFACE
    include/core/event.hpp
    include/core/game_state.hpp
    include/core/game.hpp
	include/core/inputable.hpp
    include/core/keyboard_keys.hpp
    include/core/movable.hpp
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
    src/event.cpp
    src/game.cpp
    src/inputable.cpp
    src/movable.cpp
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
    ${SDL3_SOURCE_DIR}/include 
    ${SDL3_SOURCE_DIR}/include/SDL3 
    ${SDL3_image_SOURCE_DIR}/include 
    ${SDL3_image_SOURCE_DIR}/include/SDL3_image
)

target_link_libraries(
    core 
    PRIVATE 
    SDL3::SDL3
    SDL3_image::SDL3_image
)