#include "./pipes/pipes.h"
#include "./utils/myUtils.h"
#include "./process/process.h"
#include "./tokenize/makeArgs.h"
#include "./history/history.h"

void printPrompt() {
	printf(SHN);
	printf("-");
	printf("%.2f", VER);
	printf("$ ");
}

char * parsePre(char *str, char * symb)
{
	char** args;
	char * save = NULL;
	char cpyS[100];
	strcpy(cpyS, str);
	char * token = strtok_r(cpyS, symb, &save);
	return token;
}// end parsePrePipe


char * parsePost(char *str, char * symb)
{
	char** args = NULL;
	char * save = NULL;
	char cpyS[100];
	strcpy(cpyS, str);
	char * token = strtok_r(cpyS, symb, &save);
	return save;
}// end parsePostPipe



int checkBackground(char * s) {
	if (isBackground(s)) {
		char pre[100];
		char post[100];
		strcpy(pre, parsePre(s, "&"));
		strcpy(post, parsePost(s, "&"));

		printf("forking\n");
		pid_t pid = fork();
		if (pid) {
			strcpy(s, post);
			return checkBackground(s);
		} else {
			strcpy(s, pre);
			return 1;
		}
	} else {
		return 0;
	}
}

void checkRedirect(char * s) {
	
}

void checkPipe(char * s) {
}

int main()
{

	int argc, pipeCount;	
	char **argv = NULL, **s;

	LinkedList * hist = (LinkedList *)calloc(1, sizeof(LinkedList));
	loadHistFile(".ussh_history", hist);

	s = (char**)calloc(1, sizeof(char *));
	*s = (char*)calloc(MAX, sizeof(char));

	

	printPrompt();
	fgets(*s, MAX, stdin);
	strip(*s);

	while (strcmp(*s, "exit") != 0) {
		if(strcmp(*s, "")) {
			addToHistory(*s, hist);
		}
		int isBack = checkBackground(*s);
		printf("Command is %s - ", *s);
		//checkRedirect(*s);
		//checkPipe(*s);
		argc = makeargs(*s, &argv);
		if (!strcmp(argv[0], "history")){
			printHistory(hist);
		} else if(strcmp(*s, "")) {
			if (isBack) {
				//printf("%s is a background command\n", *s);
				runIt(argv);
			} else {
				//printf("%s is NOT a background command\n", *s);
				forkIt(argv, 1);
			}
		}
		

		printPrompt();
		fgets(*s, MAX, stdin);
		strip(*s);
		
	}

	

	
  

}// end main
