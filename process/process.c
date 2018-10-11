#include "process.h"

void forkIt(char ** argv, int wait)
{
	int status;
	pid_t pid = fork();

	if(pid) {
		if (!wait) {
			waitpid(pid, &status, 0);
		} else {
			printf("[] %d\n", pid);
		}
	} 
	else
	{
		execvp(argv[0], argv);
		printf("ussh: %s : command not found\n", argv[0]);
		exit(-1);
	}// end else

}// end forkIt

int isBackground(char * cmd) {
	int len = strlen(cmd);
	int count = 0;
	int x;
	for (x = 0; x < len; x++) {
		if (cmd[x] == '&') {
			return 1;
		}
	}
	return 0;
}

