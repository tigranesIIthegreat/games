cmake_minimum_required(VERSION 3.17.3) 

project(games LANGUAGES CXX)
set(EXECUTABLE_NAME games)
set(CMAKE_CXX_STANDARD 20)
set(MY_SOURCES main.cpp)
set(MY_RESOURCES assets)

add_executable(${EXECUTABLE_NAME} ${MY_SOURCES})

file(COPY ${MY_RESOURCES} DESTINATION ${CMAKE_BINARY_DIR})
file(COPY "index.html" DESTINATION ${CMAKE_BINARY_DIR})

set(USE_FLAGS "-s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='[\"png\", \"jpg\"]' -sALLOW_MEMORY_GROWTH -s USE_FREETYPE=1 --preload-file ../assets/")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")

add_subdirectory(dependencies/googletest)
add_subdirectory(dependencies/json)

add_subdirectory(test)
add_subdirectory(core)
add_subdirectory(checkers)
add_subdirectory(utils)

target_link_libraries(${PROJECT_NAME} PRIVATE checkers)