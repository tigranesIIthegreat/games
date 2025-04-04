cmake_minimum_required(VERSION 3.0)
project(games)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined,address -Wall -Wextra -Werror")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=undefined,address -Wall -Wextra -Werror")

set(SOURCES main.cpp)

if(APPLE)
    enable_language(OBJC)
endif()

if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=3 -s USE_SDL_IMAGE=3")
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s SDL3_IMAGE_FORMATS=['png']")

    # Linker flags specific to Emscripten (this is where ALLOW_MEMORY_GROWTH should go)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s ALLOW_MEMORY_GROWTH=1 -s EXIT_RUNTIME=1")

    string(REPLACE "-Werror" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    string(REPLACE "-Werror" "" CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -g")
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

add_subdirectory(dependencies/googletest)
add_subdirectory(dependencies/json)
add_subdirectory(dependencies/SDL)
add_subdirectory(dependencies/SDL_Image)

add_subdirectory(test)
add_subdirectory(core)
add_subdirectory(checkers)
add_subdirectory(utils)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE checkers)