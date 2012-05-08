/*
 * Global.h
 * Global constants.
 * Author: Dillon Welch
 */ 

#ifndef CONSTS_H_INCLUDED // Include guard, ensures that the header file is only included once in each compilation unit. 
#define CONSTS_H_INCLUDED

using namespace std;

extern int PROG_LOC;

extern int NEGATIVE_FLAG;
extern int OVERFLOW_FLAG;
extern int LAST_MINUTE_FIX_FLAG; 

extern string currentInstructionArray[5]; // The English version of the current instruction, the 2 previous, and the 2 next instructions.

// Values of the op codes.
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

static const int INPUT_REGISTER     = 6;     // Memory location of the input register.
static const int OUTPUT_REGISTER_1 = 13; // Memory location of the first output register (read/write flag, keyboard..).
static const int OUTPUT_REGISTER_2 = 14; // Memory location of the second output register (memory address).
static const int PROGRAM_COUNTER   = 15;   // Memory location of the program counter.

static const int TOTAL_MEM_SIZE = 65536; // 2^16;
static const int TOTAL_VAL_SIZE = TOTAL_MEM_SIZE / 2; // 2^15, max size a number can be (discounting sign bit).
static const int WORD_SIZE = 16; // Size of a memory location.

#endif // Include guard