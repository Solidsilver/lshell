#include "./pipes/pipes.h"
#include "./utils/myUtils.h"
#include "./process/process.h"
#include "./tokenize/makeArgs.h"
int main()
{

	int argc, pipeCount;	
	char **argv = NULL, s[MAX];
	int preCount = 0, postCount = 0;
	char ** prePipe = NULL, ** postPipe = NULL;

	printf("command?: ");
	fgets(s, MAX, stdin);
	strip(s);

	while (strcmp(s, "exit") != 0) {
		
	}


	loadRC();
	loadHistory();

	
  

}// end main

int loadRC() {
	return 0;
}

int loadHistory() {
	return 0;
}

