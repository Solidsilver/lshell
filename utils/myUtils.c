#include "myUtils.h"

void strip(char *array)
{
	if(array == NULL)
	{
		perror("array is null");
		exit(-99);
	}// end if

	int len = strlen(array), x = 0;
   
	while(array[x] != '\0' && x < len)
	{
	  if(array[x] == '\r')
		 array[x] = '\0';

	  else if(array[x] == '\n')
		 array[x] = '\0';

	  x++;

}// end while
   
}// end strip

int replaceString(char **s, char *target, char *replace) {
	char *start, scpy[strlen(*s) + 1];
	int oldLen, newLen;
	strip(target);
	strip(replace);
	oldLen = strlen(target);
	newLen = strlen(replace);
	strcpy(scpy, *s);
	start = strstr(scpy, target);
	//printf("copy is %s\n", scpy);
	//strcpy(scpy, start);
	if (start != NULL) {
		int newStrLen = strlen(scpy) - oldLen + newLen;
		char * newS = (char *)calloc(newStrLen + 5, sizeof(char));
		int x;
		char * cur;
		for (x = 0, cur = &(s[0][0]); strcmp(cur, start) != 0; x++, cur = &(s[0][x])) {
			newS[x] = (*s)[x];
		}
		int x2;
		for (x2 = 0; x2 < newLen; x2++) {
			newS[x+x2] = replace[x2];
		}
		for (x = x; x < strlen(*s) ; x++) {
			newS[x+x2] = (*s)[x + oldLen];
		}
		free(*s);
		//printf("I'm freee!\n");
		*s = newS;
	}
	return 0;

}
