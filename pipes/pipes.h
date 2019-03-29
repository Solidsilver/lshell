#ifndef PIPES_H
#define PIPES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "../tokenize/makeArgs.h"
#include "../utils/myUtils.h"
#include "../process/process.h"

int containsPipe(char *s);
char ** parsePrePipe(char **s);
char * parsePostPipe(char *s, int * postCount);
void pipeIt(char *** cmds, int count);
char *** parsePipe(char * s, int pipeCount);
void freePipes(char ***pipes, int len);


#endif 
