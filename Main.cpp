
#include <iostream>
#include <math.h>
#include <stdio.h>


#include "CPUFunctions.h"
#include "Global.h"
#include "Helper.h"
#include "loader.h"

using namespace std;

bool memory [TOTAL_MEM_SIZE] [WORD_SIZE]; 

int PROG_LOC = 0;

int NEGATIVE_FLAG = 0;
int OVERFLOW_FLAG = 0;

string currentInstructionArray[5];

/* NOTE: Functions go from most significant bit to least significant bit. */

void runProgram()
{
    while(true)
    {
        int programLocation = boolNtoInt(WORD_SIZE, memory[PROGRAM_COUNTER]); // Get the current instruction location.
        PROG_LOC = programLocation;
        int endOfProgram = 0; // Whether or not this instruction is MOVE R15, R15.
        int opCode = boolQuartetToInt(WORD_SIZE, 4, 4, memory[programLocation]); // Get the op code.
        switch(opCode) // Based on the op code, get the rest of the needed values and do the appropriate instruction.
        {
            case OP_MOVE:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[programLocation]);
                int regA = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 2, memory[programLocation]);
                move(regD, regA, memory);
                
                // If the command is MOVE R15, R15, this signifies the end of program and it should stop going forward at this point.
                if(regD == PROGRAM_COUNTER && regA == PROGRAM_COUNTER)
                {
                    endOfProgram = 1;
                }
                break;
            }
            case OP_NOT:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[programLocation]);
                int regA = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 2, memory[programLocation]);
                not_op(regD, regA, memory);
                break;
            }
            case OP_AND:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[programLocation]);
                int regA = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 2, memory[programLocation]);
                int regB = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 1, memory[programLocation]);
                and_op(regD, regA, regB, memory);
                break;
            }
            case OP_OR:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[programLocation]);
                int regA = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 2, memory[programLocation]);
                int regB = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 1, memory[programLocation]);
                or_op(regD, regA, regB, memory);
                break;
            }
            case OP_ADD:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[programLocation]);
                int regA = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 2, memory[programLocation]);
                int regB = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 1, memory[programLocation]);
                add(regD, regA, regB, memory);
                break;
            }
            case OP_SUB:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[programLocation]);
                int regA = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 2, memory[programLocation]);
                int regB = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 1, memory[programLocation]);
                sub(regD, regA, regB, memory);
                break;
            }
            case OP_ADDI:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[programLocation]);
                int regA = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 2, memory[programLocation]);
                int data = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 1, memory[programLocation]);
                addI(regD, regA, data, memory);
                break;
            }
            case OP_SUBI:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[programLocation]);
                int regA = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 2, memory[programLocation]);
                int data = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 1, memory[programLocation]);
                subI(regD, regA, data, memory);
                break;
            }
            case OP_SET:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[programLocation]);
                int data = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 2, 1, memory[programLocation]);
                set(regD, data, memory);
                break;
            }
            case OP_SETH:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[programLocation]);
                int data = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 2, 1, memory[programLocation]);
                setH(regD, data, memory);
                break;
            }
            case OP_INCIZ:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[programLocation]);
                int data = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 2, memory[programLocation]);
                int regB = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 1, memory[programLocation]);
                incIZ(regD, data, regB, memory);
                break;
            }
            case OP_DECIN:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[programLocation]);
                int data = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 2, memory[programLocation]);
                int regB = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 1, memory[programLocation]);
                decIN(regD, data, regB, memory);
                break;
            }
            case OP_MOVEZ:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[programLocation]);
                int regA = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 2, memory[programLocation]);
                int regB = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 1, memory[programLocation]);
                moveZ(regD, regA, regB, memory);
                break;
            }
            case OP_MOVEX:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[programLocation]);
                int regA = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 2, memory[programLocation]);
                int regB = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 1, memory[programLocation]);
                moveX(regD, regA, regB, memory);
                break;
            }
            case OP_MOVEP:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[programLocation]);
                int regA = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 2, memory[programLocation]);
                int regB = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 1, memory[programLocation]);
                moveP(regD, regA, regB, memory);
                break;
            }
            case OP_MOVEN:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[programLocation]);
                int regA = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 2, memory[programLocation]);
                int regB = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 1, memory[programLocation]);
                moveN(regD, regA, regB, memory);
                break;
            }
        }
        
        // If the program counter was not changed as part of an instruction, and if the instruction is not MOVE R15, R15, then increase the program counter by 1.
        if(programLocation == boolNtoInt(WORD_SIZE, memory[PROGRAM_COUNTER]) && endOfProgram == 0)
        {
            programLocation += 1;
            setMemoryInt(PROGRAM_COUNTER, programLocation, memory);
        }
        
        // Clear the screen and print the registers and the section of memory around the instruction pointed to by the program counter..
        system("clear");
        printRegisters(memory);
        cout << endl;
        printProgramCounterMemory(memory);
        cout << endl;
        cout << "Overflow Flag: " << OVERFLOW_FLAG << endl;
        
        
        // Wait for the user to press enter before moving on to the next instruction.
        waitForEnter();
    }
}

// Error checking on PC, R6, R13, R14
// When a move on a negative number is done, both end up positive...
int main(int argc, char* argv[])
{
    FILE * testFile;
    testFile = fopen(argv[1], "r");
    loadFile(testFile, memory);
    //cout << "Loaded the file." << endl;
    /*for (int j = 100; j < 110; j++)
        printMemoryLocation(j, memory);
    cout << endl << endl;
    for(int i = 0; i < 16; i++)
    {
        printMemoryLocation(i, memory);
    }*/
    //cout << endl << endl; // James' loading into memory code.    
    setMemoryInt(15, 95, memory);
    system("clear");
    printRegisters(memory);
    cout << endl;
    printProgramCounterMemory(memory);
    cout << endl;
    cout << "Overflow Flag: " << OVERFLOW_FLAG << endl;
    waitForEnter();
    runProgram();
    
    
    
	/*setMemoryInt(0, 30000, memory);
	setMemoryInt(1,1, memory);
	set(0, 42, memory);
    setH(0, -42, memory);
    incIZ(2, 15, 1, memory);
	printMemoryLocation(0, memory);
	printMemoryLocation(1, memory);
	printMemoryLocation(2, memory);
	cout << "Result of subI: " << boolNtoInt(WORD_SIZE, memory[2]) << endl;*/

    /*setMemoryInt(0, 0, memory);
    setMemoryInt(1, 1, memory);
    setMemoryInt(2, -1, memory);
    setMemoryInt(3, 5, memory);*/
    
    /*moveZ(4, 3, 1, memory);
    moveX(5, 3, 0, memory);
    moveP(6, 3, 2, memory);
    moveN(7, 3, 1, memory);*/
    /*for(int i = 4; i < 8; i++)
    {
        printMemoryLocation(i, memory);
    }*/
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