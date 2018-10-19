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

struct histlist
{
    LinkedList * LL_hist;
    Node * histPrintFrom;
    Node * histFileFrom;
    int printCount;
    int toFileCount;
};
typedef struct histlist HistList;

HistList * histList();

int loadHistFile(char * fname, HistList * hist);
void addToHistory(char *, HistList * hist);
void saveToFile(char * fname, HistList * hist);
char * histAtIndex(int index, HistList * hist);
void printHistory(HistList * hist);
void * cleanLocal(HistList * hist);
int replaceHist(char ** s, HistList * hist);



#endif 