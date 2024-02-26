add_library(test INTERFACE gtest_main.hpp)
target_include_directories(test INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(test INTERFACE gtest gtest_main gmock)