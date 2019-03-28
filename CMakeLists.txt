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
file(GLOB TINYXML
        "src/tinyxml/*")

add_executable(interpreter
        src/mains/interpreter.cpp
        ${VIRTUAL_MACHINE}
        src/file_utilities/file_utilities.cpp src/file_utilities/file_utilities.h)

target_link_libraries(interpreter libstdc++fs.a)

find_package(Curses)

message("NCurses found: ${Curses_FOUND}")

if(Curses_FOUND)

    add_library(ncursespp
            ${NCURSESPP})

    target_link_libraries(ncursespp ${CURSES_LIBRARIES})

    add_executable(a_stressful_machine_tui
            src/mains/a_stressful_machine_tui.cpp
            ${VIRTUAL_MACHINE}
            ${TUI}
            ${GAME_LOGIC}
            ${TINYXML}
            src/file_utilities/file_utilities.cpp src/file_utilities/file_utilities.h
            )

    target_link_libraries(a_stressful_machine_tui libstdc++fs.a)
    target_link_libraries(a_stressful_machine_tui ${CURSES_LIBRARIES})
    target_link_libraries(a_stressful_machine_tui ncursespp)

    add_executable(unit_test
            src/mains/unit_test.cpp
            ${VIRTUAL_MACHINE})

    target_link_libraries(unit_test ncursespp)

endif(Curses_FOUND)

# GUI App with Qt

# find_package(Qt5 REQUIRED)

find_package(Qt5Widgets)

message("Qt5 found: ${Qt5Widgets_FOUND}")

if(Qt5Widgets_FOUND)

    # Instruct CMake to run moc automatically when needed
    set(CMAKE_AUTOMOC ON)

    find_package(Qt5Widgets CONFIG)

    add_executable(a_stressful_machine_gui
            src/mains/a_stressful_machine_gui.cpp
            ${GUI}
            ${VIRTUAL_MACHINE}
            ${GAME_LOGIC}
            ${TINYXML}
            src/file_utilities/file_utilities.cpp src/file_utilities/file_utilities.h
            src/GUI/GUISandbox.cpp src/GUI/GUISandbox.h)

    target_link_libraries(a_stressful_machine_gui Qt5::Widgets)
    target_link_libraries(a_stressful_machine_gui libstdc++fs.a)

endif(Qt5Widgets_FOUND)

#add_executable(scratch
#        src/ncurses_scratch.cpp)
#target_link_libraries(scratch ${CURSES_LIBRARIES})