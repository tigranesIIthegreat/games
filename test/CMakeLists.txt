include(add_test.cmake)
enable_testing()

add_library(test INTERFACE gtest_main.hpp)
target_include_directories(test INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(test INTERFACE gtest gtest_main gmock)

include_directories(
    ${GTEST_DIR}/include
    ${CMAKE_SOURCE_DIR}/core/include
    ${CMAKE_SOURCE_DIR}/checkers/include
    ${CMAKE_SOURCE_DIR}/utils/include
)

games_add_test(
    NAME core_vec_test
    SRCS vec_test.cpp
    DEPS test core
)