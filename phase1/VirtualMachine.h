#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H


#include <vector>
#include <string>
#include <map>
#include <stack>
#include <fstream>

using namespace std;


class VirtualMachine {
   private:
        static const short REG_FILE_SIZE = 4;
        static const short MEM_SIZE = 256;
        //vector <int> r;
        //vector <int> mem;
	short r[REG_FILE_SIZE];
	short mem[MEM_SIZE];
	stack <short> s;
        short pc;
        short ir;
        short clk;
        short base;
        short limit;
        short sr;
        short sp;
        unsigned short op;
        unsigned short rd;
        unsigned short rs;
        unsigned short i;
        unsigned short addr;
        short cnst;
        ifstream in;
        ofstream out;
        void interpret(short line);
        void setCarry(short c);
        void setOverflow(short v);
        void checkCarry(int res);
	void checkOverflow(short res);

        typedef void (VirtualMachine::*FP)();

        map<int, FP> instr;

        void load();
        void store();
        void add();
        void addc();
        void sub();
        void subc();
        void And();
        void Xor();
        void Compl();
        void shl();
        void shla();
        void shr();
        void shra();
        void compr();
        void getstat();
        void putstat();
        void jump();
        void jumpl();
        void jumpe();
        void jumpg();
        void call();
        void Return();
        void read();
        void write();
        void halt();
        void noop();

    public:
        VirtualMachine();
        int read(string filename);
	void checkMemory();
        void execute ();
};


#endif // VIRTUALMACHINE_H
