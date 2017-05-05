#include <iostream>
using std::cout;
using std::endl;
#include <iomanip>
using std::dec;
using std::hex;
using std::setfill;
using std::setw;
using std::left;
using std::right;
#include <sstream>
using std::stringstream;


#include "processor.hpp"

Processor::Processor(Program &program)
{
    complete_ = false;
    PC = 0;
    stackPtr = 1027; //start stack at end of memory
    accumulator = 0;
    stack = vector<int>(1028, 0);
    cycleCount = 0;
    _program = program;
}

void Processor::step()
{
    execute();
}

void Processor::execute()
{
    //note: casting pointer to char* and adding PC then casting back to int*
    //          is the same as casting to int* and adding PC/4. this is
    //          simply done to preserve the PC + 4 idea from
    //          word alligned memory
	int opcode = _program._instructions[PC].opcode;
	int param = _program._instructions[PC].param;

    if (opcode == 0x00) //LOAD addr
    {
        accumulator = _program._dataMemory[param];
    }
    else if (opcode == 0x01) //LOADI addr
    {
        int addr = _program._dataMemory[param];
        accumulator = _program._dataMemory[addr];
    }
    else if (opcode == 0x02) //STORE addr
    {
        _program._dataMemory[param] = accumulator;
    }
    else if (opcode == 0x03) //STOREI addr
    {
        int addr = _program._dataMemory[param];
        _program._dataMemory[addr] = accumulator;
    }
    else if (opcode == 0x04) //ADD addr
    {
        accumulator = accumulator + _program._dataMemory[param];
    }
    else if (opcode == 0x05) //ADDI const
    {
		accumulator = accumulator + param;
    }
    else if (opcode == 0x06) //AND addr
    {
        accumulator = accumulator & _program._dataMemory[param];
    }
    else if (opcode == 0x07) //OR addr
    {
        accumulator = accumulator | _program._dataMemory[param];
    }
    else if (opcode == 0x08) //NOT
    {
        accumulator = ~accumulator;
    }
    else if (opcode == 0x09) //XOR addr
    {
        accumulator = accumulator ^ _program._dataMemory[param];
    }
    else if (opcode == 0x0A) //JUMP const
    {
        //TODO: implement this
        PC = param;
    }
    else if (opcode == 0x0B) //BZERO addr
    {
        PC = (accumulator == 0 ? param : PC + 1); //PC + 4
        return;
    }
    else if (opcode == 0x0C) //SEQ	addr
    {
        accumulator = (accumulator == _program._dataMemory[param] ? 1 : 0);
    }
    else if (opcode == 0x0D) //SNE	addr
    {
        accumulator = (accumulator != _program._dataMemory[param] ? 1 : 0);
    }
    else if (opcode == 0x0E) //SGT	addr
    {
        accumulator = (accumulator > _program._dataMemory[param] ? 1 : 0);
    }
    else if (opcode == 0x0F) //SLT	addr
    {
        accumulator = (accumulator < _program._dataMemory[param] ? 1 : 0);
    }
    else if (opcode == 0x10) //SGE	addr
    {
        accumulator = (accumulator >= _program._dataMemory[param] ? 1 : 0);
    }
    else if (opcode == 0x11) //SLE	addr
    {
        accumulator = (accumulator <= _program._dataMemory[param] ? 1 : 0);
    }
    else if (opcode == 0x12) //PUSH
    {
        stackPtr--; //stackPtr - 4
        stack[stackPtr] = accumulator;
    }
    else if (opcode == 0x13) //POP
    {
        accumulator = stack[stackPtr];
        stackPtr++; //stackPtr + 4
    }
    else if (opcode == 0x14) //CALL addr
    {
        stackPtr -= 4;
        stack[stackPtr] = PC + 1; //PC + 4
        PC = param;
        return;
    }
    else if (opcode == 0x15) //RET
    {
        PC = stack[stackPtr];
        stackPtr++; //stackPtr + 4
        return;
    }
    else if (opcode == 0x17)
    {
        if (_program._instructions[PC].mnemonic == "exit")
            complete_ = true;
    }

    PC++; //PC + 4
    
    if (opcode != 0x17)
        cycleCount++;
}

void Processor::info()
{
    cout << "|-------------------------|" << endl;
    cout << "| PC: " << setfill(' ') << left << setw(19) << dec << PC << " |" << endl;
    cout << "|-------------------------|" << endl;
    cout << "| Stack ptr: " << setfill(' ') << left << setw(12) << hex << stackPtr << " |" << endl;
    cout << "|-------------------------|" << endl;
    cout << "| Accumulator: 0x" << right << setw(sizeof(int)*2) << setfill('0') << hex << accumulator << " |" << endl;
    cout << "|-------------------------|" << endl;
    
    int prevInstructions = (PC > 2 ? PC - 3 : 0);
    int futureInstructions = (prevInstructions + 6 < _program._instructions.size() ? prevInstructions + 6 : _program._instructions.size() - 1);

    for (int i = prevInstructions; i <= futureInstructions; ++i)
    {
        Instruction instr = _program._instructions[i];
        cout << (i == PC ? "|* " : "|  ") << setfill(' ') << left << setw(7) << instr.mnemonic << " 0x" << right << setfill('0') << setw(sizeof(int)*2) << hex << instr.param << "     |" << endl;
    }
    cout << "|-------------------------|" << endl;
    cout << "| Cycles: " << left << setw(15) << setfill(' ') << dec << cycleCount << " |" << endl;
    cout << "|-------------------------|" << endl;
}

bool Processor::complete()
{
    return complete_;
}