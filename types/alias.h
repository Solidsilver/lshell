
#ifndef ALIAS_H_
#define ALIAS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct alias
{
   char * name;
   char * value;
   //int len;
};
typedef struct alias Alias;

void cleanTypeAlias(void * ptr);

void * buildTypeAliasStr(char * alias, char * value);
void printTypeAlias(void * passedIn);

void printTypeAliasFile(void * passedIn, FILE * fout);
int compareAlias(const void * p1, const void * p2);



#endif /* ALIAS_H_ */
