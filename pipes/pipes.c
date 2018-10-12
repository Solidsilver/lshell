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
	char cpyS[100];
	strcpy(cpyS, s);
	char * token = strtok_r(cpyS, "|", &save);
	*preCount = makeargs(token, &args);
	return args;
}// end parsePrePipe


char ** parsePostPipe(char *s, int * postCount)
{
	char** args = NULL;
	char * save = NULL;
	char cpyS[100];
	strcpy(cpyS, s);
	char * token = strtok_r(cpyS, "|", &save);
	*postCount = makeargs(save, &args);
	return args;
}// end parsePostPipe


void pipeIt(char ** prePipe, char ** postPipe)
{
	pid_t p = fork();
	if (p) {
		int n;
		waitpid(p, &n, 0);
	} else {
		int fd[2], res, status, ret;
		res = pipe(fd);
		p = fork();

		if (p) {
			int n;
			waitpid(p, &n, 0);
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
			ret = execvp(postPipe[0], postPipe);
			printf("%s: %s : command not found\n", SHN, postPipe[0]);
        	exit(ret);
		} else {
			close(fd[0]);
			int saved_stdout = dup(1);
			dup2(fd[1], 1);
			close(fd[1]);
			ret = execvp(prePipe[0], prePipe);
			dup2(saved_stdout, 1);
			close(saved_stdout);
			printf("%s: %s : command not found\n", SHN, prePipe[0]);
			exit(ret);
		}
	}

}// end pipeIt

