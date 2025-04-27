cmake_minimum_required(VERSION 3.29)
project(Aknakereso VERSION 0.1)

set(CMAKE_DEBUG_POSTFIX d)
include_directories(include)

file(GLOB_RECURSE PROJECT_SOURCES "./src/*.cpp")
file(GLOB_RECURSE PROJECT_HEADERS "./include/*.hpp" "./include/*.h")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMEMTRACE")
set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_executable(${PROJECT_NAME}_test src/cell.cpp src/board.cpp src/game.cpp src/timer.cpp src/undo.cpp src/test.cpp)

