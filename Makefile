OBJS = interpreter.o utilities.o VirtualMachine.o
FLAGS = -ggdb -Wall -std=c++14
SRC = src/

projet: $(OBJS)
	g++ $(FLAGS) -o projet $(OBJS)

interpreter.o: $(SRC)interpreter.cpp $(SRC)VirtualMachine.h $(SRC)utilities.h
	g++ $(FLAGS) -c $(SRC)interpreter.cpp

VirtualMachine.o: $(SRC)VirtualMachine.cpp $(SRC)VirtualMachine.h
	g++ $(FLAGS) -c $(SRC)VirtualMachine.cpp

utilities.o: $(SRC)utilities.cpp $(SRC)utilities.h
	g++ $(FLAGS) -c $(SRC)utilities.cpp
