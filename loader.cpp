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

int memLocation = 0;

void loadValue(bool *instruction, int counter, int a, int b, int c, int d) {
    
    int counter2 = ((counter * 4) -1);
    instruction[counter2] = a;
    instruction[counter2 - 1] = b;
    instruction[counter2 - 2] = c;
    instruction[counter2 - 3] = d;
}

void processLine(char *line, bool memory[TOTAL_MEM_SIZE] [WORD_SIZE]) {
    
    int doneFlag = 0;
    
    char* expandedToken = NULL;
    
    bool instruction[WORD_SIZE];
    
    startToken(line);
    aToken answer;
    
    answer = getNextToken();
    
    int counter = 4;
    
    while (!doneFlag) {
        
        expandedToken = strdup(answer.start);
        
        switch (answer.type) {
            
            case aToken::MEM_LOCATION:
                //set memLocation
                break;
                
            case aToken::EOL:
                doneFlag = 1;
                
            case aToken::OP_CODE:
                if (strcasecmp(expandedToken, "MOVE") == 0) {
                    loadValue(instruction, counter, 0, 0, 0, 0);
                    break;
                }
                
                else if (strcasecmp(expandedToken, "NOT") == 0) {
                    loadValue(instruction, counter, 0, 0, 0, 1);
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
                    break;
                }
                
                else if (strcasecmp(expandedToken, "SETH") == 0) {
                    loadValue(instruction, counter, 1, 0, 0, 1);
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
                    //Invalid OP CODE... will handle error later.
                }
                
            case aToken::REGISTER:
                while (*currTokPos != ',') {
                    
                }
                
            case aToken::DATA:
                if (((int) *expandedToken > 15) && counter == 2) {
                    counter = 1;
                    intToBoolQuartet((int) *expandedToken, 8, counter, instruction);
                    doneFlag = 1;
                    break;
                }
                
                else if (((int) *expandedToken > 15) && counter != 2) {
                    //Passed 8-bit data in the 1st or 3rd quartet which is invalid...will handle error later.
                    break;
                }
                
                else {
                    intToBoolQuartet((int) *expandedToken, 4, counter, instruction);
                    break;
                }
                
            default:
                //Invalid instruction...will handle error later.
                break;
        }
    
        
        counter--;
        free(expandedToken);
    
    }
    
    setMemoryBoolArray(memLocation, instruction, memory);
    memLocation++;
    
}

int loadFile(FILE *file, bool memory[TOTAL_MEM_SIZE] [WORD_SIZE]) {
    
    char line[MAX_LINE_LENGTH + 1];
    
    while (fgets(line, MAX_LINE_LENGTH + 1, file) != NULL) {
        
        processLine(line, memory);  
        
    }
}

