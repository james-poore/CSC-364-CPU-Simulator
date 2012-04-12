/*
 * Helper.cpp
 * Code for the helper functions.
 * Author: Dillon Welch
 */ 

#include <iostream>

#include <math.h>

#include "CPUFunctions.h"
#include "Global.h"
#include "Helper.h"

using namespace std;

/* TODO: Test whether boolN sets negative #s sign bit correctly.
         Comment bitwiseAdd and bitwiseAddImm */

/*
 * int boolNtoInt(int size, bool word[])
 * Converts the binary number (in the bool array) to an int.
 * size refers to the size of the boolean array.
 * Returns the converted int.
 */
int boolNtoInt(int size, bool word[])
{
	int sum = 0;
    if(word[size - 1] == 0) // If the sign bit is 0 (positive #) directly convert using base conversion algorithm.
    {
        for(int i = size - 1; i >= 0; i--)
        {
            sum += word[i] * pow(2, i); 
        }
        return sum;
    }
    else // If the sign bit it 1 (negative #) first do two's complement, then convert that binary # to an int, then negate that int. 
    {
        //int i = size - 2;
        //int overflowTest = 1;
        // Test to see if the number is of the form 1000 0000 ... 0000. If so, this is an overflow, since two's complement will result in the same number (0111 1111 ... 1111 + 0001 = 1000 0000 ... 0000).
        /*while (i >= 0) 
        {
            if(word[i] == 1)
            {
                overflowTest = 0;
                break;
            }
            i--;
        }*/
        int overflow = overflowTest(size, word);
        
        if(overflow == 0) // If the number is not an overflow number, proceed as normal.
        {
            switchSign(size, word);
            sum = boolNtoInt(size, word);
            return -sum;
        }
        else // Otherwise, do a bitwise not on the number and set the overflow flag.
        {
            OVERFLOW_FLAG = 1;
            bitwiseNot(size, word, word);
            sum = boolNtoInt(size, word);
            return sum;
        }
    }
}

/*
 * int overflowTest(int size, bool word[])
 * Tests whether a binary number overflows two's complement (1000 0000 ... 0000).
 * size refers to the size of the boolean array.
 * Returns 0 if it does not, and 1 if it does.
 */
int overflowTest(int size, bool word[])
{
    // Do the code from boolNtoInt to test whether the # is an overflow, including 1000 0000 ... 000 and if > TOTAL_VAL_SIZE
    int i = size - 2;
    int overflowTest = 1;
    // Test to see if the number is of the form 1000 0000 ... 0000. If so, this is an overflow, since two's complement will result in the same number (0111 1111 ... 1111 + 0001 = 1000 0000 ... 0000).
    while (i >= 0) 
    {
        if(word[i] == 1)
        {
            overflowTest = 0;
            break;
        }
        i--;
    }
    return overflowTest;
}

/*
 * void bitwiseAdd(int sizeA, bool wordA[], int sizeB, bool wordB[], bool result[])
 * Takes two binary numbers and bitwise adds them and stores into result.
 * sizeA and sizeB refer to the size of wordA and wordB respectively.
 */
void bitwiseAdd(int sizeA, bool wordA[], int sizeB, bool wordB[], bool result[])
{
    int carryIn = 0; // Carry in, starts at 0.
    int counter = 0; // Counter for result.
    int counterA = 0; // Counters for positions in A and B values.
    int counterB = 0;
    int resultVal = 0; // Result of the current addition.
    
    while(counterA < sizeA && counterB < sizeB) // While we still have numbers to add.
    {
        resultVal = wordA[counterA] + wordB[counterB] + carryIn;
        switch(resultVal)
        {
            case 0:
            case 1: // If the result is less than 2 then carry out is 0.
            {
                result[counter] = resultVal;
                carryIn = 0;
                break;
            }
            case 2: // Carry out of 1 but 0 in the current column.
            {
                result[counter] = 0;
                carryIn = 1;
                break;
            }
            case 3: // Carry out of 1 and 1 in the current column (all three #s are 1).
            {
                result[counter] = 1;
                carryIn = 1;
                break;
            }
        }
        counter++;
        counterA++;
        counterB++;
    }
    // If there are still values left in one of the arrays, copy them directly over into result.
    // 1001 0101 + 1010 = 1001 1111 -> 149 + 10 = 159.
    if(counterA == sizeA)
    {
        while(counterB < sizeB)
        {
            result[counter] = wordB[counterB];
            counter++;
            counterB++;
        }
    }
    else if(counterB == sizeB)
    {
        while(counterA < sizeA)
        {
            result[counter] = wordA[counterA];
            counter++;
            counterA++;
        }
    }
    
    if((wordA[sizeA - 1] == 0 && wordB[sizeB - 1] == 0) && result[counter - 1] == 1)
    {
        OVERFLOW_FLAG = 1;
    }
}

