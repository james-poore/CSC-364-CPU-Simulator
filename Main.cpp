
#include <iostream>
#include <math.h>
#include <stdio.h>

#include "CPUFunctions.h"
#include "Global.h"
#include "Helper.h"
#include "loader.h"

using namespace std;

bool memory [TOTAL_MEM_SIZE] [WORD_SIZE]; 

int NEGATIVE_FLAG = 0;
int OVERFLOW_FLAG = 0;

/* NOTE: Functions go from most significant bit to least significant bit. */

/*
 static const int OP_MOVE  =  0;
 static const int OP_NOT   =  1;
 static const int OP_AND   =  2;
 static const int OP_OR    =  3;
 static const int OP_ADD   =  4;
 static const int OP_SUB   =  5;
 static const int OP_ADDI  =  6;
 static const int OP_SUBI  =  7;
 static const int OP_SET   =  8;
 static const int OP_SETH  =  9;
 static const int OP_INCIZ = 10;
 static const int OP_DECIN = 11;
 static const int OP_MOVEZ = 12;
 static const int OP_MOVEX = 13;
 static const int OP_MOVEP = 14;
 static const int OP_MOVEN = 15;
 */

void runProgram()
{
    while(true)
    {
        int programLocation = boolNtoInt(WORD_SIZE, memory[PROGRAM_COUNTER]);
        int endOfProgram = 0;
        //cout << "Program Location is: " << programLocation << endl;
        // memory size, word size, quartet, memory
        int opCode = boolQuartetToInt(WORD_SIZE, 4, 4, memory[programLocation]);
        //cout << "Op code is: " << opCode << endl;
        switch(opCode)
        {
            case OP_MOVE:
            {
                int regD = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[programLocation]);
                int regA = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 2, memory[programLocation]);
                move(regD, regA, memory);
                
                // MOVE R15, R15
                // If this is the command, this signifies the end of program and it should loop at this point.
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
        
        //cout << "PC at end of loop: " << boolNtoInt(WORD_SIZE, memory[PROGRAM_COUNTER]) << endl;
        //cout << "EndOfProgram: " << endOfProgram << endl;
        // If the program counter hasn't been changed by an operation, increase it by one.
        if(programLocation == boolNtoInt(WORD_SIZE, memory[PROGRAM_COUNTER]) && endOfProgram == 0)
        {
            programLocation += 1;
            setMemoryInt(PROGRAM_COUNTER, programLocation, memory);
        }
        system("clear");
        printRegisters(memory);
        cout << endl;
        printProgramCounterMemory(memory);
        // Wait for the user to press enter before moving on to the next instruction.
        waitForEnter();
    }
}

// Error checking on PC, R6, R13, R14
int main(int argc, char* argv[])
{
    /*int code = atoi(argv[1]);
    setMemoryInt(1, 0, memory);
    setMemoryInt(2, 15, memory);
    setMemoryInt(3, -1, memory);
    intToBoolQuartet(code, WORD_SIZE / 4, 4, memory[16]);
    intToBoolQuartet(1, WORD_SIZE / 4, 3, memory[16]);
    intToBoolQuartet(2, WORD_SIZE / 4, 2, memory[16]);
    intToBoolQuartet(3, WORD_SIZE / 4, 1, memory[16]);
    //printMemoryLocation(0, memory);
    //printMemoryLocation(1, memory);
    //printMemoryLocation(2, memory);
    //printMemoryLocation(3, memory);
     
    setMemoryInt(15, 16, memory); // Sets PC
    system("clear");
    printRegisters(memory);
    cout << endl;
    printProgramCounterMemory(memory);
    waitForEnter();
    runProgram();
    printMemoryLocation(0, memory);
    printMemoryLocation(1, memory);
    printMemoryLocation(2, memory);
    printMemoryLocation(3, memory);
    
    setMemoryInt(15, 40000, memory);
    printMemoryLocation(15, memory);
    int test = boolNtoInt(WORD_SIZE, memory[15]);
    cout << test << endl;
    */
    
    FILE * testFile;
    testFile = fopen("ASM.txt", "r");
    loadFile(testFile, memory);
    //cout << "Loaded the file." << endl;
    for (int j = 100; j < 110; j++)
        printMemoryLocation(j, memory);
    cout << endl << endl;
    for(int i = 0; i < 16; i++)
    {
        printMemoryLocation(i, memory);
    }
    //cout << endl << endl; // James' loading into memory code.    
    
    //system("clear");
    printRegisters(memory);
    cout << endl;
    printProgramCounterMemory(memory);
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