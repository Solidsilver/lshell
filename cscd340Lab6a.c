#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
	pid_t pid;
	int fd[2], res, status;

	res = pipe(fd);

	if(res < 0)
	{
		printf("Pipe Failure\n");
		exit(-1);
	}// end if

	pid = fork();

	if(pid != 0)
	{
		int n;
		waitpid(pid, &n, 0);
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		int ret = execlp("wc", "wc", "-w", NULL);
		
	}// end if AKA parent
	else
	{
		close(fd[0]);
		//close(1);
		dup2(fd[1], 1);
		close(fd[1]);
		execlp("ls", "ls", "-l", NULL);
	}// end else AKA child

	return 0;

}// end main

