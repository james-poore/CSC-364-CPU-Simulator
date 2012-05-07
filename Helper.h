/*
 * Helper.h
 * Helper functions for the CPU simulator
 * Author: Dillon Welch
 */ 

/* NOTE: Functions go from most significant bit to least significant bit. */

#include "Global.h"

// Functions that return an int.
int binaryToInt(string binaryString, bool memory[TOTAL_MEM_SIZE][WORD_SIZE]);
int boolNtoInt(int size, bool word[]);
int boolQuartetToInt(int size, int lengthOfBinaryNumber, int quartetNum, bool word[]);

int getProgramCounter(bool memory[TOTAL_MEM_SIZE][WORD_SIZE]);

int hexToInt(string hexString, bool memory[TOTAL_MEM_SIZE][WORD_SIZE]);

int overflowTest(int size, bool word[]);

string binaryToString(string binaryString, bool memory[TOTAL_MEM_SIZE][WORD_SIZE]);

string hexToString(string hexString, bool memory[TOTAL_MEM_SIZE][WORD_SIZE]);

// Functions that return nothing.
void bitwiseAdd(int sizeA, bool wordA[], int sizeB, bool wordB[], bool result[]);
void bitwiseAddImm(int sizeA, bool wordA[], int addImm, bool result[]);
void bitwiseNot(int size, bool word[], bool result[]);

void calculateInstructionStrings(bool memory[TOTAL_MEM_SIZE][WORD_SIZE]);
void copyBooleanArray(bool src[], bool dest[]);
void copyBooleanArrayQuartet(bool src[], bool dest[], int size, int quartetNum);

void intToBoolN(int number, int size, bool word[]);
void intToBoolQuartet(int number, int size, int quartetNum, bool word[]);

void printBoolArray(int size, bool word[]);
void printMemoryLocation(int index, bool memory[TOTAL_MEM_SIZE][WORD_SIZE]);
void printProgramCounterMemory(bool memory[TOTAL_MEM_SIZE][WORD_SIZE]);
void printRegisters(bool memory[TOTAL_MEM_SIZE][WORD_SIZE]);
void printUserDisplay(bool memory[TOTAL_MEM_SIZE][WORD_SIZE]);

void setMemoryBoolArray(int location, bool number[WORD_SIZE], bool memory[TOTAL_MEM_SIZE][WORD_SIZE]);
void setMemoryInt(int location, int number, bool memory[TOTAL_MEM_SIZE][WORD_SIZE]);
void switchSign(int size, bool number[]);

void waitForEnter();

void zeroBoolArray(int size, bool word[]);