//
//  loader.cpp
//  CPU Simulator Loader
//
//  Created by James Poore on 4/11/12.
//  Copyright (c) 2012 James Poore. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include "tokenizer.h"
#include "Helper.h"
#include "Global.h"

#define MAX_LINE_LENGTH 500
#define PC 15

int memLocation = 0;
int lineNumber = 1;

void loadValue(bool instruction[WORD_SIZE], int counter, int a, int b, int c, int d) {
    
    int counter2 = ((counter * 4) - 1);
    instruction[counter2] = a;
    instruction[counter2 - 1] = b;
    instruction[counter2 - 2] = c;
    instruction[counter2 - 3] = d;
}

void printError(char errorMessage[100]) {
    std::cout << "Line " << lineNumber << " : " << errorMessage << endl;
    exit(EXIT_FAILURE);
}

void processLine(char *line, bool memory[TOTAL_MEM_SIZE] [WORD_SIZE]) {
    
    bool doneFlag = 0;
    
    char *expandedToken = NULL;
    char registerNum[WORD_SIZE];
    char memLoc1[WORD_SIZE];
    char memLoc2[WORD_SIZE];
    
    bool tempMemLoc[WORD_SIZE];
    bool programCounter[WORD_SIZE];
    bool boolean[WORD_SIZE];
    bool instruction[WORD_SIZE];
    
    zeroBoolArray(WORD_SIZE, instruction);
    
    startToken(line);
    aToken answer;
    
    int counter = 4;
    int regNum = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    bool setFlag = 0;
    bool argFlag = 0;
    
    while ((!doneFlag)) {
        
        if (memLocation > 65535) {
            printError("Program exceeds bounds of memory");
            exit(EXIT_FAILURE);
        }
        
        doneFlag = 0;
        
        answer = getNextToken();
        
        i = 0;
        j = 0;
        k = 0;
        
        expandedToken = strdup(answer.start);
        
        switch (answer.type) {
            
            case aToken::MEM_LOCATION:
                while (expandedToken[j] != '=') {
                    memLoc1[j] = expandedToken[j];
                    j++;
                }
                
                memLoc1[j] = '\0';
                
                if ( atoi(memLoc1) > 65535 ) {
                    printError("Expected value less than 65535 before '=' ");
                    exit(EXIT_FAILURE);
                }
                
                j++;
                
                while (expandedToken[j] != '\n') {
                    memLoc2[k] = expandedToken[j];
                    j++;
                    k++;
                }
                
                memLoc2[k] = '\0';
                
                if ( (atoi(memLoc2) > 32767)  || (atoi(memLoc2) < -32768)  ) {
                    printError("Expected value between -32768 and 32767 before ';' ");
                    exit(EXIT_FAILURE);
                }
                
                if (strcasecmp(memLoc2, "ASM") == 0) {
                    memLocation = atoi(memLoc1);
                    setMemoryInt(PC, memLocation, memory);
                    doneFlag = true;
                    break;
                }
                
                else if(strncasecmp(memLoc2, "0b") == 0) {
                    memLoc2 = memLoc2.substr(2, memLoc2.size() - 2);
                    intToBoolQuartet(binaryToInt(memLoc2, memory), WORD_SIZE, 1, tempMemLoc);
                    setMemoryBoolArray(atoi(memLoc1), tempMemLoc, memory);
                }
                
                else if(strncasecmp(memLoc2, "0x") == 0) {
                    memLoc2 = memLoc2.substr(2, memLoc2.size() - 2);
                    intToBoolQuartet(hexToInt(memLoc2, memory), WORD_SIZE, 1, tempMemLoc);
                    setMemoryBoolArray(atoi(memLoc1), tempMemLoc, memory);
                }
                
                else {
                    intToBoolQuartet(atoi(memLoc2), WORD_SIZE, 1, tempMemLoc);
                    setMemoryBoolArray(atoi(memLoc1), tempMemLoc, memory);
                    doneFlag = true;
                    break;
                }
                
            case aToken::COMMENT:
            case aToken::EOL:
                doneFlag = 1;
                break;
                
            case aToken::OP_CODE:
                
                
                if (strcasecmp(expandedToken, "MOVE") == 0) {
                    loadValue(instruction, counter, 0, 0, 0, 0);
                    argFlag = 1;
                    break;
                }
                
                else if (strcasecmp(expandedToken, "NOT") == 0) {
                    loadValue(instruction, counter, 0, 0, 0, 1);
                    argFlag = 1;
                    break;
                }
                
                else if (strcasecmp(expandedToken, "AND") == 0) {
                    loadValue(instruction, counter, 0, 0, 1, 0);
                    break;
                }
                
                else if (strcasecmp(expandedToken, "OR") == 0) {
                    loadValue(instruction, counter, 0, 0, 1, 1);
                    break;
                }
                
                else if (strcasecmp(expandedToken, "ADD") == 0) {
                    loadValue(instruction, counter, 0, 1, 0, 0);
                    break;
                }
                
                else if (strcasecmp(expandedToken, "SUB") == 0) {
                    loadValue(instruction, counter, 0, 1, 0, 1);
                    break;
                }
                
                else if (strcasecmp(expandedToken, "ADDI") == 0) {
                    loadValue(instruction, counter, 0, 1, 1, 0);
                    break;
                }
                
                else if (strcasecmp(expandedToken, "SUBI") == 0) {
                    loadValue(instruction, counter, 0, 1, 1, 1);
                    break;
                }
                
                else if (strcasecmp(expandedToken, "SET") == 0) {
                    loadValue(instruction, counter, 1, 0, 0, 0);
                    argFlag = 1;
                    setFlag = true;
                    break;
                }
                
                else if (strcasecmp(expandedToken, "SETH") == 0) {
                    loadValue(instruction, counter, 1, 0, 0, 1);
                    argFlag = 1;
                    setFlag = true;
                    break;
                }
                
                else if (strcasecmp(expandedToken, "INCIZ") == 0) {
                    loadValue(instruction, counter, 1, 0, 1, 0);
                    break;
                }
                
                else if (strcasecmp(expandedToken, "DECIN") == 0) {
                    loadValue(instruction, counter, 1, 0, 1, 1);
                    break;
                }
                
                else if (strcasecmp(expandedToken, "MOVEZ") == 0) {
                    loadValue(instruction, counter, 1, 1, 0, 0);
                    break;
                }
                
                else if (strcasecmp(expandedToken, "MOVEX") == 0) {
                    loadValue(instruction, counter, 1, 1, 0, 1);
                    break;
                }
                
                else if (strcasecmp(expandedToken, "MOVEP") == 0) {
                    loadValue(instruction, counter, 1, 1, 1, 0);
                    break;
                }
                
                else if (strcasecmp(expandedToken, "MOVEN") == 0) {
                    loadValue(instruction, counter, 1, 1, 1, 1);
                    break;
                }
                
                else {
                    printError("Invalid op-code.");
                    exit(EXIT_FAILURE);
                }
                
            case aToken::REGISTER:
                while ((expandedToken[i] != ',') && (expandedToken[i] != '\n') && (expandedToken[i] != '\0')) {
                    registerNum[i] = expandedToken[i];
                    i++;
                }
                registerNum[i] = '\0';
                
                regNum = atoi(registerNum);
                
                if (regNum > 15 || regNum < 0) {
                    printError("Invalid register number.");
                    exit(EXIT_FAILURE);
                }
                
                else if (regNum == 6 && counter == 3) {
                    printError("Register 6 is the input register. Write functionality not permitted.");
                    exit(EXIT_FAILURE);
                }
                    
                
                intToBoolQuartet(regNum, 4, counter, instruction);
                break;
                
            case aToken::DATA:
                if (setFlag == true && counter == 2) {
                    intToBoolQuartet(atoi(expandedToken), 8, 1, instruction);
                    break;
                }
                
                else if (setFlag == true && counter != 2) {
                    printError("8-bit data given, 4-bit data expected.");
                    exit(EXIT_FAILURE);
                }
                
                else {
                    intToBoolQuartet(atoi(expandedToken), 4, counter, instruction);
                    break;
                }
                
            case aToken::BINARY:
                if (setFlag == true && counter == 2) {
                    intToBoolQuartet(binaryToInt(expandedToken, memory), 8, 1, instruction);
                    break;
                }
                
                else if (setFlag == true && counter != 2) {
                    printError("8-bit data given, 4-bit data expected.");
                    exit(EXIT_FAILURE);
                }
                
                else {
                    intToBoolQuartet(binaryToInt(expandedToken, memory), 4, counter, instruction);
                    break;
                }
                
            case aToken::HEX:
                if (setFlag == true && counter == 2) {
                    intToBoolQuartet(hexToInt(expandedToken, memory), 8, 1, instruction);
                    break;
                }
                
                else if (setFlag == true && counter != 2) {
                    printError("8-bit data given, 4-bit data expected.");
                    exit(EXIT_FAILURE);
                }
                
                else {
                    intToBoolQuartet(hexToInt(expandedToken, memory), 4, counter, instruction);
                    break;
                }
                
            default:
                printError("Invalid instruction.");
                exit(EXIT_FAILURE);
        }
    
        
        counter--;
        if (expandedToken != NULL) {
            free(expandedToken);
        }
    
    }

    if (counter == -1) {
        setMemoryBoolArray(memLocation, instruction, memory);
        memLocation++;
    }
    else if ( (argFlag == 1) && (counter == 0)) {
        setMemoryBoolArray(memLocation, instruction, memory);
        memLocation++;
    }
    
}

int loadFile(FILE *file, bool memory[TOTAL_MEM_SIZE] [WORD_SIZE]) {
    
    char line[MAX_LINE_LENGTH + 1];
    
    while (fgets(line, MAX_LINE_LENGTH + 1, file) != NULL) {
        
        processLine(line, memory);
        lineNumber++;
        
    }
    
    return 0;
}