/*
 * void bitwiseAddImm(int sizeA, bool wordA[], int addImm, bool result[])
 * Takes a binary number and an int and bitwise adds them and stores into result.
 * sizeA refers to the size of wordA.
 */
void bitwiseAddImm(int sizeA, bool wordA[], int addImm, bool result[])
{
    int carryIn = 0; // Carry in, starts at 0.
    int counterA = 0; // Counter for position in A value.
    int resultVal = 0; // Result of the current addition.
    
    bool wordB[sizeA]; // Convert the int to a binary number. Same size as wordA, padded with 0's if smaller than 16 bits.
    intToBoolN(addImm, sizeA, wordB);
    
    while(counterA < sizeA)
    {
        resultVal = wordA[counterA] + wordB[counterA] + carryIn;
        switch(resultVal)
        {
            case 0:
            case 1: // If the result is less than 2 then carry out is 0.
            {
                result[counterA] = resultVal;
                carryIn = 0;
                break;
            }
            case 2: // Carry out of 1 but 0 in the current column.
            {
                result[counterA] = 0;
                carryIn = 1;
                break;
            }
            case 3: // Carry out of 1 and 1 in the current column (all three #s are 1).
            {
                result[counterA] = 1;
                carryIn = 1;
                break;
            }
        }
        counterA++;
    }
    
    if((wordA[sizeA - 1] == 0 && wordB[sizeA - 1] == 0) && result[sizeA - 1] == 1)
    {
        OVERFLOW_FLAG = 1;
    }
}

/*
 * void bitwiseNot(int size, bool word[], bool result[])
 * Takes a binary number and does a bitwise not on it and stores into result.
 */
void bitwiseNot(int size, bool word[], bool result[])
{
    for(int i = size - 1; i >= 0; i--) // Bitwise not the number.
	{
        if(word[i] == 0)
        {
            result[i] = 1;
        }
        else
        {
            result[i] = 0;
        }
	}
}

/*
 * void printBoolArray(int size, bool word[])
 * Prints the given binary number (in the bool array).  
 * size refers to the size of the boolean array.
 */
void printBoolArray(int size, bool word[])
{
	for(int i = size - 1; i >= 0; i--)
	{
		cout << word[i];
		if(i > 0 && i % 4 == 0) // Print a space between every four numbers.
		{
			cout << " ";
		}
	}
	cout << endl;
}

/*
 * void intToBoolN(int number, int size, bool word[])
 * Converts the number to binary and stores it in a bool[size].
 * If number of bits in binary is smaller than size, the rest of the array will be zeroed out.
 * size refers to the size of the boolean array.
 */
void intToBoolN(int number, int size, bool word[])
{
	int negative = 0; // Whether the current number is negative or positive.
	if(number >= TOTAL_VAL_SIZE || number >= pow(2, size))  // The number is bigger than the max value size.
	{
		OVERFLOW_FLAG = 1;
	}
	else if(number < 0) // The number is negative
	{
		NEGATIVE_FLAG = 1;
        number *= -1; // Make the number of positive so it works with the conversion algorithm.
        negative = 1;
        
        cout << "Negative flag has been set." << endl;
	}

	int i = 0;
	while(number > 0) // Using the convert int to binary algorithm, convert to binary.
	{
		int x = number % 2;
		number = number / 2;
		word[i] = x;
		i++;
	}
	// Pads the rest of the number with 0's if it's smaller than size bits.
	if(i < size)
	{
		for(int j = size - 1; j >= i; j--)
		{
			word[j] = 0;
		}
	}

	if(negative == 1) // If the original number was negative, the current value is positive so must be switched. 
	{
		switchSign(size, word);
	}
}

