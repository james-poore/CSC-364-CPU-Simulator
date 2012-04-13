//
//  tokenizer.h
//  CPU Simulator Loader
//
//  Created by James Poore on 4/11/12.
//  Copyright (c) 2012 James Poore. All rights reserved.
//

#ifndef CPU_Simulator_Loader_tokenizer_h
#define CPU_Simulator_Loader_tokenizer_h

/***
 * A token: storing start of the token string
 *  and the type of the token.
 ***/
typedef struct
{
    char *start;
    enum { OP_CODE, EOL, MEM_LOCATION, DATA, REGISTER } type;
} aToken;

static char* currTokPos;

/***
 * startToken:
 *    Register the start of a new line to tokenize.
 *    The previous line (if still present) gets ignored.
 *    An error is printed if the line is NULL (but treated as an empty line)
 *
 *    line: A pointer to the start of the null-terminated string for this line.
 *          The string gets stored in a local copy so the string line can change
 *          without affecting the tokenizer.  Also, line is not altered in any way.
 ***/
void startToken(char *line);

/***
 * getNextToken:
 *    Return the next token in the current line as a struct (aToken).
 *    String tokens are handled as described above.
 *
 *    Returns aToken.type of:
 *      EOL: If end-of-line reached
 *      ERROR: If some error occurred (namely, unterminated string)
 *      BASIC: If token is a regular token
 *      SINGLE_QUOTE: If token is 'single quoted string'
 *      DOUBLE_QUOTE: If token is "double quoted string"
 *      PIPE: If token is '|'
 *      SEMICOLON: If token is ';'
 *      INPUT: If token is '<'
 *      OUTPUT: If token is '>'
 *      ERR_REDIR: If token is '>&'
 *
 *    Returns aToken.start:
 *      If not EOL or ERROR, then start points to start of the string
 *      (and string is null-terminated)
 *
 **********************************************
 *    WARNING: This start string is ONLY temporary.  A subsequent call to
 *      getNextToken/startToken will possibly erase it.  So caller MUST
 *      make a local copy if further use is needed!
 **********************************************
 ***/
aToken getNextToken();

#endif  /* __TOKENIZER_H */
