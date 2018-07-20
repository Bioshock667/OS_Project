//VirtualMachine.cpp
//Programmed by Seth Lemanek
//Prof. Key Zemoudeh
//Cass: CSE 460 
//Date Modified April, 28, 2015
//This program takes in an object file and executes it.  Its purpose is to
//simulate a 16-bit computer.  It comes with many features of basic computers 
// susch as stack pointer for recursion, a register for holding status flags 
// and a program counter to go through the program.  It puts its output and 
// clock cycle in a .out file.
#include "VirtualMachine.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <assert.h>
#include <stdlib.h>

using namespace std;

VirtualMachine::VirtualMachine()
{
    /*construct a new virtual machine and  initializes its components*/
    //r = vector <int> (REG_FILE_SIZE);
    //mem = vector <int> (MEM_SIZE);
    pc = 0;
    for(int i = 0; i < MEM_SIZE; i++)
	mem[i] = 0;
    for(int i = 0; i < REG_FILE_SIZE; i++)
	r[i] = 0;
    ir = 0;
    clk = 0;
    base = 0;
    limit = 0;
    sr = 0;
    op = 0;
    rd = 0;
    rs = 0;
    i = 0;
    addr = 0;
    cnst = 0;
    sp = 256;

        instr [0] = &VirtualMachine::load;
        instr [1] = &VirtualMachine::store;
        instr[2] = &VirtualMachine::add;
        instr[3] = &VirtualMachine::addc;
        instr[4] = &VirtualMachine::sub;
        instr[5] = &VirtualMachine::subc;
        instr[6] = &VirtualMachine::And;
        instr[7] = &VirtualMachine::Xor;
        instr[8] = &VirtualMachine::Compl;
        instr[9] = &VirtualMachine::shl;
        instr[10] = &VirtualMachine::shla;
        instr[11] = &VirtualMachine::shr;
        instr[12] = &VirtualMachine::shra;
        instr[13] = &VirtualMachine::compr;
        instr[14] = &VirtualMachine::getstat;
        instr[15] = &VirtualMachine::putstat;
        instr[16] = &VirtualMachine::jump;
        instr[17] = &VirtualMachine::jumpl;
        instr[18] = &VirtualMachine::jumpe;
        instr[19] = &VirtualMachine::jumpg;
        instr[20] = &VirtualMachine::call;
        instr[21] = &VirtualMachine::Return;
        instr[22] = &VirtualMachine::read;
        instr[23] = &VirtualMachine::write;
        instr[24] = &VirtualMachine::halt;
        instr[25] = &VirtualMachine::noop;
}
//reads an object file and loads it into memory
// returns 0 on failure and 1 on success
int VirtualMachine::read(string filename)
{
    string ext = filename.substr(filename.length()-2);
    if (ext != ".o"){
	return 0;
    }
    string oFileName = "o_files/" + filename;
    ifstream object;
    object.open(oFileName.c_str());
    if(object.fail()) {
	return 0;
    }
    filename.erase(filename.end()-2, filename.end());
    string infile, outfile;
    infile = "in_files/" + filename + ".in";
    outfile = "out_files/" + filename + ".out";
    int code;
    int i = 0;
    while(object>>code)
    {
        mem[i] = code;
        i++;
        limit++;
    }
    object.close();
    in.open(infile.c_str());
    if(in.fail())
	inputAvailiable = false;
    else
	inputAvailiable = true;
    out.open(outfile.c_str());
    return 1;
}
void VirtualMachine::checkMemory()
{
    for (int i =0; i <= limit-1; i++)
    	cout << "Mem: " << mem[i] << endl;
}
void VirtualMachine::execute()
{
    while (op != 24)
    {
   	ir = mem[pc];
	pc++;
   	interpret(ir);
   	(this->*instr[op])();
	assert (pc < MEM_SIZE);
	//uncomment to see how vm interprets its machine code
	/*cout << "PC: " << pc << endl;
   	cout << "OPCODE: " << op << endl;
	cout << "Reg. Dest.: " << rd << endl;
   	cout << "Immed. Mode: " << i << endl;
   	cout << "Reg Source: " << rs << endl;
    	cout << "Constant: " << cnst << endl;
    	cout << "Address: " << addr << endl;
    	cout << endl;
*/
    }
      
  out << endl << "Clock Cycles: " << clk << endl;
    in.close();
    out.close();
}

