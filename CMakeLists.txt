cmake_minimum_required(VERSION 3.8)
project(A_Stressful_Machine)

set(CMAKE_CXX_STANDARD 17)


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


add_executable(interpreter
        src/interpreter.cpp
        src/VirtualMachine.cpp src/VirtualMachine.h
        src/utilities.cpp src/utilities.h
        src/VirtualMachineProcedure.cpp src/VirtualMachineProcedure.h src/VirtualMachineException.cpp src/VirtualMachineException.h)
target_link_libraries(interpreter libstdc++fs.a)


#add_executable(play_level
#        src/play_level.cpp
#        src/VirtualMachine.cpp src/VirtualMachine.h
#        src/utilities.cpp src/utilities.h
#        src/VirtualMachineProcedure.cpp src/VirtualMachineProcedure.h
#        src/GameLevel.cpp src/GameLevel.h src/VirtualMachineException.cpp src/VirtualMachineException.h)

find_package(Curses REQUIRED)

add_executable(a_stressful_machine_tui
        src/a_stressful_machine_tui.cpp
        src/GameTUI.cpp src/GameTUI.h
        src/ncurses_utilities.cpp src/ncurses_utilities.h
        )


target_link_libraries(a_stressful_machine_tui a_stressful_machine_lib)
target_link_libraries(a_stressful_machine_tui libstdc++fs.a)

target_link_libraries(a_stressful_machine_tui ${CURSES_LIBRARIES})

#add_executable(test
#
#        src/ncurses_utilities.cpp src/ncurses_utilities.h
#        src/test.cpp)

#target_link_libraries(test ${CURSES_LIBRARIES})

