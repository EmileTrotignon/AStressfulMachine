cmake_minimum_required(VERSION 3.8)
project(A_Stressful_Machine)

set(CMAKE_CXX_STANDARD 17)

find_package(Curses REQUIRED)

add_library(a_stressful_machine_lib
        src/Game.cpp src/Game.h
        src/GameLevel.cpp src/GameLevel.h
        src/GameSequence.cpp src/GameSequence.h
        src/GameGUI.cpp src/GameGUI.h
        src/SavePicker.cpp src/SavePicker.h
        src/VirtualMachine.cpp src/VirtualMachine.h
        src/utilities.cpp src/utilities.h
        src/VirtualMachineProcedure.cpp src/VirtualMachineProcedure.h
        src/GameLevel.cpp src/GameLevel.h
        src/VirtualMachineException.cpp src/VirtualMachineException.h
        src/a_stressful_machine_tui.cpp)

target_link_libraries(a_stressful_machine_lib libstdc++fs.a)

add_library(ncurses++
        src/ncurses++.cpp src/ncurses++.h
        src/NcursesWindow.cpp src/NcursesWindow.h
        src/NcursesMenu.cpp src/NcursesMenu.h)

target_link_libraries(ncurses++ ${CURSES_LIBRARIES})

add_executable(interpreter
        src/interpreter.cpp
        src/VirtualMachine.cpp src/VirtualMachine.h
        src/utilities.cpp src/utilities.h
        src/VirtualMachineProcedure.cpp src/VirtualMachineProcedure.h src/VirtualMachineException.cpp src/VirtualMachineException.h)
target_link_libraries(interpreter libstdc++fs.a)

add_executable(a_stressful_machine_tui
        src/a_stressful_machine_tui.cpp
        src/GameTUI.cpp src/GameTUI.h
        )


target_link_libraries(a_stressful_machine_tui a_stressful_machine_lib)
target_link_libraries(a_stressful_machine_tui libstdc++fs.a)
target_link_libraries(a_stressful_machine_tui ${CURSES_LIBRARIES})
target_link_libraries(a_stressful_machine_tui ncurses++)

add_executable(unit_test
        src/ncurses_utilities.cpp src/ncurses_utilities.h
        src/test.cpp)

target_link_libraries(unit_test ${CURSES_LIBRARIES})

#add_executable(scratch
#        src/ncurses_scratch.cpp)
#target_link_libraries(scratch ${CURSES_LIBRARIES})
