#include "./pipes/pipes.h"
#include "./utils/myUtils.h"
#include "./process/process.h"
#include "./tokenize/makeArgs.h"
#include "./history/history.h"
//#include "./history/history.h"

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

	setenv("HISTCOUNT", "1000", 1);
	setenv("HISTFILESIZE", "2000", 1);

	LinkedList *LL_hist = linkedList();

	loadHistFile(".ussh_history", LL_hist);

	//printf("command?: ");
	printPrompt();
	fgets(s, MAX, stdin);
	strip(s);

	while (strcmp(s, "exit") != 0)
	{
		int wait = 1;
		if (s[strlen(s) - 1] == '&')
		{
			wait = 0;
			s[strlen(s) - 1] = '\0';
		}
		pid_t p = 0;
		if (wait == 0)
		{
			p = fork();
		}
		if (p == 0)
		{
			if (strcmp(s, "") != 0)
			{
				addToHistory(s, LL_hist);
			}
			pipeCount = containsPipe(s);
			if (pipeCount > 0)
			{
				prePipe = parsePrePipe(s, &preCount);
				postPipe = parsePostPipe(s, &postCount);
				pipeIt(prePipe, postPipe);
				clean(preCount, prePipe);
				clean(postCount, postPipe);
			} // end if pipeCount
			else if (strcmp("history", s) == 0)
			{
				printHistory(LL_hist);
			}
			else
			{
				argc = makeargs(s, &argv);
				if (argc != -1)
					forkIt(argv, 1);

				clean(argc, argv);
				argv = NULL;
			}
			if (wait == 0) {
				exit(0);
			}
		}

		//printf("command?: ");
		printPrompt();
		fgets(s, MAX, stdin);
		strip(s);

	} // end while
	saveToFile(".ussh_history", LL_hist);
	LL_hist = cleanLocal(LL_hist);

	return 0;

} // end main
