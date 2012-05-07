/*
 * Helper.cpp
 * Code for the helper functions.
 * Author: Dillon Welch
 */ 

#include <iostream>
#include <math.h>
#include <sstream>
#include <stdlib.h>

#include "CPUFunctions.h"
#include "Global.h"
#include "Helper.h"

using namespace std;

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
    else // If the sign bit it 1 (negative #)
    {
        bool test[WORD_SIZE]; // Copy over the word into some temporary memory.
        zeroBoolArray(WORD_SIZE, test);
        copyBooleanArray(word, test);
        
        int overflow = overflowTest(size, word); // Test whether the number is an overflow number (1000 0000 ... 0000).
        
        if(overflow == 0) // If the number is not an overflow number
        {
            switchSign(size, test); // Do two's compliment on the number, and then re-call boolN (since it's now positive)
            sum = boolNtoInt(size, test); // This will be the positive version of the number.
            return -sum; // Return the properly negated version.
        }
        else // Otherwise, do a bitwise not on the number and set the overflow flag.
        {
            OVERFLOW_FLAG = 1;
            bitwiseNot(size, test, test);
            sum = boolNtoInt(size, test);
            return sum;
        }
    }
}

/*
 * int boolNtoIntPositive(int size, bool word[])
 * Converts the binary number (in the bool array) to a positive int.
 * size refers to the size of the boolean array.
 * Returns the converted int.
 */
int boolNtoIntPositive(int size, bool word[])
{
    int sum = 0;
    for(int i = size - 1; i >= 0; i--)
    {
        sum += word[i] * pow(2, i); 
    }
    return sum;
}
/*
 * int boolQuartetToInt(int size, int lengthOfBinaryNumber, int quartetNum, bool word[])
 * Converts a quartet/octet in memory to an integer.
 * Returns the converted integer number.
 */
int boolQuartetToInt(int size, int lengthOfBinaryNumber, int quartetNum, bool word[])
{
    if(lengthOfBinaryNumber != 4 && lengthOfBinaryNumber != 8)
    {
        cerr << "boolQuartetToInt: LengthOfBinaryNumber must be either 4 or 8 but is " << lengthOfBinaryNumber << endl;
        exit(EXIT_FAILURE);
    }
    int i = 4 * (quartetNum - 1); // C0 for 1, C4 for 2, C8 for 3, C 12 for 4.
    int sum = 0;
    for(int j = 0; j < lengthOfBinaryNumber; j++, i++) // Goes either 4 or 8 bits and converts the quartet/octet into an int. 
    {
        sum += word[i] * pow(2, j);
    }
    return sum;
}

/*
 * int getProgramCounter(bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
 * Returns the value of the program counter, which will range from 0 to TOTAL_MEM_SIZE - 1.
 */
int getProgramCounter(bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
{
    int sum = 0;
    for(int i = WORD_SIZE - 1; i >= 0; i--)
    {
        sum += memory[PROGRAM_COUNTER][i] * pow(2, i); 
    }
    return sum;
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
            return overflowTest;
        }
        i--;
    }
    return overflowTest;
}

/*
 * string hexToString(string hexString, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
 * Converts a string in binary, 0b(0, 1)+, into a string with the equivalent int value.
 */
