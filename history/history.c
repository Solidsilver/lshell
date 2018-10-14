#include "history.h"

int loadHistFile(char * fname, LinkedList * hist) {
    if (hist == NULL) {
        perror("Cannot fill null list");
        exit(-1);
    }
    FILE * fin = openInputFile(fname);
    if (fin == NULL) {
        printf("history file does not exist\n");
        return 0;
    } else {
        int total = countRecords(fin, 1);
        printf("%d records\n", total);
        buildListTotal(hist, total, fin, buildTypeWord);
        fclose(fin);
        return 0;
    }
}

void addToHistory(char * cmd, LinkedList * hist) {
    Node * nn;
    nn = buildNode_Str(cmd, buildTypeWordStr);
    addLast(hist, nn);
    if (hist->size > 1000) {
        removeFirst(hist, cleanTypeWord);
    }
}

void saveToFile(char * fname, LinkedList * hist) {
    char temp[MAX];
    FILE * fout = openOutputFile(fname);
    printListFile(hist, printTypeWordFile, fout);
    /*Node * nn;
    for (nn = hist->head->next; nn != NULL; nn = nn->next) {
        printTypeWordFile(nn->data, fout);
    }*/
    //fprintf(fout, "\n");
}

void printHistory(LinkedList * hist) {
    printList(hist, printTypeWord);
}

char * histAtIndex(int index, LinkedList * hist) {
    Node * nix = itemAtIndex(hist, index);
    Word * w = (Word *)(nix->data);
    return w->ltrs;
}

void * cleanLocal(LinkedList * hist) {
    clearList(hist, cleanTypeWord);
    return NULL;
}

