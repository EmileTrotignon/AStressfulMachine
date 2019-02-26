OBJS = obj/interpreter.o obj/utilities.o obj/VirtualMachine.o
FLAGS = -ggdb -Wall -std=c++14
SRC = src/
EXE = bin/interpreter

$(EXE): $(OBJS)
	g++ $(FLAGS) -o $(EXE) $(OBJS)

obj/interpreter.o: $(SRC)interpreter.cpp $(SRC)VirtualMachine.h $(SRC)utilities.h
	g++ $(FLAGS) -c $(SRC)interpreter.cpp -o obj/interpreter.o

obj/VirtualMachine.o: $(SRC)VirtualMachine.cpp $(SRC)VirtualMachine.h
	g++ $(FLAGS) -c $(SRC)VirtualMachine.cpp -o obj/VirtualMachine.o

obj/utilities.o: $(SRC)utilities.cpp $(SRC)utilities.h
	g++ $(FLAGS) -c $(SRC)utilities.cpp -o obj/utilities.o
