objects=VirtualMachine.o Assembler.o format.o

os: os.cpp $(objects)
	g++ os.cpp $(objects) -g -o os

VirtualMachine.o: VirtualMachine.cpp
	g++ -c -g VirtualMachine.cpp

Assember.o: Assembler.cpp
	g++ -c Assembler.cpp

format.o: format.cpp
	g++ -c format.cpp

clean: 
	rm $(objects)

