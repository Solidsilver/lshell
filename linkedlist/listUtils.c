#include "listUtils.h"

Node * buildNode(FILE * in, void *(*buildData)(FILE * fin) )
{
    return buildNode_Type(buildData(in));
}// end buildNode

Node * buildNode_Str(char * in, void *(*buildData)(char * in)) {
    return buildNode_Type(buildData(in));
}

Node * buildNode_Type(void * passedIn)
{
    if (passedIn == NULL) {
		perror("Invalid parameter: NULL pointer");
		exit(-99);
	}
    Node * nn = (Node *)calloc(1, sizeof(Node));
    nn->data = passedIn;
    return nn;
   
}// end buildNode_Type


void buildListTotal(LinkedList * myList, int total, FILE * fin, void * (*buildData)(FILE * in) )
{
    if (myList == NULL) {
		perror("Invalid parameter: NULL LinkedList");
		exit(-99);
	}
    Node * nn;
    int x;
    for (x = 0; x < total; x++) {
        nn = (Node *)calloc(1, sizeof(Node));
        nn->data = buildData(fin);
        addLast(myList, nn);
    }
    //rewind(fin);
}// end buildListTotal


void sort(LinkedList * theList, int (*compare)(const void *, const void *))
{
    if (theList == NULL) {
		perror("Invalid parameter: NULL LinkedList");
		exit(-99);
	}
    Node * start, *search, *min;
    void * temp;

    if(theList->size > 1)
    {

        for(start = theList->head->next; start->next != NULL; start = start->next)
        {
            min = start;

            for(search = start->next; search != NULL; search = search->next)
                if(compare(search->data, min->data) < 0)
                    min = search;

            temp = start->data;
            start->data = min->data;
            min->data = temp;

        }// end for start

    }// end if
}// end sort
