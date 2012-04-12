/*
 * CPUFunctions.h
 * Header file for the 16 CPU functions.
 * Author: Dillon Welch
 */ 

/* NOTE: Functions go from most significant bit to least significant bit. */

#include "Global.h"

void move(int regD, int regA, bool memory[TOTAL_MEM_SIZE][WORD_SIZE]);
void not_op(int regD, int regA, bool memory[TOTAL_MEM_SIZE][WORD_SIZE]);
void and_op(int regD, int regA, int regB, bool memory[TOTAL_MEM_SIZE][WORD_SIZE]);
void or_op(int regD, int regA, int regB, bool memory[TOTAL_MEM_SIZE][WORD_SIZE]);
void add(int regD, int regA, int regB, bool memory[TOTAL_MEM_SIZE][WORD_SIZE]);
void sub(int regD, int regA, int regB, bool memory[TOTAL_MEM_SIZE][WORD_SIZE]);
void addI(int regD, int regA, int data4, bool memory[TOTAL_MEM_SIZE][WORD_SIZE]);
void subI(int regD, int regA, int data4, bool memory[TOTAL_MEM_SIZE][WORD_SIZE]);
void set(int regD, int data8, bool memory[TOTAL_MEM_SIZE][WORD_SIZE]);
void setH(int regD, int data8, bool memory[TOTAL_MEM_SIZE][WORD_SIZE]);
void incIZ(int regD, int data4, int regB, bool memory[TOTAL_MEM_SIZE][WORD_SIZE]);
void decIN(int regD, int data4, int regB, bool memory[TOTAL_MEM_SIZE][WORD_SIZE]);
void moveZ(int regD, int regA, int regB, bool memory[TOTAL_MEM_SIZE][WORD_SIZE]);
void moveX(int regD, int regA, int regB, bool memory[TOTAL_MEM_SIZE][WORD_SIZE]);
void moveP(int regD, int regA, int regB, bool memory[TOTAL_MEM_SIZE][WORD_SIZE]);
void moveN(int regD, int regA, int regB, bool memory[TOTAL_MEM_SIZE][WORD_SIZE]);