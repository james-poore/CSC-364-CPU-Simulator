#include <iostream>
#include <math.h>
#include <stdio.h>

#include "CPUFunctions.h"
#include "Global.h"
#include "Helper.h"

using namespace std;

bool memory [TOTAL_MEM_SIZE] [WORD_SIZE]; 

int NEGATIVE_FLAG = 0;
int OVERFLOW_FLAG = 0;

/* NOTE: Functions go from most significant bit to least significant bit. */

int main()
{

	/*setMemoryInt(0, 30000, memory);
	setMemoryInt(1,1, memory);
	set(0, 42, memory);
    setH(0, -42, memory);
    incIZ(2, 15, 1, memory);
	printMemoryLocation(0, memory);
	printMemoryLocation(1, memory);
	printMemoryLocation(2, memory);
	cout << "Result of subI: " << boolNtoInt(WORD_SIZE, memory[2]) << endl;*/

    setMemoryInt(0, 0, memory);
    setMemoryInt(1, 1, memory);
    setMemoryInt(2, -1, memory);
    setMemoryInt(3, 5, memory);
    for(int i = 0; i < 4; i++)
    {
        printMemoryLocation(i, memory);
    }
    cout << endl << endl;
    moveZ(4, 3, 1, memory);
    moveX(5, 3, 0, memory);
    moveP(6, 3, 2, memory);
    moveN(7, 3, 1, memory);
    for(int i = 4; i < 8; i++)
    {
        printMemoryLocation(i, memory);
    }
    cout << "Negative flag: " << NEGATIVE_FLAG << endl;
    cout << "Overflow flag: " << OVERFLOW_FLAG << endl;
    
    /*setMemoryInt(0, 5, memory);
    setMemoryInt(1, 1, memory);
    bitwiseAdd(WORD_SIZE, memory[0], WORD_SIZE, memory[1], memory[2]);
	printMemoryLocation(0, memory);
	printMemoryLocation(1, memory);
	printMemoryLocation(2, memory);
    bitwiseAddImm(WORD_SIZE, memory[0], 1, memory[3]);
    cout << endl << endl;
    printMemoryLocation(0, memory);
	printMemoryLocation(3, memory);*/
    
    /*int num = -5;
    cout << "Original num = " << num << endl;
    bool test[WORD_SIZE];
    intToBoolN(num, WORD_SIZE, test);
    cout << "FIRST" << endl;
    printBoolArray(WORD_SIZE, test);
    int tests = boolNtoInt(WORD_SIZE, test);
    cout << "Final result: " << tests << endl;*/

	
	/*for(int i = 0; i < TOTAL_MEM_SIZE; i++)
	{
		printWord(i);
	}*/
	//int x = 0;//b0110011001100110;
	//not(1, 0);
	//printWord(1);

	/*memory = new bool*[WORD_SIZE];
	for(int i = 0; i < TOTAL_MEM_SIZE; ++i)
	{
		if(i % 1000 == 0)
		{
			cout << "Success!" << endl;
		}
		memory[i] = new bool[WORD_SIZE];
	}
	/*
	setMemoryInt(0, 19);
	bool test[WORD_SIZE];
	for(int i = 0; i < WORD_SIZE; i++)
	{
		if(i % 2 == 0)
		{
			test[i] = 0;
		}
		else
		{
			test[i] = 1;
		}
	}
	setMemoryBoolArray(1, test);
		printWord(0);
	printWord(1);
	and(2, 1, 0);

	printWord(2);*/

	/*cout << endl;
	bool** rawr;
	rawr = new bool*[WORD_SIZE];
	for(int i = 0; i < TOTAL_MEM_SIZE; ++i)
	{
		if(i % 1000 == 0)
		{
			cout << "Success!" << endl;
		}
		rawr[i] = new bool[WORD_SIZE];
	}

	for(int i = WORD_SIZE - 1; i >= 0; i--)
	{
		rawr[0][i] = 1;
	}

	for(int i = WORD_SIZE - 1; i >= 0; i--)
	{
		cout << rawr[0][i];
		if(i > 0 && i % 4 == 0)
		{
			cout << " ";
		}
	}
	cout << endl;*/
	
}