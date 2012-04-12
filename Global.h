/*
 * Global.h
 * Global constants.
 * Author: Dillon Welch
 */ 

#ifndef CONSTS_H_INCLUDED // include guard, ensures that the header file is only included once in each compilation unit. 
#define CONSTS_H_INCLUDED	

extern int NEGATIVE_FLAG;
extern int OVERFLOW_FLAG;

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

static const int TOTAL_MEM_SIZE = 65536; // 2^16;
static const int TOTAL_VAL_SIZE = TOTAL_MEM_SIZE / 2; // 2^15, max size a number can be (discounting sign bit).
static const int WORD_SIZE = 16;

#endif // include guard