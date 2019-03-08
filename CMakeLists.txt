cmake_minimum_required(VERSION 3.5)
project(A_Stressful_Machine)

set(CMAKE_CXX_STANDARD 14)

#find_package(Curses REQUIRED)

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
        )

add_executable(interpreter
        src/interpreter.cpp
        src/VirtualMachine.cpp src/VirtualMachine.h
        src/utilities.cpp src/utilities.h
        src/VirtualMachineProcedure.cpp src/VirtualMachineProcedure.h src/VirtualMachineException.cpp src/VirtualMachineException.h)
#target_link_libraries(interpreter ${CURSES_LIBRARIES})

add_executable(play_level
        src/play_level.cpp
        src/VirtualMachine.cpp src/VirtualMachine.h
        src/utilities.cpp src/utilities.h
        src/VirtualMachineProcedure.cpp src/VirtualMachineProcedure.h
        src/GameLevel.cpp src/GameLevel.h src/VirtualMachineException.cpp src/VirtualMachineException.h)