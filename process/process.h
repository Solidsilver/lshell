#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "../utils/myUtils.h"
#include "../history/history.h"


void run(char ** argv, int wait, LinkedList * hist, LinkedList * alias);
void runIt(char ** argv);
int isBackground(char * cmd);
int isBuiltin(char * cmd);

int runBuiltin(char ** argv, LinkedList * hist, LinkedList * alias);



#endif
