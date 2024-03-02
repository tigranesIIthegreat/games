add_library(
	checkers_headers INTERFACE
	include/checkers/board.hpp
	include/checkers/figure.hpp
	include/checkers/game.hpp
    include/checkers/player.hpp
)

target_include_directories(
    checkers_headers 
    INTERFACE
    include/
)

add_library(
    checkers STATIC
    src/board.cpp
    src/figure.cpp
    src/game.cpp
    src/player.cpp
)

target_link_libraries(checkers PUBLIC checkers_headers)
target_link_libraries(checkers_headers INTERFACE core_headers)
target_link_libraries(checkers PRIVATE core)