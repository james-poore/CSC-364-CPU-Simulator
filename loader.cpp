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
#include "helper.h"

#define MAX_LINE_LENGTH 500

void loadValue(bool *instruction, int counter, int a, int b, int c, int d) {
    int counter2 = ((counter * 4) -1);
    instruction[counter2] = a;
    instruction[counter2 - 1] = b;
    instruction[counter2 - 2] = c;
    instruction[counter2 - 3] = d;
}



void processLine(char *line) {
    
    int doneFlag = 0;
    
    char* expandedToken = NULL;
    
    bool instruction[16];
    
    startToken(line);
    aToken answer;
    
    answer = getNextToken();
    
    int counter = 4;
    
    expandedToken = strdup(answer.start);
    
    while (!doneFlag) {
        
        switch (answer.type) {
            
            case aToken::MEM_LOCATION:
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
                
            case aToken::DATA:
                
            default:
                //Invalid instruction...will handle error later.
                break;
        }
    
        counter--;
        free(expandedToken);
    
    }
}

int loadFile(FILE *file) {
    
    char line[MAX_LINE_LENGTH + 1];
    
    while (fgets(line, MAX_LINE_LENGTH + 1, file) != NULL)
        processLine(line);  
    
}

