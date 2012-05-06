//
//  loader.h
//  CPU Simulator Loader
//
//  Created by James Poore on 4/12/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef CPU_Simulator_Loader_loader_h
#define CPU_Simulator_Loader_loader_h

void printError(char errorMessage[100]);
int loadFile(FILE *file, bool memory[TOTAL_MEM_SIZE] [WORD_SIZE]);

#endif
