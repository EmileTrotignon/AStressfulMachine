cmake_minimum_required(VERSION 3.12)
project(LIFAP4_project)

set(CMAKE_CXX_STANDARD 14)

add_executable(interpreter src/interpreter.cpp src/VirtualMachine.cpp src/VirtualMachine.h src/utilities.cpp src/utilities.h src/VirtualMachineProcedure.cpp src/VirtualMachineProcedure.h)