#include "word.h"
#include "../utils/myUtils.h"


/**
 * @brief Prints the specific word.
 *
 * Format is word - length
 *
 * @param passedIn - The void * passed in representing a specific word
 *
 * @warning - The passed in void * passedIn is checked - exit(-99) if NULL
 */
void printTypeWord(void * passedIn)
{
    printTypeWordFile(passedIn, stdout);
}// end printType

void printTypeWordFile(void * passedIn, FILE * fout) {
    if (passedIn == NULL) {
        printf("Cannot print word: parameter was NULL\n");
        exit(-99);
    }
	Word * w1 = (Word *)passedIn;
    fprintf(fout, "%s\n", w1->ltrs);
}


/**
 * @brief Builds and returns a single word.
 *
 * Reads the initial data from the file and then builds
 * an object of type word.
 *
 * @note The carriage return will be removed when reading from the file
 *
 * @param fin - The FILE * representing the open file
 * @return void * - Representing a word object
 *
 * @warning - The passed in FILE * fin is checked - exit(-99) if NULL
 */
void * buildTypeWord(FILE * fin)
{
    if (fin == NULL) {
        printf("Cannot build word: FILE * was NULL\n");
        exit(-99);
    }
    char temp[100];
    fgets(temp, 100, fin);
    strip(temp);
    Word * w1 = (Word *)calloc(1, sizeof(Word));
    w1->len = strlen(temp);
    w1->ltrs = (char *)calloc(strlen(temp)+1, sizeof(char));
    strcpy(w1->ltrs, temp);
    return w1;
}// end buildType

void * buildTypeWordStr(char * str) {
    strip(str);
    Word * w1 = (Word *)calloc(1, sizeof(Word));
    w1->len = strlen(str);
    w1->ltrs = (char *)calloc(strlen(str)+1, sizeof(char));
    strcpy(w1->ltrs, str);
    return w1;
}


/**
 * @brief Builds and returns a single word.
 *
 * Reads the initial data from the keyboard by prompting the user.
 * A word object is constructed.
 *
 * @note The carriage return will be removed when reading from the keyboard
 *
 * @return void * - Representing a word object
 *
 */
void * buildTypeWord_Prompt()
{
    printf("Enter a word: ");
    return buildTypeWord(stdin);
}// end buildType_Prompt


/**
 * @brief Compares two objects of type word.
 *
 * Words are compared based on the letters (word)
 *
 * @note The passed in items will need to be cast to the appropriate word type.
 *
 * @param p1 - The void * representing an object of type word
 * @param p2 - The void * representing an object of type word
 * @return int - Representing order < 0 indicates p1 is less than p2,
 * > 0 indicates p1 is greater than p2 and == 0 indicates p1 == p2 for contents
 *
 * @warning - The passed in void * p1 is checked - exit(-99) if NULL
 * @warning - The passed in void * p2 is checked - exit(-99) if NULL
 */
int compareWords(const void * p1, const void * p2)
{
    if (p1 == NULL || p2 == NULL) {
        printf("Cannot compare words: one or more parameter was NULL\n");
        exit(-99);
    }
    Word * w1 = (Word *)p1;
    Word * w2 = (Word *)p2;
    return strcmp(w1->ltrs, w2->ltrs);
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
void cleanTypeWord(void * ptr)
{
    if (ptr == NULL) {
        printf("Cannot clean word: parameter was NULL\n");
        exit(-99);
    }
    Word * temp = (Word *)ptr;
    free(temp->ltrs);
    free(temp);     
}// end cleanType
