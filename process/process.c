#include "process.h"


void forkIt(char ** argv, int wait)
{
	int status;
	pid_t pid = fork();

	if(pid) {
		if (wait == 1) {
			waitpid(pid, &status, 0);
		}
	} 
	else
	{
		runIt(argv);
	}// end else

}// end forkIt

void runIt(char ** argv) {
	execvp(argv[0], argv);
	printf("%s: %s : command not found\n", SHN, argv[0]);
	exit(-1);
}




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

