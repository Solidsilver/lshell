#include "process.h"

void forkIt(char ** argv)
{
	int status;
	pid_t pid = fork();

	if(pid != 0)
		waitpid(pid, &status, 0);

	else
	{
		execvp(argv[0], argv);
		printf("ussh: %s : command not found\n", argv[0]);
		exit(-1);
	}// end else

}// end forkIt