/*
 * void intToBoolQuartet(int number, int size, int quartetNum, bool word[])
 * Converts the number to binary and stores it in the given quartet of word.
 * If the number of bits in the binary version of number is smaller than size, then it will be padded with 0's.
 * size refers to the boolean array word.
 * quartetNum should be 1 to start at C0, 2 to start at C3, 3 to start at C7, and 4 to start at C11.
 */
void intToBoolQuartet(int number, int size, int quartetNum, bool word[])
{
    if(number < 0)
    {
        OVERFLOW_FLAG = 1; // Error, should only be positive numbers.
    }
    bool memoryCopy[size];
    intToBoolN(number, size, memoryCopy);
    int i = 4 * (quartetNum - 1);
    for(int j = 0; j < size; j++, i++)
    {
        word[i] = memoryCopy[j];
    }
    
	/*int negative = 0;
	bool temp[size];


	if(number < 0)
	{
		number *= -1;
		negative = 1;
	}

	int i = 4 * (quartetNum - 1); // Starting position of the quartet (least significant bit).
	while(number > 0)
	{
		int x = number % 2;
		number = number / 2;
		word[i] = x;
		i++;
	}

	if(negative == 1)
	{
		switchSign(size, word);
	}*/
}

/*
 * void printMemoryLocation(int index, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
 * Prints the given index of memory.
 */
void printMemoryLocation(int index, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
{
    cout<<index<<": ";
	for(int i = WORD_SIZE - 1; i >= 0; i--)
	{
		cout << memory[index][i];
		if(i > 0 && i % 4 == 0)
		{
			cout << " ";
		}
	}
	cout << endl;
}

/*
 * void setMemoryBoolArray(int location, bool number[WORD_SIZE], bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
 * Sets the given memory location to the given number in the boolean array.
 * number must have values in all 16 slots (must be padded with 0's if the value is not 16 bits)
 * Example: 40 would be 0000 0000 0010 1010.
 */
void setMemoryBoolArray(int location, bool number[WORD_SIZE], bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
{
	for(int i = WORD_SIZE - 1; i >= 0; i--)
	{
		memory[location][i] = number[i];
	}
}

/*
 * void setMemoryInt(int location, int number, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
 * Sets the given memory location to the given integer number.
 */
void setMemoryInt(int location, int number, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
{
	int negative = 0; // Whether the current number is negative or positive.
	if(number >= TOTAL_VAL_SIZE) // The number is bigger than the max value size.
	{
		OVERFLOW_FLAG = 1;
	}
	else if(number < 0) // The number is negative
	{
		NEGATIVE_FLAG = 1;
		number *= -1; // Make the number of positive so it works with the conversion algorithm.
        negative = 1;
        
        cout << "Negative flag has been set." << endl;
	}

	int i = 0;
	while(number > 0)  // Using the convert int to binary algorithm, convert to binary.
	{
		int x = number % 2;
		number = number / 2;
		memory[location][i] = x;
		i++;
	}
	// Pads the rest of the number with 0's if it's smaller than WORD_SIZE bits.
	if(i < TOTAL_MEM_SIZE)
	{
		for(int j = WORD_SIZE - 1; j >= i; j--)
		{
			memory[location][j] = 0;
		}
	}

	if(negative == 1)  // If the original number was negative, the current value in memory is positive so must be switched. 
	{
		switchSign(WORD_SIZE, memory[location]);
	}
}

/*
 * void switchSign(int size, bool number[])
 * Does two's complement on a binary number.
 */
void switchSign(int size, bool number[])
{
	for(int i = size - 1; i >= 0; i--) // Bitwise not the number.
	{
			if(number[i] == 0)
			{
				number[i] = 1;
			}
			else
			{
				number[i] = 0;
			}
	}
    bitwiseAddImm(size, number, 1, number); // Add 1 to it.
}

/*
 * void zeroBoolArray(int size, bool word[])
 * Zeroes out a boolean array.
 */
void zeroBoolArray(int size, bool word[])
{
	for(int i = 0; i < size; i++)
	{
		word[i] = 0;
	}
}