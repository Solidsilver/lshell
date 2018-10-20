#include "linkedList.h"

LinkedList * linkedList()
{
	LinkedList * ll = (LinkedList *)calloc(1, sizeof(LinkedList));
	ll->head = (Node *)calloc(1, sizeof(Node));
	ll->head->data = NULL;
	ll->size = 0;
	return ll;
}// end linkedList


void clearList(LinkedList * theList, void (*removeData)(void *))
{
	if (theList == NULL) {
		perror("Invalid parameter: NULL LinkedList");
		exit(-99);
	}
	if (theList->size != 0) {
		Node * cur = theList->head->next;
		Node * temp;
		while (cur != NULL) {
			temp = cur;
			cur = cur->next;
			removeData(temp->data);
			temp->data = NULL;
			free(temp);
		}
		//free(theList->head);
	}
	free(theList->head);
	
}// end clearList

void printList(const LinkedList * theList, void (*convertData)(void *))
{
	if (theList->size == 0) {
		printf("Empty List\n");
	} else {
		Node * cur = theList->head->next;
		while (cur != NULL) {
			convertData(cur->data);
			cur = cur->next;
		}
		printf("\n");
	}
}// end printList

void printListFile(const LinkedList * theList, void (*convertData)(void *, FILE *), FILE * fout) {
	if (theList->size == 0) {
		fprintf(fout, "Empty List\n");
	} else {
		Node * cur = theList->head->next;
		while (cur != NULL) {
			convertData(cur->data, fout);
			cur = cur->next;
		}
		//fprintf(fout, "\n");
	}
}

void addLast(LinkedList * theList, Node * nn)
{
	if (theList == NULL) {
		perror("Invalid parameter: NULL LinkedList");
		exit(-99);
	}
	if (nn == NULL) {
		perror("Invalid parameter: NULL Node");
		exit(-99);
	}
	Node * cur = theList->head;
	while (cur->next != NULL) {
		cur = cur->next;
	}
	cur->next = nn;
	nn->prev = cur;
	theList->size = theList->size + 1;

}// end addLast

void addFirst(LinkedList * theList, Node * nn)
{
	if (theList == NULL) {
		perror("Invalid parameter: NULL LinkedList");
		exit(-99);
	}
	if (nn == NULL) {
		perror("Invalid parameter: NULL Node");
		exit(-99);
	}
	if (theList->head->next != NULL) {
		theList->head->next->prev = nn;
	}
	nn->next = theList->head->next;
	nn->prev = theList->head;
	theList->head->next = nn;
	theList->size = theList->size + 1;
}// end addFirst

void removeFirst(LinkedList * theList, void (*removeData)(void *))
{
	if (theList == NULL) {
		perror("Invalid parameter: NULL LinkedList");
		exit(-99);
	}
	if (theList->size > 0) {
		Node * temp = theList->head->next;
		theList->head->next = temp->next;
		if (temp->next != NULL) {
			temp->next->prev = theList->head;
		}
		removeData(temp->data);
		free(temp);
		theList->size = theList->size - 1;
	} else {
		printf("LinkedList is empty!\n");
	}	
   

}// end removeFirst

void removeLast(LinkedList * theList, void (*removeData)(void *))
{
	if (theList == NULL) {
		perror("Invalid parameter: NULL LinkedList");
		exit(-99);
	}
	if (theList->size > 0) {
		Node * cur = theList->head->next;
		Node * temp = theList->head;
		while (cur->next != NULL) {
			temp = cur;
			cur = cur->next;
		}
		temp->next = NULL;
		removeData(cur->data);
		free(cur);
		theList->size = theList->size - 1;
	} else {
		printf("LinkedList is empty!\n");
	}
	
}// end removeLast


void removeItem(LinkedList * theList, void * (*buildType)(FILE * stream), void (*removeData)(void *), int (*compare)(const void *, const void *))
{
	if (theList == NULL) {
		perror("Invalid parameter: NULL LinkedList");
		exit(-99);
	}
	if (theList->size > 0) {
		void * dat = buildType(stdin);
		Node * temp = theList->head->next;
		while (temp != NULL && compare(dat, temp->data) != 0) {
			temp = temp->next;
		}
		if (temp == NULL) {
			printf("Item not found\n");
		} else {
			temp->prev->next = temp->next;
			if (temp->next != NULL) {
				temp->next->prev = temp->prev;
			}
			removeData(temp->data);
			free(temp);
			theList->size = theList->size - 1;
		}
		removeData(dat);
		dat = NULL;
	} else {
		printf("LinkedList is empty!\n");
	}

}// end removeItem

void * itemAtIndex(LinkedList * theList, int index) {
	if (index >= theList->size) {
		return NULL;
	} else {
		printf("linkedlist.c:182: getting index %d\n", index);
		Node * cur = theList->head->next;
		int x;
		for (x = 0; x < index; x++) {
			cur = cur->next;
		}
		return cur->data;
	}
}