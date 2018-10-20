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

int replaceEnvVars(char **s)
{
	char *start, scpy[strlen(*s) + 1], *token, *save;
	strcpy(scpy, *s);
	start = strstr(scpy, "$");
	if (start != NULL)
	{
		token = strtok_r(start, " :\"", &save);
		char *t = &token[1];
		char *envRet = getenv(t);
		if (envRet == NULL)
		{
			envRet = "";
		}
		replaceString(s, token, envRet);
		replaceEnvVars(s);
	}
	return 0;
}

int hasAlias(char *in)
{
	//int ret = 0;
	char *start;
	start = strstr(in, "alias");
	if (start != NULL)
	{
		return 1;
	}
	return 0;
}

int strhasstr(char *containing, char *in)
{
	char *start;
	start = strstr(in, in);
	if (start != NULL)
	{
		return 1;
	}
	return 0;
}

void runCommand(char **strin, HistList *LL_hist, LinkedList *LL_alias)
{
	char *s = *strin;
	int argc, pipeCount;
	char **argv = NULL;
	int preCount = 0, postCount = 0;
	char **prePipe = NULL, **postPipe = NULL;

	if (replaceHist(strin, LL_hist) == 0)
	{
		s = *strin;
		addToHistory(s, LL_hist);
		replaceEnvVars(strin);
		s = *strin;
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
			int pipeCount = containsPipe(s);
			if (pipeCount > 0)
			{
				char ***pipes = parsePipe(s, pipeCount);
				int x = 0;
				pipeIt(pipes, pipeCount);
				free(pipes);
			}
			else if (strhasstr(s, "alias"))
			{
				
			}
			else
			{
				argc = makeargs(s, &argv);
				if (argc != -1)
					run(argv, 1, LL_hist, LL_alias);

				clean(argc, argv);
				argv = NULL;
				if (wait == 0)
				{
					exit(0);
				}
			}
		}
	}
}

int main()
{
	char *s;
	char *prompt = SHN;

	s = (char *)calloc(1000, sizeof(char));

	setenv("HISTCOUNT", "1000", 1);
	setenv("HISTFILESIZE", "2000", 1);

	HistList *LL_hist = histList();
	LinkedList *LL_alias = linkedList();

	loadHistFile(".ussh_history", LL_hist);

	FILE *fin = openInputFile(".usshrc");
	if (fin != NULL)
	{
		int count = countRecords(fin, 1);
		int x;
		for (x = 0; x < count; x++)
		{
			fgets(s, MAX, fin);
			strip(s);
			if (strcmp("", s) != 0)
			{
				runCommand(&s, LL_hist, LL_alias);
			}
		}
	}

	//printf("command?: ");
	printPrompt();
	fgets(s, MAX, stdin);
	strip(s);

	while (strcmp(s, "exit") != 0)
	{
		if (strcmp(s, "") != 0)
		{
			runCommand(&s, LL_hist, LL_alias);
		}
		free(s);
		s = (char *)calloc(1000, sizeof(char));
		printPrompt();
		fgets(s, MAX, stdin);
		strip(s);

	} // end while*/
	saveToFile(".ussh_history", LL_hist);
	LL_hist = cleanLocal(LL_hist);
	clearList(LL_alias, cleanTypeWord);
	free(LL_alias);

	free(s);

	return 0;

} // end main
