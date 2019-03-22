#include "myInt.h"

void * buildInt(FILE * stream)
{

	int val;

	printf("Please enter an integer ");
	fscanf(stream, "%d", &val);

	while(fgetc(stream) !='\n');

	MyInt * temp = calloc(1, sizeof(MyInt));
	temp->value = val;

	return temp;	

}

void printInt(void * ptr)
{
	MyInt * temp = (MyInt *)ptr;
	printf("Int: %d\n", temp->value);
}

void cleanInt(void * ptr)
{
	MyInt * temp = (MyInt *)ptr;
	free(temp);

}

int compareInt(const void * p1, const void * p2)
{
	MyInt * left = (MyInt *)p1;
   	MyInt *right = (MyInt *)p2;
	return left->value - right->value;
}
