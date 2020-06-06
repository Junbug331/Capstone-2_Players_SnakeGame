cmake_minimum_required(VERSION 3.12)
project(SnakeGame)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
        "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

file(GLOB project_SRCS src/*.cpp)
file(GLOB project_LIBS lib/*.cpp)

add_library(lib ${project_LIBS})
add_executable(SnakeGame ${project_SRCS})

include_directories(
        lib
        ${SDL2_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
)

target_link_libraries(
        SnakeGame
        lib
        ${SDL2_LIBRARY}
        ${SDL2_TTF_LIBRARIES}
)