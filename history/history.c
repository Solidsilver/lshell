#include "history.h"

HistList *histList()
{
    HistList *hl = (HistList *)calloc(1, sizeof(HistList));
    hl->LL_hist = linkedList();
    hl->histPrintFrom = hl->LL_hist->head;
    hl->histFileFrom = hl->LL_hist->head;
    hl->printCount = atoi(getenv("HISTCOUNT"));
    hl->toFileCount = atoi(getenv("HISTFILESIZE"));
    return hl;
}

int loadHistFile(char *fname, HistList *histlist)
{
    LinkedList *hist = histlist->LL_hist;
    if (hist == NULL)
    {
        perror("Cannot fill null list");
        exit(-1);
    }
    FILE *fin = openInputFile(fname);
    if (fin == NULL)
    {
        printf("history file does not exist\n");
        return 0;
    }
    else
    {
        int total = countRecords(fin, 1);
        printf("%d records\n", total);
        if (total != 0)
        {
            if (hist == NULL)
            {
                perror("Invalid parameter: NULL LinkedList");
                exit(-99);
            }
            Node *nn;
            int x;
            for (x = 0; x < total; x++)
            {
                nn = (Node *)calloc(1, sizeof(Node));
                nn->data = buildTypeWord(fin);
                addLast(hist, nn);
                if (hist->size > histlist->printCount)
                {
                    histlist->histPrintFrom = histlist->histPrintFrom->next;
                }
            }
        }
        fclose(fin);
        return 0;
    }
}

void addToHistory(char *cmd, HistList *histlist)
{
    LinkedList *hist = histlist->LL_hist;
    Node *nn;
    nn = buildNode_Str(cmd, buildTypeWordStr);
    addLast(hist, nn);
    if (hist->size > histlist->printCount)
    {
        histlist->histPrintFrom = histlist->histPrintFrom->next;
    }
}

void saveToFile(char *fname, HistList *histlist)
{
    LinkedList *hist = histlist->LL_hist;
    char temp[MAX];
    FILE *fout = openOutputFile(fname);
    printListFile(hist, printTypeWordFile, fout);
    fclose(fout);
}

void printHistory(HistList *histlist)
{
    LinkedList *hist = histlist->LL_hist;
    //int printCount = getenv("HISTCOUNT");
    if (hist->size == 0)
    {
        printf("Empty List\n");
    }
    else
    {
        Node *cur = histlist->histPrintFrom->next;
        int x = 1;
        while (cur != NULL)
        {
            printf("%d\t", x);
            printTypeWord(cur->data);
            cur = cur->next;
            x++;
        }
        printf("\n");
    }
    //printList(hist, printTypeWord);
}

char *histAtIndex(int index, HistList *histlist)
{
    LinkedList *hist = histlist->LL_hist;
    Word *w = itemAtIndex(hist, index);
    //printf("WORD: %s\n", w->ltrs);
    return w->ltrs;
}

void *cleanLocal(HistList *histlist)
{
    clearList(histlist->LL_hist, cleanTypeWord);
    free(histlist->LL_hist);
    free(histlist);
    return NULL;
}

int replaceHist(char **s, HistList *histlist)
{
    LinkedList *history = histlist->LL_hist;
    char *start, scpy[strlen(*s) + 1], *token, *save, rplc[MAX];
    int oldLen, newLen;
    strcpy(scpy, *s);
    start = strstr(scpy, "!");
    if (start != NULL)
    {
        token = strtok_r(start, " ", &save);
        oldLen = strlen(token);
        int index = -1;
        if (token[1] != '!')
        {
            char *t = &token[1];
            index = atoi(t);
        }
        if (index >= history->size)
        {
            fprintf(stderr, "%s: %s: event not found\n", SHN, token);
            return (-1);
        }
        char *histItem = histAtIndex(index, histlist);
        strcpy(rplc, histItem);
        replaceString(s, token, rplc);

        //free(newS);
        return replaceHist(s, histlist);
    }
    return 0;
}
