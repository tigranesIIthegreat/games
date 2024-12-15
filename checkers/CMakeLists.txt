add_library(
	checkers_headers INTERFACE
	include/checkers/board.hpp
    include/checkers/color.hpp
    include/checkers/cell.hpp
	include/checkers/figure.hpp
	include/checkers/game.hpp
    include/checkers/king.hpp
    include/checkers/man.hpp
    include/checkers/play_state.hpp
)

target_include_directories(
    checkers_headers 
    INTERFACE
    include/
)

add_library(
    checkers STATIC
    src/board.cpp
    src/cell.cpp
    src/figure.cpp
    src/game.cpp
    src/king.cpp
    src/man.cpp
    src/play_state.cpp
)

target_link_libraries(checkers PUBLIC checkers_headers)
target_link_libraries(checkers_headers INTERFACE core_headers)
target_link_libraries(checkers PRIVATE core)