void VirtualMachine::interpret(short line)
{


        class format1 {
        public:
        unsigned UNUSED:6;
        unsigned RS:2;
        unsigned I:1;
        unsigned RD:2;
        unsigned OP:5;
    };
    class format2 {
    public:
        unsigned ADDR:8;
        unsigned I:1;
        unsigned RD:2;
        unsigned OP:5;
    };
    class format3 {
    public:
            short CONST:8;
            unsigned I:1;
            unsigned RD:2;
            unsigned OP:5;
    };

    union instruction {
            short i;
            format1  f1;
            format2  f2;
            format3  f3;
    };

    instruction ins;
    ins.i = line;
    op = ins.f1.OP;
    rd = ins.f1.RD;
   if (ins.f1.I == 1)
       i = 1;
   else
        i = 0;
    if(op == 0)
    {
        if(i == 0)
        {
        addr = ins.f2.ADDR;
        rs = 0;
        cnst = 0;
        }
        else
        {
            cnst = ins.f3.CONST;
            rs = 0;
            addr = 0;
        }
    }
    else if (op == 1) // for store function
    {
        addr = ins.f2.ADDR;
        rs = 0;
        cnst = 0;
    }
    else if((op >=2 && op <=7)|| op == 13)//for the operate instructions (add, sub, etc.)
    {
        if(i==0)
        {
            rs = ins.f1.RS;
            addr = 0;
            cnst = 0;
        }
        else if (i == 1)
        {
            cnst = ins.f3.CONST;
            addr = 0;
            rs = 0;
        }
    }
    else if(op >=16 && op <= 20) //for jump and call functions
    {
        addr = ins.f2.ADDR;
        rs = 0;
        cnst = 0;
    }
    else //for compliment, shift, return read, write, noop, halt
    {
        addr = 0;
        rs = 0;
        cnst = 0;
    }
    /*cout << ins->i << endl;
	cout << ins->f1.OP << " " << ins->f1.RD << " " << ins->f1.I << " " << ins->f1.RS << " " << ins->f1.UNUSED << endl;
	cout << ins->f2.OP << " " << ins->f2.RD << " " << ins->f2.I << " " << ins->f2.ADDR << endl;
	cout << ins->f3.OP << " " << ins->f3.RD << " " << ins->f3.I << " " << ins->f3.CONST << endl;8*/
}

void VirtualMachine::checkCarry(int res)
{
    setCarry((res >> 16) & 1);
}

void VirtualMachine::checkOverflow(short res)
{
    short opd;
    if(i)
    	opd = cnst;
    else
    	opd = r[rs];
    
    short rdSign = (r[rd] >> 15) & 1;
    short opdSign = (opd >> 15) & 1;
    short resSign = (res >> 15) & 1;
    short v;
    if(op >= 9 && op <= 12) //shift ins
    	v = rdSign ^ resSign; // then 1 if signs don't match and 0 if they do
    else
    	v = ~(rdSign ^ opdSign) & (rdSign ^ resSign); //if the signs of rd and operand match AND signs of rd and result don't match then overflow
    setOverflow(v);
}

void VirtualMachine::setCarry(short c)
{
    if(c == 0)
        sr = sr & 62;
    else if (c == 1)
        sr = sr | 1;
    else
        return;
}

void VirtualMachine::setOverflow(short v)
{
    if(v == 0)
        sr = sr & 15;
    else if (v == 1)
        sr = sr | 16;
    else
        return;
}

void VirtualMachine::load()
{
    if (i == 0)
    {
        r[rd] = mem[addr];
        clk += 4;
    }
    else // i = 1 : immediate mode
    {
        r[rd] = cnst;
        clk++;
    }
      r[rd] &= 0xFFFF; //all registers must hold no more than 16 bits therefore zero out the higher 16 bit;
}