string binaryToString(string binaryString, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
{
    //binaryString = binaryString.substr(2, binaryString.size() - 2); // Takes off the 0b.
    long int subResult = strtol(binaryString.c_str(), NULL, 2); // Converts it to an int.
    
    stringstream ss; // Converts the int into a string.
    ss << subResult;
    string result = ss.str();
    return result;
}

/*
 * string hexToInt(string hexString, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
 * Converts a string in binary, 0b(0, 1)+, into an int with equivalent value.
 */
int binaryToInt(string binaryString, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
{
    //binaryString = binaryString.substr(2, binaryString.size() - 2); // Takes off the 0b.
    long int subResult = strtol(binaryString.c_str(), NULL, 2); // Converts it to an int.
    
    stringstream ss; // Converts the int into a string.
    ss << subResult;
    return subResult;
}

/*
 * string hexToString(string hexString, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
 * Converts a string in hex, 0x(0..F)+, into a string with the equivalent int value.
 */
string hexToString(string hexString, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
{
    int hexNum = 0;
    string result = "";
    
    stringstream ss; // Converts the hex string to an int.
    ss << hex << hexString; //hexString.substr(2, hexString.size() - 2);
    ss >> hexNum;
    
    stringstream sss; // Converts the int back into a string.
    sss << hexNum;
    result = sss.str();
    
    return result;
}

/*
 * string hexToInt(string hexString, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
 * Converts a string in hex, 0x(0..F)+, into an int with equivalent value.
 */
int hexToInt(string hexString, bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
{
    int hexNum = 0;
    string result = "";
    
    stringstream ss; // Converts the hex string to an int.
    ss << hex << hexString; //hexString.substr(2, hexString.size() - 2);
    ss >> hexNum;
    
    return hexNum;
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
    
    // If both numbers were positive and the result is negative, this is an overflow.
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
    
    // If both numbers were positive and the result is negative, this is an overflow.
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
 * void calculateInstructionStrings(bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
 * Calculate the English version of the current instruction, the 2 previous, and the 2 next instructions.
 */
void calculateInstructionStrings(bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
{
    int programLocation = getProgramCounter(memory); // The instruction that is at the location specificed by the program counter.
    int j = programLocation - 2; // Start at 2 before it
    for(int i = 0; j <= programLocation + 2; i++, j++) // Go until 2 after it.
    {
        if(j < 0) // If j is negative, do nothing since memory starts at 0.
        {
            currentInstructionArray[i] = "";
            continue;
        }
        int opCode = boolQuartetToInt(WORD_SIZE, 4, 4, memory[j]); // Get the op code.
        stringstream ins; // Used to concatenate all of the words and the data into one string.
        switch(opCode) // Based on the op code, get the correct registers/data and concatenate them together properly.
        {
            case OP_MOVE:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[j]);
                int regA = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 2, memory[j]);
                ins << "MOVE R" << regD << ", R" << regA;
                break;
            }
            case OP_NOT:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[j]);
                int regA = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 2, memory[j]);
                ins << "NOT R" << regD << ", R" << regA;
                break;
            }
            case OP_AND:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[j]);
                int regA = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 2, memory[j]);
                int regB = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 1, memory[j]);
                ins << "AND R" << regD << ", R" << regA << ", R" << regB;
                break;
            }
            case OP_OR:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[j]);
                int regA = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 2, memory[j]);
                int regB = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 1, memory[j]);
                ins << "OR R" << regD << ", R" << regA << ", R" << regB;
                break;
            }
            case OP_ADD:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[j]);
                int regA = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 2, memory[j]);
                int regB = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 1, memory[j]);
                ins << "ADD R" << regD << ", R" << regA << ", R" << regB;
                break;
            }
            case OP_SUB:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[j]);
                int regA = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 2, memory[j]);
                int regB = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 1, memory[j]);
                ins << "SUB R" << regD << ", R" << regA << ", R" << regB;
                break;
            }
            case OP_ADDI:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[j]);
                int regA = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 2, memory[j]);
                int data = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 1, memory[j]);
                ins << "ADDI R" << regD << ", R" << regA << ", " << data;
                break;
            }
            case OP_SUBI:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[j]);
                int regA = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 2, memory[j]);
                int data = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 1, memory[j]);
                ins << "SUBI R" << regD << ", R" << regA << ", " << data;
                break;
            }
            case OP_SET:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[j]);
                int data = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 2, 1, memory[j]);
                ins << "SET R" << regD << ", " << data;
                break;
            }
            case OP_SETH:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[j]);
                int data = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 2, 1, memory[j]);
                ins << "SETH R" << regD << ", " << data;
                break;
            }
            case OP_INCIZ:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[j]);
                int data = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 2, memory[j]);
                int regB = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 1, memory[j]);
                ins << "INCIZ R" << regD << ", " << data << ", R" << regB;
                break;
            }
            case OP_DECIN:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[j]);
                int data = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 2, memory[j]);
                int regB = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 1, memory[j]);
                ins << "DECIN R" << regD << ", " << data << ", R" << regB;
                break;
            }
            case OP_MOVEZ:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[j]);
                int regA = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 2, memory[j]);
                int regB = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 1, memory[j]);
                ins << "MOVEZ R" << regD << ", R" << regA << ", R" << regB;
                break;
            }
            case OP_MOVEX:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[j]);
                int regA = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 2, memory[j]);
                int regB = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 1, memory[j]);
                ins << "MOVEX R" << regD << ", R" << regA << ", R" << regB;
                break;
            }
            case OP_MOVEP:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[j]);
                int regA = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 2, memory[j]);
                int regB = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 1, memory[j]);
                ins << "MOVEP R" << regD << ", R" << regA << ", R" << regB;
                break;
            }
            case OP_MOVEN:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[j]);
                int regA = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 2, memory[j]);
                int regB = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 1, memory[j]);
                ins << "MOVEN R" << regD << ", R" << regA << ", R" << regB;
                break;
            }
        }
        // Add the string and flush the buffer. Always flush your buffers.
        currentInstructionArray[i] = ins.str();
        ins.flush();
    }
}

