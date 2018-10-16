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

int replaceString(char **s, char *target, char *replace) {
	char *start, scpy[strlen(*s)], *token, *save;
	int oldLen, newLen;
	oldLen = strlen(target);
	newLen = strlen(replace);
	strcpy(scpy, *s);
	start = strstr(scpy, target);
	printf("copy is %s\n", scpy);
	//strcpy(scpy, start);
	if (start != NULL) {
		int newStrLen = strlen(*s) - oldLen + newLen;
		char * newS = (char *)calloc(newStrLen, sizeof(char));
		int x;
		char * cur;
		for (x = 0, cur = &(s[0][0]); strcmp(cur, start) != 0; x++, cur = &(s[0][x])) {
			//printf("cur is %s\n", cur);
			newS[x] = (*s)[x];
		}
		int x2;
		for (x2 = 0; x2 < newLen; x2++) {
			newS[x+x2] = replace[x2];
		}
		for (x = x; x < strlen(*s) ; x++) {
			newS[x+x2] = (*s)[x + oldLen]; 
		}
		//printf("new string %s\n", newS);
		free(s[0]);
		printf("I'm freee!\n");
		s[0] = newS;
	}
	return 0;

}

int replaceHist(char ** s, LinkedList *history) {
	printf("Entering replaceHistory\n");
	char *start, scpy[strlen(*s)], *token, *save, rplc[MAX];
	int oldLen, newLen;
	strcpy(scpy, *s);
	start = strstr(scpy, "!");
	//strcpy(scpy, start);
	if (start != NULL) {
		//printf("contains Bang!\n");
		token = strtok_r(start, " ", &save);
		printf("%s\n", token);
		oldLen = strlen(token);
		int index = 0;
		if (token[1] != '!') {
			char * t = &token[1];
			index = atoi(t);
		}
		printf("history index is %d\n", index);
		if (index >= history->size) {
			fprintf(stderr, "%s: %s: event not found\n", SHN, token);
			return(-1);
		}
		char * histItem = histAtIndex(index, history);
		printf("history command is %s\n", histItem);
		strcpy(rplc, histItem);
		//printf("new history command is %s\n", rplc);
		replaceString(s, token, rplc);
		
		//free(newS);
		return replaceHist(s, history);

	}
	return 0;
}

int replaceEnvVars(char ** s) {
	char *start, scpy[strlen(*s)], *token, *save;
	strcpy(scpy, *s);
	start = strstr(scpy, "$");
	if (start != NULL) {
		token = strtok_r(start, " ", &save);
		char * t = &token[1];
		char * envRet = getenv(t);
		if (envRet == NULL) {
			envRet = "";
		}
		replaceString(s, token, envRet);
		replaceEnvVars(s);
	}
	return 0;
}



int main() {

	//create vars
	int wait;
	char * s = (char*)calloc(1000, sizeof(char));
	pid_t pid;
	LinkedList *LL_hist, *LL_alias;

	//setup
	LL_hist = linkedList();
	//LL_alias = linkedList();
	loadHistFile(".ussh_history", LL_hist);

	setenv("HISTCOUNT", "1000", 1);
	setenv("HISTFILESIZE", "2000", 1);

	//Start getting input
	printPrompt();
	
	fgets(s, MAX, stdin);
	
	strip(s);

	while (strcmp(s, "exit") != 0)
	{
		replaceHist(&s, LL_hist);
		replaceEnvVars(&s);
		//replaceString(&s, "!!", "wow!");
		printf("Got back from replHist, new string is %s\n", s);
		pid = 0;
		wait = 1;
		if (s[strlen(s) - 1] == '&')
		{
			wait = 0;
			s[strlen(s) - 1] = '\0';
			pid = fork();
		}
		if (pid == 0) {



			if (wait == 0) {
				exit(0);
			}
		}



		addToHistory(s, LL_hist);
		//Go again
		printPrompt();
		fgets(s, MAX, stdin);
		strip(s);
	}
	//printf("exiting while\n");
	saveToFile(".ussh_history", LL_hist);

	//cleanup
	//NEED TO FREE LL_alias!!!!!!
	LL_hist = cleanLocal(LL_hist);
	free(s);

	printf("exit\n");
	return 0;

}// end main
