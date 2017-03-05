#include <iostream>
using std::cout;
using std::endl;

#include "processor.hpp"

Processor::Processor(Program *program)
{
    PC = 0;
    accumulator = 0;
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
	int instruction = *((int*)((char*)(_program->_instructions) + PC));
	int opcode = instruction >> (31 - 5);
	int param = instruction & 0x07FFFFFF;

    if (opcode == 0x00) //LOAD addr
    {
        accumulator = *((int*)((char*)(_program->_dataMemory) + param));
    }
    else if (opcode == 0x01) //LOADI addr
    {
        int addr = *((int*)((char*)(_program->_dataMemory) + param));
        accumulator = *((int*)((char*)(_program->_dataMemory) + addr));
    }
    else if (opcode == 0x02) //STORE addr
    {
        *((int*)((char*)(_program->_dataMemory) + param)) = accumulator;
    }
    else if (opcode == 0x03) //STOREI addr
    {
        int addr = *((int*)((char*)(_program->_dataMemory) + param));
        *((int*)((char*)(_program->_dataMemory) + addr)) = accumulator;
    }
    else if (opcode == 0x04) //ADD addr
    {
        accumulator = accumulator + *((int*)((char*)(_program->_dataMemory) + param));
    }
    else if (opcode == 0x05) //ADDI const
    {
		accumulator = accumulator + param;
    }
    else if (opcode == 0x06) //AND addr
    {
        accumulator = accumulator & *((int*)((char*)(_program->_dataMemory) + param));
    }
    else if (opcode == 0x07) //OR addr
    {
        accumulator = accumulator | *((int*)((char*)(_program->_dataMemory) + param));
    }
    else if (opcode == 0x08) //NOT
    {
        accumulator = !accumulator;
    }
    else if (opcode == 0x09) //XOR addr
    {
        accumulator = accumulator ^ *((int*)((char*)(_program->_dataMemory) + param));
    }
    else if (opcode == 0x0A) //JUMP const
    {
        //PC = _labels[param];
    }
    else if (opcode == 0x0B) //BZERO addr
    {
        PC = (accumulator == 0 ? *((int*)((char*)(_program->_dataMemory) + param)) : PC + 4);
        return;
    }
    else if (opcode == 0x0C) //SEQ	addr
    {
        accumulator = (accumulator == *((int*)((char*)(_program->_dataMemory) + param)) ? 1 : 0);
    }
    else if (opcode == 0x0D) //SNE	addr
    {
        accumulator = (accumulator != *((int*)((char*)(_program->_dataMemory) + param)) ? 1 : 0);
    }
    else if (opcode == 0x0E) //SGT	addr
    {
        accumulator = (accumulator > *((int*)((char*)(_program->_dataMemory) + param)) ? 1 : 0);
    }
    else if (opcode == 0x0F) //SLT	addr
    {
        accumulator = (accumulator < *((int*)((char*)(_program->_dataMemory) + param)) ? 1 : 0);
    }
    else if (opcode == 0x10) //SGE	addr
    {
        accumulator = (accumulator >= *((int*)((char*)(_program->_dataMemory) + param)) ? 1 : 0);
    }
    else if (opcode == 0x11) //SLE	addr
    {
        accumulator = (accumulator <= *((int*)((char*)(_program->_dataMemory) + param)) ? 1 : 0);
    }
    else if (opcode == 0x12) //PUSH
    {
        stackPtr -= 4;
        *((int*)((char*)(_program->_dataMemory) + stackPtr)) = accumulator;
    }
    else if (opcode == 0x13) //POP
    {
        accumulator = *((int*)((char*)(_program->_dataMemory) + stackPtr));
        stackPtr += 4;
    }
    else if (opcode == 0x14) //CALL addr
    {
        stackPtr -= 4;
        *((int*)((char*)(_program->_dataMemory) + stackPtr)) = PC + 4;
        PC = *((int*)((char*)(_program->_dataMemory) + param));
        return;
    }
    else if (opcode == 0x15) //RET
    {
        PC = *((int*)((char*)(_program->_dataMemory) + stackPtr));
        stackPtr += 4;
        return;
    }

    PC += 4;
}

void Processor::info()
{
    cout << accumulator << endl;
}