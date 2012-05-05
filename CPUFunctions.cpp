/*
 * CPUFunctions.cpp
 * Code for the 16 CPU functions.
 * Author: Dillon Welch
 */ 

/* NOTE: Functions go from most significant bit to least significant bit. */

#include <iostream>
#include <stdlib.h>

#include "CPUFunctions.h"
#include "Global.h"
#include "Helper.h"

using namespace std;

/*
 * void move(int regD, int regA, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
 * Moves the value from regA into regD in the memory array passed.
 */
void move(int regD, int regA, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
{
	for(int i = WORD_SIZE - 1; i >= 0; i--) // Moves in the value bit by bit into regD
	{
		memory[regD][i] = memory[regA][i];
	}
}

/*
 * void not_op(int regD, int regA, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
 * Does a bitwise not of regA and stores into regD in the memory array passed.
 */
void not_op(int regD, int regA, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
{
	for(int i = WORD_SIZE - 1; i >= 0; i--) // Nots each bit and move it into regD.
	{
		if(memory[regA][i] == 0)
		{

			memory[regD][i] = 1;
		}
		else if(memory[regA][i] == 1)
		{

			memory[regD][i] = 0;
		}
		else // Somehow there was a non binary value in memory.
		{
			cerr << "Error. Memory has a value that is not 0 or 1." << endl;
			exit(1);
		}
	}
}

/* 
 * void and_op(int regD, int regA, int regB, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
 * Does a bitwise and of regA and regB and stores into regD in the memory array passed.
 */
void and_op(int regD, int regA, int regB, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
{
	for(int i = WORD_SIZE - 1; i >= 0; i--)
	{
		if(memory[regA][i] == 1 && memory[regB][i] == 1)
		{
			memory[regD][i] = 1;
		}
		else
		{
			memory[regD][i] = 0;
		}
	}
}

/* 
 * void or_op(int regD, int regA, int regB, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
 * Does a bitwise or of regA and regB and stores into regD in the memory array passed.
 */
void or_op(int regD, int regA, int regB, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
{
	for(int i = WORD_SIZE - 1; i >= 0; i--)
	{
		if(memory[regA][i] == 1 || memory[regB][i] == 1)
		{
			memory[regD][i] = 1;
		}
		else
		{
			memory[regD][i] = 0;
		}
	}
}

/* 
 * void add(int regD, int regA, int regB, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
 * Adds regA and regB and stores into regD in the memory array passed.
 */
void add(int regD, int regA, int regB, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
{
    bitwiseAdd(WORD_SIZE, memory[regA], WORD_SIZE, memory[regB], memory[regD]);
}

/* 
 * void sub(int regD, int regA, int regB, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
 * Subtracts regA and regB and stores into regD in the memory array passed.
 */
void sub(int regD, int regA, int regB, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
{
	int a = boolNtoInt(WORD_SIZE, memory[regA]); // Turns the values in memory into ints.
	int b = boolNtoInt(WORD_SIZE, memory[regB]);
	int d = a - b; 
    /*if(a > 0 && a < b && d < 0)
    {
        OVERFLOW_FLAG = 1;
    }*/
	bool result[WORD_SIZE]; 
	intToBoolN(d, WORD_SIZE, result); // Converts the result of the integer subtraction into binary, store it in result.
	setMemoryBoolArray(regD, result, memory);
}

/* 
 * void addI(int regD, int regA, int data4, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
 * Adds regA and the value of data4 and stores into regD in the memory array passed.
 */
void addI(int regD, int regA, int data4, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
{
    bitwiseAddImm(WORD_SIZE, memory[regA], data4, memory[regD]);
}

/* 
 * void subI(int regD, int regA, int data4, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
 * Subtracts regA and the value of data4 and stores into regD in the memory array passed.
 */
void subI(int regD, int regA, int data4, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
{
    int a = boolNtoInt(WORD_SIZE, memory[regA]); // Turns regA's value into an int.
    int d = a - data4;
    
    bool result[WORD_SIZE];
	intToBoolN(d, WORD_SIZE, result); // Converts the result of the integer subtraction into binary, store it in result.
	setMemoryBoolArray(regD, result, memory);
}

/*
 * void set(int regD, int data8, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
 * Sets regD to 8 0's followed by an 8 bit number.
 */
void set(int regD, int data8, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
{
    setMemoryInt(regD, data8, memory);
}

/*
 * void setH(int regD, int data8, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
 * Sets the high bits of regD to data8 and then copies over the low bits.
 */
void setH(int regD, int data8, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
{
    bool memoryCopy[WORD_SIZE / 2];
    intToBoolN(data8, WORD_SIZE / 2, memoryCopy); // Convert the data into a binary number.
    
    int j = (WORD_SIZE / 2) - 1;
    for(int i = WORD_SIZE - 1; i >= 0; i--) // Copies the number into memory's high bits
    {
        if(i >= WORD_SIZE / 2)
        {
            // memory[regD][15] = memoryCopy[7]
            // memory[regD][14] = memoryCopy[6]
            // ... all the way to
            // memory[regD][8]  = memoryCopy[0]
            memory[regD][i] = memoryCopy[j];
            j--;
        }
    }
}

/*
 * void incIZ(int regD, int data4, int regB, bool memory[TOTAL_MEM_SIZE][WORD_SIZE]);
 * Adds regD and the value of data4 if regB is 0.
 */
void incIZ(int regD, int data4, int regB, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
{
    int result = 1;
    for(int i = WORD_SIZE - 1; i >= 0; i--) // Scan through the memory, if any of the values are 1 then the number is not 0.
    {
        if(memory[regB][i] == 1)
        {
            result = 0;
            break;
        }
    }
    
    if(result == 1) // If all the values were 0, do the addI. 
    {
        addI(regD, regD, data4, memory);
    }
}

/*
 * void decIN(int regD, int data4, int regB, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
 * Subtracts regD and the value of data4 if regB15 is 1 (negative).
 */
void decIN(int regD, int data4, int regB, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
{
    if(memory[regB][WORD_SIZE - 1] == 1)
    {
        subI(regD, regD, data4, memory);
    }
}

/*
 * void moveZ(int regD, int regA, int regB, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
 * Moves regA into regD if regB is 0.
 */
void moveZ(int regD, int regA, int regB, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
{
    int result = 1;
    for(int i = WORD_SIZE - 1; i >= 0; i--) // Scan through the memory, if any of the values are 1 then the number is not 0.
    {
        if(memory[regB][i] == 1)
        {
            result = 0;
            break;
        }
    }
    if(result == 1) // If all the values are 0, do the move.
    {
        move(regD, regA, memory);
    }
}

/*
 * void moveX(int regD, int regA, int regB, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
 * Moves regA into regD if regB is not 0.
 */
void moveX(int regD, int regA, int regB, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
{
    int result = 0;
    for(int i = WORD_SIZE - 1; i >= 0; i--) // Scan through the memory, if any of the values are 1 then the number is not 0.
    {
        if(memory[regB][i] == 1)
        {
            result = 1;
            break;
        }
    }
    if(result == 1) // If any of the values are not 0, then do the move.
    {
        move(regD, regA, memory);
    }
}

/*
 * void moveP(int regD, int regA, int regB, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
 * Moves regA into regD if regB15 is 0 (positive number).
 */
void moveP(int regD, int regA, int regB, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
{
    if(memory[regB][WORD_SIZE - 1] == 0)
    {
        move(regD, regA, memory);
    }
}

/*
 * void moveN(int regD, int regA, int regB, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
 * Moves regA into regD if regB15 is 1 (negative number).
 */
void moveN(int regD, int regA, int regB, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
{
    if(memory[regB][WORD_SIZE - 1] == 1)
    {
        move(regD, regA, memory);
    }
}
