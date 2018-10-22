#include "alias.h"
#include "../utils/myUtils.h"


void printTypeAlias(void * passedIn)
{
    printTypeAliasFile(passedIn, stdout);
}// end printType

void printTypeAliasFile(void * passedIn, FILE * fout) {
    if (passedIn == NULL) {
        printf("Cannot print word: parameter was NULL\n");
        exit(-99);
    }
	Alias * a1 = (Alias *)passedIn;
    fprintf(fout, "alias %s=%s\n", a1->name, a1->value);
}

void * buildTypeAliasStr(char * name, char * value) {
    strip(name);
    strip(value);
    //printf("Got in: Name: %s, Value %s\n", name, value);
    Alias * a1 = (Alias *)calloc(1, sizeof(Alias));
    //a1->len = strlen(str);
    a1->name = (char *)calloc(strlen(name)+1, sizeof(char));
    a1->value = (char *)calloc(strlen(value)+1, sizeof(char));
    strcpy(a1->name, name);
    strcpy(a1->value, value);
    //printf("going out: Name: %s, Value %s\n", a1->name, a1->value);
    return a1;
}

int compareAlias(const void * p1, const void * p2)
{
    if (p1 == NULL || p2 == NULL) {
        printf("Cannot compare words: one or more parameter was NULL\n");
        exit(-99);
    }
    Alias * a1 = (Alias *)p1;
    Alias * a2 = (Alias *)p2;
    return strcmp(a1->name, a2->name);
}// end compare


/**
 * @brief Cleans up all dynamically allocated memory for the word
 *
 * Cleans up and frees all the dynamically allocated memory 
 * In this case ltrs
 *
 * Each pointer in the specific data type is set to NULL after it has been freed.
 *
 * @param passedIn - The void * passed in representing the specific word
 *
 * @warning - The passed in void * passedIn is checked - exit(-99) if NULL
 */
void cleanTypeAlias(void * ptr)
{
    if (ptr == NULL) {
        printf("Cannot clean word: parameter was NULL\n");
        exit(-99);
    }
    Alias * temp = (Alias *)ptr;
    free(temp->name);
    free(temp->value);
    free(temp);     
}// end cleanType
