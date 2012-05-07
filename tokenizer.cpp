//
//  tokenizer.cpp
//  CPU Simulator Loader
//
//  Created by James Poore on 4/11/12.
//  Copyright (c) 2012 James Poore. All rights reserved.
//



#include "tokenizer.h"
//#include "loader.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

static char* tokLine = NULL;

void startToken(char* line)
{
    if (line == NULL)
    {
        // Hey, no line even passed
        fprintf(stderr, "ERROR: Null line given.  Using empty line.\n");
        line = "";
    }
    
    // Make a copy of the line (so we have it safely)
    
    // Reallocated space
    if ((tokLine = (char *)realloc(tokLine, strlen(line)+1)) == NULL)
    {
        // Not enough memory???
        fprintf(stderr, "ERROR: Insufficient memory to tokenize!  Using empty space.\n");
        tokLine = NULL;
        currTokPos = NULL;
        return;
    }
    
    strcpy(tokLine, line);
    
    // Start the token pointing to the first position
    currTokPos = tokLine;
}

aToken getNextToken()
{
    bool hexBinFlag = false;
    
    aToken res;
    if (*currTokPos == NULL || *currTokPos == '\n')
    {
        // End of line reached.  (Nothing left to parse)
        res.type = aToken::EOL;
        res.start = currTokPos;
        return res;
    }
    
    // Find the first non-white space
    while (*currTokPos == (' ') || *currTokPos == '\t')
        currTokPos++;
    
    switch (*currTokPos)
    {
        case '#': // The # tells the loader to use this line to find the starting postion
                  // for loading the program into memory
            res.start = (currTokPos+=1);
            res.type = aToken::MEM_LOCATION;
            return res;
            
        case '\n':
            // We have reached the end of the line...
            res.type = aToken::EOL;
            res.start = currTokPos;
            return res;
        
        case '/':
            //We have found a comment line, ignore everthing else on that line
            if (*(currTokPos + 1) == '/') {
                res.start = currTokPos;
                res.type = aToken::COMMENT;
            }
            else {
                printf("Would print an actual error here, but C apparently WON'T let you do anything you want!!!\nComments require '//'\n");
                exit(EXIT_FAILURE);
                //printError("'/' character not recognized.");
            }
            //res.start = currTokPos;
            //res.type = aToken::COMMENT;
            return res;
            
        case '0':
            if (*(currTokPos + 1) == 'b') {
                res.type = aToken::BINARY;
                hexBinFlag = true;
                currTokPos += 2;
            }
            else if (*(currTokPos + 1) == 'x') {
                res.type = aToken::HEX;
                hexBinFlag = true;
                currTokPos += 2;
            }
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            if (!hexBinFlag) {
                res.type = aToken::DATA;
            }
            
            res.start = currTokPos;
            
            while (*currTokPos != ' ' && *currTokPos != '\n' && *currTokPos != '\t')
                currTokPos++;
            
            if (*currTokPos != '\n')
            {
                // Haven't quite reached the end (mark it - and advance currTokPos)
                *(currTokPos++) = '\0';
            }
            
            return res;
            
        case 'R':
            res.start = currTokPos += 1;
            res.type = aToken::REGISTER;
            
            while (*currTokPos != ' ' && *currTokPos != '\n' && *currTokPos != '\t')
                currTokPos++;
            
            if (*currTokPos != '\n')
            {
                // Haven't quite reached the end (mark it - and advance currTokPos)
                *(currTokPos++) = '\0';
            }
            
            return res;
            
        default:
            // This is an OP CODE
                res.start = currTokPos;
                res.type = aToken::OP_CODE;
            
            // Find end of token (using regular delimiters)
            while (*currTokPos != ' ' && *currTokPos != '\n' && *currTokPos != '\t')
                currTokPos++;
            
            if (*currTokPos != '\n')
            {
                // Haven't quite reached the end (mark it - and advance currTokPos)
                *(currTokPos++) = '\0';
            }
            
            return res;
    }
    
    
    
    // Return the start of this token
    //return res;
}

