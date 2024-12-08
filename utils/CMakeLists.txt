add_library(
	utils_headers INTERFACE
    include/utils/log.hpp
    include/utils/timer.hpp
    include/utils/vec.hpp
)

target_include_directories(
    utils_headers 
    INTERFACE
    include/
)

add_library(
    utils STATIC
    src/log.cpp
    src/timer.cpp
)

target_link_libraries(
    utils
    PUBLIC
    utils_headers
)

target_link_libraries(
    utils_headers
    INTERFACE
)

target_include_directories(
    utils_headers INTERFACE 
)
