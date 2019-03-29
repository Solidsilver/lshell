#include "./pipes/pipes.h"
#include "./utils/myUtils.h"
#include "./process/process.h"
#include "./tokenize/makeArgs.h"
#include "./history/history.h"

void printPrompt()
{
	printf(SHN);
	printf("-");
	printf("%.2f", VER);
	printf("$ ");
}

int main()
{

	int argc = 0, pCount = 0;
	char *s;
	char **argv;
	char ***toPipe;

	s = (char *)calloc(100, sizeof(char));
	fgets(s, MAX, stdin);
	strip(s);
	pCount = containsPipe(s);

	toPipe = parsePipe(s, pCount);
	pipeIt(toPipe, pCount + 1);

	freePipes(toPipe, pCount + 1);
	free(s);
}

/* 
int main()
{

	int argc, pipeCount;
	char **argv = NULL;
	int preCount = 0, postCount = 0;
	char **prePipe = NULL, **postPipe = NULL;
	char *prompt = SHN;
	//create vars
	int wait;
	char *s = (char *)calloc(1000, sizeof(char));
	pid_t pid;

	//Start getting input
	char **pipCmds[2];
	s = (char *)calloc(1000, sizeof(char));
	//printf("command?: ");
	printPrompt();
	fgets(s, MAX, stdin);
	strip(s);

	int x = 0;
	while (strcmp(s, "exit") != 0)
	{
		int pipeCount = containsPipe(s);
		//printf("got pipecount %d\n", pipeCount);
		if (pipeCount > 0)
		{
			char ***pipes = parsePipe(s, pipeCount);
			int x = 0;
			int y;
			for (y = 0; y <= pipeCount; y++)
			{
				printf("%d)\n", y);
				printargs(pipes[x]);
			}
			pipeIt(pipes, x);
			free(pipes);

		} // end if pipeCount
		else
		{
		}

		printPrompt();
		fgets(s, MAX, stdin);
		strip(s);
		x++;

	} // end while

	//pipeIt(pipCmds, 2);

	free(s);

	printf("exit\n");
	return 0;

} // end main */
