cmake_minimum_required(VERSION 3.24)
enable_testing()

include_directories(
  ${GTEST_DIR}/include
  ${CMAKE_SOURCE_DIR}/core/include
  ${CMAKE_SOURCE_DIR}/test/
)

games_add_test(
    NAME core_vec_test
    SRCS vec_test.cpp
    DEPS test core
)