void VirtualMachine::store()
{
    mem[addr] = r[rd];
    clk += 4;
}
void VirtualMachine::add()
{
    int RD = (int)r[rd] & 0xFFFF;
    int opd;
    if (i) {
        opd = cnst;
    } else {
        opd = r[rs];
    }
    opd &= 0xFFFF;
    RD = RD + opd;
    checkCarry(RD);
    checkOverflow((short)RD);
    r[rd] = RD;
    clk++;
}
void VirtualMachine::addc()
{
    int RD = (int)r[rd] & 0xFFFF;
    int opd;
    if(i)
    	opd = cnst;
    else
	opd = r[rs];
    opd &= 0xFFFF;
    opd += (sr & 1);
    RD += opd;
    checkCarry(RD);
    checkOverflow((short)RD);
    r[rd] = RD;
    clk++;
}
void VirtualMachine::sub()
{
    int RD = r[rd] & 0xFFFF;
    int opd;
    if (i)
      opd = cnst;
    else
	 opd = r[rs];
    opd = (~opd);
    opd++;
    opd &= 65535;
    RD += opd; // subtract using 2's complement
    checkCarry(RD);
    checkOverflow((short)RD);
    r[rd] = RD;
    clk++;

}
void VirtualMachine::subc()
{
    int RD = r[rd] & 0xFFFF;
    int opd;
    if (i)
      opd = cnst;
    else
	 opd = r[rs];
    opd += (sr & 1);
    opd = (~opd);
    opd++;
    opd &= 65535;
    RD += opd; // subtract using 2's complement
    checkCarry(RD);
    checkOverflow((short)RD);
    r[rd] = RD;
    clk++;
}
void VirtualMachine::And()
{
    if (i == 0)
        r[rd] &= r[rs];
    else
    {
	cnst &= 65535;
        r[rd] &= cnst;
    }
    clk++;
}
void VirtualMachine::Xor()
{
    if (i == 0)
        r[rd] ^= r[rs];
    else
{
	cnst &= 65535;
        r[rd] ^= cnst;
	}
    clk++;
}
void VirtualMachine::Compl()
{
    r[rd] = ~r[rd];
    r[rd] &= 65535;
    clk++;
}
void VirtualMachine::shl()
{
    int RD = r[rd] << 1;
    checkCarry(RD);
    r[rd] = RD;
    clk++;

}
void VirtualMachine::shla ()
{
    int RD = r[rd] << 1;
    checkCarry(RD);
    checkOverflow((short)RD);
    r[rd] = RD;
    clk++;
}
void VirtualMachine::shr ()
{
    setCarry(r[rd] & 1); //carry out bit 1 before shifting
    r[rd] >>= 1;
    r[rd] &= 0x7FFF; //zero out bit 15
    clk++;
}
void VirtualMachine::shra ()
{
     setCarry(r[rd] & 1); 
     r[rd] >>= 1;
    clk++;
}
void VirtualMachine::compr()
{
    short opr = 0;
    if(i==0)
	opr = r[rs];
    else
	opr = cnst;
    opr &= 65535;
    sr &= 0xFFF1; //clear previous comparison flags
    if(r[rd] > opr)
	sr |= 2;
    else if (r[rd] == opr)
	sr |= 4;
    else
	sr |= 8;
    clk++;
}
void VirtualMachine::getstat()
{
    r[rd] = sr;
    clk++;
}
void VirtualMachine::putstat()
{
    sr = r[rd];
    clk++;
}
void VirtualMachine::jump()
{
    pc = addr;
    clk++;
}
void VirtualMachine::jumpl()
{
    if ((sr & 8) == 8)
        pc = addr;
        clk++;
}
void VirtualMachine::jumpe()
{
    if ((sr & 4) == 4)
        pc = addr;
        clk++;
}  
void VirtualMachine::jumpg()
{
    if((sr & 2) == 2)
        pc = addr;
        clk++;
}
void VirtualMachine::call() //push the values of the registers and last ess to the stack and jump to address
{
    assert (sp >= (limit + 6));
    --sp;
    mem[sp] = pc;
    --sp;
    mem[sp] = r[0];
    --sp;
    mem[sp] = r[1];
    --sp;
    mem[sp] = r[2];
    --sp;
    mem[sp] = r[3];
    --sp;
    mem[sp] = sr;
    pc = addr;
    clk += 4;
}
void VirtualMachine::Return() //populate the registers with values popped from stack and jump to last saved place
{
    assert (sp < 256);
    sr = mem[sp];
    ++sp;
    r[3] = mem[sp];
    ++sp;
    r[2] = mem[sp];
    ++sp;
    r[1] = mem[sp];
    ++sp;
    r[0] = mem[sp];
    ++sp;
    pc = mem[sp];
    ++sp;
    clk += 4;
}
void VirtualMachine::read()
{
    if(inputAvailiable)
    {
    	in >> r[rd];
    }
    clk += 28;
}
void VirtualMachine::write()
{
    out << r[rd] << endl;
    clk += 28;
}
void VirtualMachine::halt()
{
    cout << "Program halted!" << endl;
    clk++;
}
void VirtualMachine::noop ()
{
    clk++;
}