/*
 * void copyBooleanArray(bool src[], bool dest[])
 * Copies the source array into the destination array.
 */
void copyBooleanArray(bool src[], bool dest[])
{
    for(int i = WORD_SIZE; i >= 0; i--)
    {
        dest[i] = src[i];
    }
}

/*
 * void copyBooleanArrayQuartet(bool src[], bool dest[], int size, int quartetNum)
 * Copies the source array into the destination array's quartet.
 */
void copyBooleanArrayQuartet(bool src[], bool dest[], int size, int quartetNum)
{
    int i = 4 * (quartetNum - 1);
    for(int j = (size - 1); j >= 0; j--, i++)
    {
        dest[i] = src[j];
    }
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
        number *= -1; // Make the number of positive so it works with the conversion algorithm.
        negative = 1;
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
 * quartetNum should be 1 to start at C0, 2 to start at C4, 3 to start at C8, and 4 to start at C12.
 */
void intToBoolQuartet(int number, int size, int quartetNum, bool word[])
{
    if(number < 0)
    {
        cerr << "Quartets can only be set to positive values." << endl;
        exit(EXIT_FAILURE);
    }
    bool memoryCopy[size];
    intToBoolN(number, size, memoryCopy);
    int i = 4 * (quartetNum - 1);
    for(int j = 0; j < size; j++, i++)
    {
        word[i] = memoryCopy[j];
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
 * void printProgramCounterMemory(bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
 * Prits the binary and English versions of the current instruction, as well as the 2 before and after it.
 */
void printProgramCounterMemory(bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
{
    int instruction = getProgramCounter(memory); // Get the current instruction location.
    calculateInstructionStrings(memory);
    
    bool extraSpaceBefore = false; // Calculate whether extra space needs to be printed to keep all the instructions in line.
    bool extraSpaceAfter = false;
    switch(instruction - 2)
    {
        case 8:
        case 9:
        case 98:
        case 99:
        case 998:
        case 999:
        case 9998:
        case 9999:
        {
            extraSpaceBefore = true;
        }
    }
    switch(instruction + 2)
    {
        case 10:
        case 11:
        case 100:
        case 101:
        case 1000:
        case 1001:
        case 10000:
        case 10001:
        {
            extraSpaceAfter = true;
        }
    }
    
    for(int k = 0, j = instruction - 2; j < instruction + 3; k++, j++)
    {
        if(j < 0) // If j is negative, do nothing since memory starts at 0.
        {
            continue;
        }
        else if(j >= TOTAL_MEM_SIZE) // If j is at or above the max memory size, then we are at the end of memory.
        {
            return;
        }
        cout << j << ": ";
        
        if(extraSpaceBefore == true) // Prints out extra space if the line would otherwise be out of line with the others.
        {
            switch(j)
            {
                case 8:
                case 9:
                case 98:
                case 99:
                case 998:
                case 999:
                case 9998:
                case 9999:
                {
                    cout << " ";
                }
            }
        }
        if(extraSpaceAfter == true)
        {
            switch(j)
            {
                case 6:
                case 7:
                case 8:
                case 9:
                case 96:
                case 97:
                case 98:
                case 99:
                case 996:
                case 997:
                case 998:
                case 999:
                case 9996:
                case 9997:
                case 9998:
                case 9999:
                {
                    cout << " ";
                }
            }
        }
        
        for(int i = WORD_SIZE - 1; i >= 0; i--) // Print out the binary version.
        {
            cout << memory[j][i];
            if(i > 0 && i % 4 == 0) // Space out every 4 bits.
            {
                cout << " ";
            }
        }
        
        cout << " " << currentInstructionArray[k]; // Print out the English version
        
        
        
        if(j == instruction)
        {
            int amountOfSpace = 25;
            int stringSize = currentInstructionArray[k].size();
            int amountToPrint = amountOfSpace - stringSize;
            for(int i = 0; i < amountToPrint; i++)
            {
                cout << " ";
            }
            cout << "<----- Instruction to be executed."; // If this line is the current instruction, print out a note.
        }
        
        cout << endl;
    }
}

/*
 * void printRegisters(bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
 * Prints the registers.
 */
void printRegisters(bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
{
    for(int j = 0; j < 16; j++)
    {
        cout << j << ": ";
        if(j < 10) // If the number is only 1 digit, print out an extra space to line them up correctly.
        {
            cout << " ";
        }
        for(int i = WORD_SIZE - 1; i >= 0; i--) // Print out the binary version.
        {
            cout << memory[j][i];
            if(i > 0 && i % 4 == 0) // Space out every 4 bits.
            {
                cout << " ";
            }
        }
        
        switch(j)
        {
            case OUTPUT_REGISTER_2:
            {
                cout << " " << boolNtoIntPositive(WORD_SIZE, memory[j]) << endl; // Print out the decimal version.
                break;
            }
            case PROGRAM_COUNTER:
            {
                cout << " " << getProgramCounter(memory) << endl; // Print out the decimal version.
                break;
            }
            default:
            {
                cout << " " << boolNtoInt(WORD_SIZE, memory[j]) << endl; // Print out the decimal version.
                break;
            }
            
        }
    }
}

/*
 * void printUserDisplay(bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
 * Calls the functions to print everything to the screen for the user.
 */
void printUserDisplay(bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
{
    system("clear"); // Clear the screen and print the registers and the section of memory around the instruction pointed to by the program counter.
    printRegisters(memory);
    cout << endl;
    printProgramCounterMemory(memory);
    cout << endl;
    cout << "Overflow Flag: " << OVERFLOW_FLAG << endl;
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
    if(location != PROGRAM_COUNTER)
    {
        int negative = 0; // Whether the current number is negative or positive.
        if(number >= TOTAL_VAL_SIZE) // The number is bigger than the max value size.
        {
            OVERFLOW_FLAG = 1;
        }
        else if(number < 0) // The number is negative
        {
            number *= -1; // Make the number of positive so it works with the conversion algorithm.
            negative = 1;
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
    else
    {
        if(number >= TOTAL_MEM_SIZE)
        {
            OVERFLOW_FLAG = 1;
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
 * void waitForEnter()
 * Waits for the enter key to be pressed before executing the next instruction.
 * Type in anything with the letter e to exit the program.
 */
void waitForEnter(bool memory[TOTAL_MEM_SIZE][WORD_SIZE])
{
    cout << endl << "Type in e or exit to quit, hit enter to continue, or type in a number between 0 and ";
    cout << TOTAL_MEM_SIZE - 1 << endl << "to move the program counter to that location." << endl;
    int c;
    fflush( stdout );
    stringstream ss;
    int programCounterFlag = 0;
    do 
    {
        c = getchar(); 
        if(c == 101) // The letter e.
        {
            exit(EXIT_SUCCESS);
        }
        else if(c >= 48 && c <=57)
        {
            ss << (char)c;
            programCounterFlag = 1;
        }
    }
    while ((c != '\n') && (c != EOF));
    if(programCounterFlag == 1)
    {
        int programCounter = 0;
        ss >> programCounter;
        setMemoryInt(PROGRAM_COUNTER, programCounter, memory);
        printUserDisplay(memory);
        cout << endl << "Type in e or exit to quit, or hit enter to continue." << endl;
        c = 0;
        fflush( stdout );
        do 
        {
            c = getchar(); 
            if(c == 101) // The letter e.
            {
                exit(EXIT_SUCCESS);
            }
        }
        while ((c != '\n') && (c != EOF));
    }
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