cmake_minimum_required(VERSION 3.22)
project(Aknakereso VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNCURSES_STATIC -lncurses")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMEMTRACE")

file(GLOB_RECURSE PROJECT_HEADERS "./include/*.hpp" "./include/*.h")
include_directories(./include)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(CURSES_LIBRARY "C:/msys64/mingw64/lib/libncurses.a")
    set(CURSES_INCLUDE_PATH "C:/msys64/mingw64/include/")
    message(STATUS "Platform is Windows")
    include_directories(${CURSES_INCLUDE_PATH}/ncurses)
else()
    message(STATUS "Platform is Linux")
    include_directories(${CURSES_INCLUDE_PATH})
endif ()
find_package(Curses REQUIRED)

add_executable(${PROJECT_NAME}
        ./src/cell.cpp ./src/board.cpp ./src/game.cpp ./src/timer.cpp
        ./src/undo.cpp ./src/cli.cpp ./src/main.cpp
        ${PROJECT_HEADERS})
add_executable(${PROJECT_NAME}_test
        ./src/cell.cpp ./src/board.cpp ./src/game.cpp ./src/timer.cpp
        ./src/undo.cpp ./src/test.cpp
        ${PROJECT_HEADERS})

#link_directories(${CURSES_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARY})
