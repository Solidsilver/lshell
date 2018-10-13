#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "../utils/myUtils.h"

void forkIt(char ** argv, int wait);
void runIt(char ** argv);
int isBackground(char * cmd);



#endif
