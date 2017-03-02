#include "processor.hpp"

Processor::Processor(Program *program)
{
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
        accumulator = _dataMemory[param];
    }
    else if (opcode == 0x01) //LOADI addr
    {
        accumulator = _dataMemory[_dataMemory[param]];
    }
    else if (opcode == 0x02) //STORE addr
    {
        _dataMemory[param] = accumulator;
    }
    else if (opcode == 0x03) //STOREI addr
    {
        _dataMemory[_dataMemory[param]] = accumulator;
    }
    else if (opcode == 0x04) //ADD addr
    {
        accumulator = accumulator + _dataMemory[param];
    }
    else if (opcode == 0x05) //ADDI const
    {
		accumulator = accumulator + param;
    }
    else if (opcode == 0x06) //AND addr
    {
        accumulator = accumulator & _dataMemory[param];
    }
    else if (opcode == 0x07) //OR addr
    {
        accumulator = accumulator | _dataMemory[param];
    }
    else if (opcode == 0x08) //NOT
    {
        accumulator = !accumulator;
    }
    else if (opcode == 0x09) //XOR addr
    {
        accumulator = accumulator ^ _dataMemory[param];
    }
    else if (opcode == 0x0A) //JUMP const
    {
        //PC = _labels[param];
    }
    else if (opcode == 0x0B) //BZERO addr
    {
        PC = (accumulator == 0 ? _dataMemory[param] : PC + 4);
        return;
    }
    else if (opcode == 0x0C) //SEQ	addr
    {
        accumulator = (accumulator == _dataMemory[param] ? 1 : 0);
    }
    else if (opcode == 0x0D) //SNE	addr
    {
        accumulator = (accumulator != _dataMemory[param] ? 1 : 0);
    }
    else if (opcode == 0x0E) //SGT	addr
    {
        accumulator = (accumulator > _dataMemory[param] ? 1 : 0);
    }
    else if (opcode == 0x0F) //SLT	addr
    {
        accumulator = (accumulator < _dataMemory[param] ? 1 : 0);
    }
    else if (opcode == 0x10) //SGE	addr
    {
        accumulator = (accumulator >= _dataMemory[param] ? 1 : 0);
    }
    else if (opcode == 0x11) //SLE	addr
    {
        accumulator = (accumulator <= _dataMemory[param] ? 1 : 0);
    }
    else if (opcode == 0x12) //PUSH
    {
        stackPtr -= 4;
        _dataMemory[stackPtr] = accumulator;
    }
    else if (opcode == 0x13) //POP
    {
        accumulator = _dataMemory[stackPtr];
        stackPtr += 4;
    }
    else if (opcode == 0x14) //CALL addr
    {
        stackPtr -= 4;
        _dataMemory[stackPtr] = PC + 4;
        PC = _dataMemory[param];
        return;
    }
    else if (opcode == 0x15) //RET
    {
        PC = _dataMemory[stackPtr];
        stackPtr += 4;
        return;
    }

    PC += 4;
}