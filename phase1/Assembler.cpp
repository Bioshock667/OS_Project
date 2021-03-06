/////////////////////////////////////////////////////////////////
//Assembler.cpp
//Programmed by Seth Lemanek
//Prof. Kay Zemoudeh
//CSE 460
//This assembler converts user code into machine code to be read by 
//VirtualMachine.cpp
/////////////////////////////////////////////////////////////////////////

#include "Assembler.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
using namespace std;
Assembler::Assembler()
{
    line = 0;
}


void Assembler::compile(string filename)
{
    string sFilesFolder = "s_files/";
    string oFilesFolder = "o_files/";
    string sfile = sFilesFolder + filename;
    ifstream infile;
    infile.open(sfile.c_str());
      filename.replace(filename.end()-2, filename.end(), ".o");//create name for object file
    string ofile = oFilesFolder + filename;
    ofstream outfile;
    outfile.open(ofile.c_str());

    string Line;
    string code;
    int i;
    int rd;
    unsigned int mcode;
    int opd;
    int eoOP;
    bool isNeg;
    while(getline(infile, Line))
    {
       line++;
       if(Line.substr(0,1) != "!")//if this line is not a comment
        {
            if(Line.find("!") != string::npos)
            {
	      Line.erase(Line.find("!"), Line.length());
 //remove comment part of the line if found
            }
	    istringstream instr(Line);
	    instr >> code;

            if (code.at(code.length()-1) == 'i')
            {
                code.erase(code.length()-1); //if there is an i at the end of opcode, immediate mode = 1 then remove i
            	i = 1;
            }
            else
            	i = 0;

            mcode = checkOP(code); //call function checkOP to return corresponding number
	/* each instruction will be identified by its type 
	   dm = Data Movement
	   op = Operate (arithmetic & logic)
	   ctr = control with Dest. register
	   ctra = control with only an address
	   ctrn = control with no following numbers
	*/
            if(mcode < 2)
           	 iType = dm;
            else if (mcode >= 2 && mcode < 8)
           	 iType = op;
            else if (mcode >= 8  && mcode < 16)
            {
            	if(mcode == 13)
                    iType = op;
           	 else
                    iType = ctr;
            }
            else if (mcode >= 16 && mcode <= 20)
            	iType = ctra;
            else if (mcode == 21)
            	iType = ctrn;
            else if (mcode == 22 || mcode == 23)
            	iType = ctr;
            else // for halt and noop
            	iType = ctrn;
            if(i == 1 && (iType == ctr||iType ==ctra|| iType == ctrn))
           	 aError("No immediate mode for ctr. instructions");
            if (iType == ctra || iType == ctrn)//these control instructions dont use rd
            	rd = 0;
            else
            {
            	instr >> rd;
            	if (rd < 0 || rd > 3)
            	{
                    aError("Incompatible Dest. Register");
            	}
            }
	/*************start of new code****************/
	    //for instructions that do not have i at the end but still have i = 1
	    if(mcode == 1 | iType == ctra) //if instruction is store, call, or one of the jumps
		i = 1; //set i to 1
	/*************end of new code**************/
            mcode = mcode<<2;
            mcode = mcode + rd;


            mcode = mcode << 1;
            mcode = mcode + i;

           if(iType == ctr|| iType == ctrn)
           	 opd = 0;
           else
           {
	 
         	instr >> opd;

	     	if(opd < 0)
	     	{
	     	if(iType == dm && i == 0)
	           aError("Address cannot be negative");
                else if (iType == ctra)
                    aError("Address cannot be negative");

            	}
		if(opd > 128|| opd < -127)
		    aError("Address/constant outside range for 8 bit format");
		opd = opd & 255; //and with 0000000011111111 to  reduce signed 32bit number to signed signed 8bit number
	
        }
        if(iType == op && i == 0)//if if instruction is operate in immediate mode then the operand is source register then shifted 6 bits up
        {
	  if (opd < 0 || opd >3)
	        aError("Incompatible source register");
            mcode = mcode << 2;
            mcode = mcode + opd;
            mcode = mcode << 6;
        }
        else //operand is an 8-bit address or constant
        {
            mcode = mcode << 8;
            mcode = mcode + opd;
        }
	  // cout << opd << endl;
        outfile << mcode << endl;
        }
	}	
    

    infile.close();
    outfile.close();
    return;
}

int Assembler::checkOP(string opc)
{
    if (opc == "load")
        return 0;
    if(opc == "store")
        return 1;
    if (opc == "add")
        return 2;
    if (opc == "addc")
        return 3;
    if (opc == "sub")
        return 4;
    if (opc == "subc")
        return 5;
    if (opc == "and")
        return 6;
    if (opc == "xor")
        return 7;
    if (opc == "compl")
        return 8;
    if (opc == "shl")
        return 9;
    if (opc == "shla")
        return 10;
    if (opc == "shr")
        return 11;
    if (opc == "shra")
        return 12;
    if (opc == "compr")
        return 13;
    if (opc == "getstat")
        return 14;
    if (opc == "putstat")
        return 15;
    if (opc == "jump")
        return 16;
    if (opc == "jumpl")
        return 17;
    if (opc == "jumpe")
        return 18;
    if (opc == "jumpg")
        return 19;
    if (opc == "call")
        return 20;
    if (opc == "return")
        return 21;
    if (opc == "read")
        return 22;
    if (opc == "write")
        return 23;
    if (opc == "halt")
        return 24;
    if (opc == "noop")
        return 25;
    else
    {
        aError(opc + " is not a known Opcode");
        exit(EXIT_FAILURE);
    }
}
//this function exits and returns an error
void Assembler::aError(string error_type)
{
    cout << error_type << " at line: " << line << endl;
    exit(EXIT_FAILURE);
}
