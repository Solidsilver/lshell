#include "pipes.h"

int containsPipe(char *s)
{
	int len = strlen(s);
	int count = 0;
	int x;
	for (x = 0; x < len; x++) {
		if (s[x] == '|') {
			count += 1;
		}
	}
	return count;
}// end containsPipe


char ** parsePrePipe(char *s, int * preCount)
{
	char** args;
	char * save = NULL;
	char cpyS[strlen(s) + 1];
	printf("PRE: scopying: %s\n", s);
	strcpy(cpyS, s);
	printf("PRE: tokenizing\n");
	char * token = strtok_r(cpyS, "|", &save);
	printf("PRE-TOKEN IS %s\n", token);
	*preCount = makeargs(token, &args);
	return args;
}// end parsePrePipe


char * parsePostPipe(char *s, int * postCount)
{
	char** args = NULL;
	char * save = NULL;
	char cpyS[strlen(s) + 1];
	strcpy(cpyS, s);
	printf("POST: copy is %s\n", cpyS);
	char * token = strtok_r(cpyS, "|", &save);
	printf("POST-TOKEN IS: %s\n", save);
	printf("POST-SAVE IS: %s\n", save);
	return save;
}// end parsePostPipe


void pipeIt(char *** cmds, int count)
{	
	int len = count;
	//char ** cmds[len];
	//cmds[0] = prePipe;
	//cmds[1] = postPipe;
	//makeargs("wc", &cmds[2]);
	printf("PIPING with %d commands\n", len);
	pid_t pid;
	int status, ret, x, i;
	
	int fd[len - 1][2];
	for (i = 0; i < len - 1; i++) {
		pipe(fd[i]);
	}
	for (x = 0; x < len; x++) {
		pid = fork();
		if (pid == 0) {
			// if the child
			if (x > 0) {
				dup2(fd[x-1][0], 0);
			}
			if (x < len-1) {
				dup2(fd[x][1], 1);
			}
			for (i = 0; i < len - 1; i++) {
				close(fd[i][0]);
				close(fd[i][1]);
				
			}
			runIt(cmds[x]);
		}
		//if the parent
		//printf("Waiting for fork%d, pid%d\n", x, pid);
		//waitpid(0, &status, 0);
		//printf("Done waiting, next fork:\n");
	}

	//printf("Cleaning fd's\n");
	for (i = 0; i < len - 1; i++) {
		close(fd[i][0]);
		close(fd[i][1]);
	}

}// end pipeIt

