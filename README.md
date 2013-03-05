CSC-364-CPU-Simulator
=====================

CPU Simulator

There is a makefile included to help in compiling the program.

To run the program, type in ./CPU-Simulator FILE_NAME, where FILE_NAME is the name of the file with the assembly code.

Some examples of test programs are given in the directory, namely "Div.txt" and "Mult.txt".

There are a total of 2^16 or 65536 memory slots.

A number can have at most 2^15 bits, with the most significan bit being the sign bit.

The input register is register 6.

The output registers are registers 13 and 14.

The program counter is 15.

To set a register to a value at the beginning of your program, do #NUM=VAL, where NUM is the number of the register (0-15) and VAL is the value.

To set the program counter and loading point of your program, do #VAL=ASM, where VAL is the position of the program counter. ASM needs to be typed exactly as is.

To comment your code, use //insert_comment_here

The format of the various instructions are (spaces are important, replace A, B, D with register values, replace # with a value):
MOVE RD, RA
-Moves the value in register A into register D.

NOT RD, RA
-Performs a bitwise NOT on register A and saves the result into register D.

AND RD, RA, RB
-Performs a bitwise AND on register A and register B and saves the result into register D.

OR RD, RA, RB
-Performs a bitwise OR on register A and register B and saves the result into register D.

ADD RD, RA, RB
-Adds the values in register A and register B and saves the result into register D.

SUB RD, RA, RB
-Subtracts the values in register A and register B and saves the result into register D.

ADDI RD, RA, #
-Adds RA and # (4 bit number) and saves the result into register D.

SUBI RD, RA, #
-Subtracts RA and # (4 bit number) and saves the result into register D.

SET RD, #
-Sets RD to be 8 0's followed by # (8 bit number).
-For example, SET R5, 42 would result in R5 being 0000 0000 0010 1010.

SETH RD, #
-Sets the first 8 bits of RD to be # (8 bit number) followed by the previous 8 bits of RD.
-For example, if R5 was 1100 1010 0010 1010, after SETH R5, 42 it would become 0010 1010 0010 1010.

INCIZ RD, #, RB
-Adds RD and # (4 bit number) and saves the result into RD only if RB == 0(the value in RB is 0).

DECIN RD, #, RB
-Subtracts RD and # (4 bit number) and saves the result into RD only if RB15 == 1 (the value in RB is negative).

MOVEZ RD, RA, RB
-Sets RD to the value of RA if RB == 0 (the value in RB is 0).

MOVEX RD, RA, RB
-Sets RD to the value of RA if RB != 0 (the value in RB is not zero).

MOVEP RD, RA, RB
-Sets RD to the value of RA if RB15 == 0 (the value in RB is positive).

MVOEN RD, RA, RB
-Sets RD to the value of RA if RB15 == 1 (the value in RB is negative).
