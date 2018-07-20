
#include "VirtualMachine.h"
#include "Assembler.h"
#include <iostream>
#include <experimental/filesystem>

using namespace std;
void usage() {
    cout << "Usage: ./os [option]\n"
	 << "Options:\n\t-c  [program]\tOnly compile code into object files\n"
	 << "\t-dr [program]\tload machine instruction and read memory\n"
	 << "\t-e  [program]\tload and execute program\n"
	 << "\t-l\t\tlist all the programs\n"
	 << "\t-h\t\tdisplay this message\n";
    return;
} 
int main(int argc, char *argv[])
{
    Assembler as;
    VirtualMachine vm;
    if(argc < 2) 
    {
	cout << "Error: no agruments passed\n";
	usage();
	return 1;
    }
    string a = argv[1];
    if (a == "-h")
    {
	usage();
	return 0;
    }
    string filename = argc == 3? argv[2]: "";
    if (a == "-c")
    {
    	//if(filename.substr(filename.length()-2) != ".s"){
	    //cout << "Error: invalid file extension" << endl;
	    //return 0;
    	//}
	filename += ".s";
	as.compile(filename);
    }
    else if (a == "-dr")
    {
    	/*if(filename.substr(filename.length()-2) != ".o"){
	    cout << "Error: invalid file extension" << endl;
	    return 0;
    	}*/
	filename += ".o";
	if(vm.read(filename))
	    vm.checkMemory();
	else
	    cout << "Error: failed to open file " << filename << ".\n";
    }
    else if (a == "-e")
    {
    	/*if(filename.substr(filename.length()-2) != ".o"){
	    cout << "Error: invalid file extension" << endl;
	    return 0;
    	}*/
	filename += ".o";
	if(vm.read(filename))
	    vm.execute();
	else
	    cout << "Error: failed to open file " << filename << ".\n";
    }
    else if ( a == "-l")
    {
	for(const auto& entry : experimental::filesystem::directory_iterator("s_files"))
	{
	    string f_name = entry.path().filename().string();
	    cout << f_name.substr(0, f_name.length()-2) << endl;
	}
    }
    else if (a == "-h")
    {
	usage();
    }
    else 
    {
	cout << "Error: invalid argument" << endl;
	cout << "use \"-h\"" << endl;
    }
    return 0;
}
