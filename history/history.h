#ifndef HISTORY_H
#define HISTORY_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include "../linkedlist/linkedList.h"
#include "../linkedlist/listUtils.h"
#include "../utils/myUtils.h"
#include "../utils/fileUtils.h"
#include "../linkedlist/requiredIncludes.h"


int loadHistFile(char * fname, LinkedList * hist);
void addToHistory(char *, LinkedList * hist);
void saveToFile(char * fname, LinkedList * hist);
char * histAtIndex(int index, LinkedList * hist);
void printHistory(LinkedList * hist);




#endif 