cmake_minimum_required(VERSION 3.8)
project(A_Stressful_Machine)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SRC "src/*")

include_directories(${SRC})

file(GLOB NCURSESPP
        "src/ncursespp/*")
file(GLOB GUI
        "src/GUI/*")
file(GLOB TUI
        "src/TUI/*")
file(GLOB GAME_LOGIC
        "src/game_logic/*")
file(GLOB VIRTUAL_MACHINE
        "src/virtual_machine/*")

find_package(Curses REQUIRED)

add_library(ncursespp
        ${NCURSESPP})

target_link_libraries(ncursespp ${CURSES_LIBRARIES})

add_executable(interpreter
        src/mains/interpreter.cpp
        ${VIRTUAL_MACHINE}
        src/file_utilities.cpp src/file_utilities.h)

target_link_libraries(interpreter libstdc++fs.a)

add_executable(a_stressful_machine_tui
        src/mains/a_stressful_machine_tui.cpp
        ${VIRTUAL_MACHINE}
        ${TUI}
        ${GAME_LOGIC}
        src/file_utilities.cpp src/file_utilities.h
        )

target_link_libraries(a_stressful_machine_tui libstdc++fs.a)
target_link_libraries(a_stressful_machine_tui ${CURSES_LIBRARIES})
target_link_libraries(a_stressful_machine_tui ncursespp)

add_executable(unit_test
        src/mains/unit_test.cpp)

target_link_libraries(unit_test ncursespp)


#add_executable(scratch
#        src/ncurses_scratch.cpp)
#target_link_libraries(scratch ${CURSES_LIBRARIES})
