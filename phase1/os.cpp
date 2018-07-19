
#include "VirtualMachine.h"
#include "Assembler.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    Assembler as;
    VirtualMachine vm;
    if(argc < 3) 
    {
	cout << "Error: no agruments passed\n";
	cout << "Usage: ./os [option]\nOptions:\n\t-c  [.s file]\tOnly compile code into object files\n\t-dr [.o file]\tload machine instruction and read memory\n\t-e  [.o file]\tload and execute program\n";
	return 1;
    }
    string a = argv[1];
    if (a == "-h")
    {
	cout << "Usage: ./os [option]\nOptions:\n\t-c  [.s file]\tOnly compile code into object files\n\t-dr [.o file]\tload machine instruction and read memory\n\t-e  [.o file]\tload and execute program\n";
	return 0;
    }
    string filename = argv[2];
    //for (int i = 0; i < argc; i++)
	//cout << argv[i] << endl;
    if (a == "-c")
    {
    	if(filename.substr(filename.length()-2) != ".s"){
	    cout << "Error: invalid file extension" << endl;
	    return 0;
    	}
	as.compile(filename);
    }
    else if (a == "-dr")
    {
    	if(filename.substr(filename.length()-2) != ".o"){
	    cout << "Error: invalid file extension" << endl;
	    return 0;
    	}
	if(vm.read(filename))
	    vm.checkMemory();
	else
	    cout << "Error: failed to open file " << filename << ".\n";
    }
    else if (a == "-e")
    {
    	if(filename.substr(filename.length()-2) != ".o"){
	    cout << "Error: invalid file extension" << endl;
	    return 0;
    	}
	if(vm.read(filename))
	    vm.execute();
	else
	    cout << "Error: failed to open file " << filename << ".\n";
    }
    else if (a == "-h")
    {
	cout << "Usage: ./os [option]\nOptions:\n\t-c  [.s file]\tOnly compile code into object files\n\t-dr [.o file]\tload machine instruction and read memory\n\t-e  [.o file]\tload and execute program\n";
    }
    else 
    {
	cout << "Error: invalid argument" << endl;
	cout << "use \"-h\"" << endl;
    }
    return 0;
}
