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
		printf("got pipecount %d\n", pipeCount);
		if (pipeCount > 0)
		{
			char ***pipes = parsePipe(s, pipeCount);
			int x = 0;
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

	} // end while*/

	//pipeIt(pipCmds, 2);

	free(s);

	printf("exit\n");
	return 0;

} // end main
