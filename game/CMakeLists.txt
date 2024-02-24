add_library(
	game_headers INTERFACE
	include/game/game.hpp
	include/game/board.hpp
	include/game/cell.hpp
	include/game/clock.hpp
	include/game/figure.hpp
    include/game/player.hpp
    include/game/table.hpp
)

target_include_directories(
    game_headers 
    INTERFACE
    include/
)

add_library(
    game STATIC
    src/game.cpp
    src/board.cpp
    src/cell.cpp
    src/clock.cpp
    src/figure.cpp
    src/player.cpp
    src/table.cpp
)

target_link_libraries(game PUBLIC game_headers)
target_link_libraries(game_headers INTERFACE core_headers)

# add_subdirectory(test)
# enable_testing()

target_include_directories(
    game_headers INTERFACE 
    ${SDL3_SOURCE_DIR}/include 
    ${SDL3_SOURCE_DIR}/include/SDL3 
    ${SDL3_image_SOURCE_DIR}/include 
    ${SDL3_image_SOURCE_DIR}/include/SDL3_image
)

target_link_libraries(game PRIVATE core)