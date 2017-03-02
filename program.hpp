#pragma once

class Program
{
	public:
    int _instrCount;
    void* _instructions; //void pointer because we're casting anyways

	Program();
    Program(int instrCount);

	private:
};