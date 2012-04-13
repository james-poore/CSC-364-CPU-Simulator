//
//  tokenizer.cpp
//  CPU Simulator Loader
//
//  Created by James Poore on 4/11/12.
//  Copyright (c) 2012 James Poore. All rights reserved.
//

//THIS IS A TEST

//THIS IS ANOTHER TEST


#include "tokenizer.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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
    aToken res;
    if (currTokPos == NULL || *currTokPos == '\n')
    {
        // End of line reached.  (Nothing left to parse)
        res.type = aToken::EOL;
        res.start = NULL;
        return res;
    }
    
    // Find the first non-white space
    while (*currTokPos == ' ')
        currTokPos++;
    
    switch (*currTokPos)
    {
        case '#': // The # tells the loader to use this line to find the starting postion
                  // for loading the program into memory
            res.start = currTokPos;
            res.type = aToken::MEM_LOCATION;
            return res;
            
        case '\n':
            // We have reached the end of the line...
            res.type = aToken::EOL;
            res.start = NULL;
            return res;
        
        case '/':
            //We have found a comment line, ignore everthing else on that line
            res.start = NULL;
            res.type = aToken::EOL;
            return res;
            
        default:
            //Check to see if this token is a number
            if (*currTokPos == 0 || 1 || 2 || 3 || 4 || 5 || 6 || 7 || 8 || 9 ) {
                res.start = currTokPos;
                res.type = aToken::NUMBER;
            }
            
            if (*currTokPos == 'R') {
                res.start = currTokPos++;
                res.type = aToken::REGISTER;
            }
            
            // This is start of a basic string of letters
            else {
                res.start = currTokPos;
                res.type = aToken::OP_CODE;
            }
            
            // Find end of token (using regular delimiters)
            while (*currTokPos != ' ' &&
                   *currTokPos != '\n')
                currTokPos++;
    }
    
    if (*currTokPos != '\n')
    {
        // Haven't quite reached the end (mark it - and advance currTokPos)
        *(currTokPos++) = '\n';
    }
    
    // Return the start of this token
    return res;
}

