cmake_minimum_required(VERSION 3.5)
project(A_Stressful_Machine)

set(CMAKE_CXX_STANDARD 14)

#find_package(Curses REQUIRED)
add_executable(interpreter
        src/interpreter.cpp
        src/VirtualMachine.cpp src/VirtualMachine.h
        src/utilities.cpp src/utilities.h
        src/VirtualMachineProcedure.cpp src/VirtualMachineProcedure.h)
#target_link_libraries(interpreter ${CURSES_LIBRARIES})

add_executable(play_level
        src/play_level.cpp
        src/VirtualMachine.cpp src/VirtualMachine.h
        src/utilities.cpp src/utilities.h
        src/VirtualMachineProcedure.cpp src/VirtualMachineProcedure.h
        src/GameLevel.cpp src/GameLevel.h)