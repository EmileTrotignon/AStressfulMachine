OBJS = obj/interpreter.o obj/utilities.o obj/VirtualMachine.o obj/VirtualMachineProcedure.o
FLAGS = -ggdb -Wall -std=c++14
EXE = bin/interpreter

$(EXE): $(OBJS)
	g++ $(FLAGS) -o $(EXE) $(OBJS)

obj/interpreter.o: src/interpreter.cpp src/VirtualMachine.h
	g++ $(FLAGS) -c src/interpreter.cpp -o obj/interpreter.o

obj/VirtualMachine.o: src/VirtualMachine.cpp src/VirtualMachine.h src/utilities.h src/VirtualMachineProcedure.h
	g++ $(FLAGS) -c src/VirtualMachine.cpp -o obj/VirtualMachine.o

obj/VirtualMachineProcedure.o: src/VirtualMachineProcedure.cpp src/VirtualMachineProcedure.h src/VirtualMachine.h
	g++ $(FLAGS) -c src/VirtualMachineProcedure.cpp -o obj/VirtualMachineProcedure.o

obj/utilities.o: src/utilities.cpp src/utilities.h
	g++ $(FLAGS) -c src/utilities.cpp -o obj/utilities.o

clean:
	rm obj/*.o
