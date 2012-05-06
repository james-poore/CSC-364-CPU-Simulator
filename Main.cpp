
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

/*
 TODO:
 Program counter isn't being set in loader
 Other misc. loader bugs.
 */

void runProgram()
{
    while(true)
    {
        int programLocation = getProgramCounter(memory);//boolNtoInt(WORD_SIZE, memory[PROGRAM_COUNTER]); // Get the current instruction location.
        PROG_LOC = programLocation;
        int endOfProgram = 0; // Whether or not this instruction is MOVE R15, R15.
        int opCode = boolQuartetToInt(WORD_SIZE, 4, 4, memory[programLocation]); // Get the op code.
        int registerCheck = boolQuartetToInt(WORD_SIZE, WORD_SIZE / 4, 3, memory[programLocation]);
        if(registerCheck == INPUT_REGISTER) // If RD is INPUT_REGISTER, then the program is trying to write to the input register which is illegal.
        {
            cerr << "Register " << INPUT_REGISTER << " is the input register, and you can not write to it." << endl;
            exit(EXIT_FAILURE);
        }
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
        if(programLocation == getProgramCounter(memory) && endOfProgram == 0 && programLocation < TOTAL_MEM_SIZE)
        {
            programLocation += 1;
            setMemoryInt(PROGRAM_COUNTER, programLocation, memory);
        }
        
        
        printUserDisplay(memory); // Prints everything that the user needs to see to the screen.
        waitForEnter(); // Wait for the user to press enter before moving on to the next instruction.
    }
}

int main(int argc, char* argv[])
{
    FILE * testFile; // Load in the file given by argv[1] into memory.
    testFile = fopen(argv[1], "r");
    loadFile(testFile, memory);
    

    //setMemoryInt(15, 95, memory); /*** loadFile doesn't actually set PC just yet, so manually set it. ***/
    printUserDisplay(memory); // Prints everything that the user needs to see to the screen.
    waitForEnter(); // Wait for the user to press enter before moving on to the next instruction.
    runProgram(); // Execute the program.
}