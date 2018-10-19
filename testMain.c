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
	char **argv = NULL, s[MAX];
	int preCount = 0, postCount = 0;
	char **prePipe = NULL, **postPipe = NULL;
	char *prompt = SHN;
	//create vars
	int wait;
	char *s = (char *)calloc(1000, sizeof(char));
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
		pipeCount = containsPipe(s);
		if (pipeCount > 0)
		{
			char **pipes[pipeCount + 1];
			char *next = s;
			int x = 0;
			while (next != NULL)
			{
				printf("1) next is %s\n", next);
				pipes[x] = parsePrePipe(next, &preCount);
				printf("2) saved %s\n", pipes[x][0]);
				next = parsePostPipe(next, &postCount);
				printf("3) next-next is %s\n", next);
				x++;
			}
			pipeIt(pipes, x);
			//clean(preCount, prePipe);
			//clean(postCount, postPipe);
		} // end if pipeCount

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

} // end main
