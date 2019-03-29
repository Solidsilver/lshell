#include "pipes.h"

int containsPipe(char *s)
{
	//printf("counting pipes in %s\n", s);
	int len = strlen(s);
	int count = 0;
	int x;
	for (x = 0; x < len; x++)
	{
		if (s[x] == '|')
		{
			count += 1;
		}
	}
	//printf("Returning pipeCount: %d\n", count);
	return count;
} // end containsPipe

char ***parsePipe(char *s, int pipeCount)
{
	char ***pipes = (char ***)calloc(pipeCount + 1, sizeof(char **));
	char **argv;
	char next[100];
	strcpy(next, s);
	char *save = NULL;
	int x = 0;
	while (containsPipe(next))
	{
		char nextCpy[100];
		strcpy(nextCpy, next);
		makeargs(strtok_r(nextCpy, "|", &save), &argv);
		strcpy(next, save);
		pipes[x] = argv;
		//printf("pipes:64: pipes at %d is %s\n", x, pipes[x][0]);
		x++;
	}
	makeargs(next, &argv);
	pipes[x] = argv;
	//printf("pipes:64: pipes at %d is %s\n", x, pipes[x][0]);
	return pipes;
}

void pipeIt(char ***cmds, int len)
{
	//int len = count;
	pid_t pid;
	int status, x, fd[2], fd2[2];
	pipe(fd);
	pipe(fd2);
	for (x = 0; x < len; x++)
	{
		pid = fork();
		if (pid == 0)
		{
			// if the child
			if (x > 0)
			{
				if (x % 2 == 0)
				{
					dup2(fd[0], 0);
				}
				else
				{
					dup2(fd2[0], 0);
				}
			}
			if (x < len - 1)
			{
				if (x % 2 == 0)
				{
					dup2(fd2[1], 1);
				}
				else
				{
					dup2(fd[1], 1);
				}
			}
			close(fd[0]);
			close(fd[1]);
			close(fd2[0]);
			close(fd2[1]);
			runIt(cmds[x]);
		}
		//parent goes again
	}
	close(fd[0]);
	close(fd[1]);
	close(fd2[0]);
	close(fd2[1]);
	waitpid(pid, &status, 0);
} // end pipeIt

void freePipes(char ***pipes, int len)
{
	int x;
	for (x = 0; x < len; x++) {
		char **words = pipes[x];
		int y = 0;
		char *wd = pipes[x][y];
		while (wd != NULL)
		{
			free(wd);
			y += 1;
			wd = pipes[x][y];
		}
		free(words);
	}
	free(pipes);
	pipes = NULL;
}
