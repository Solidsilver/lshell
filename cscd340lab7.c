#include "./pipes/pipes.h"
#include "./utils/myUtils.h"
#include "./process/process.h"
#include "./tokenize/makeArgs.h"
#include "./history/history.h"
//#include "./history/history.h"

void printPrompt() {
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
  char ** prePipe = NULL, ** postPipe = NULL;
  char * prompt = SHN;

  LinkedList * LL_hist = linkedList();

  loadHistFile(".ussh_history", LL_hist);
  
  //printf("command?: ");
  printPrompt();
  fgets(s, MAX, stdin);
  strip(s);



  while(strcmp(s, "exit") != 0)
  {
	if (strcmp(s, "") != 0) {
		addToHistory(s, LL_hist);
	}
	pipeCount = containsPipe(s);
	if(pipeCount > 0)
	{
		prePipe = parsePrePipe(s, &preCount);
		postPipe = parsePostPipe(s, &postCount);
		pipeIt(prePipe, postPipe);
		clean(preCount, prePipe);
        clean(postCount, postPipe);
	}// end if pipeCount
	else if (strcmp("history", s) == 0) {
		printHistory(LL_hist);
	}	  
	else
	{
		int wait = 1;
		if (s[strlen(s)-1] == '&') {
			wait = 0;
			s[strlen(s)-1] = '\0';
		}
		argc = makeargs(s, &argv);
	  	if(argc != -1)
	  		forkIt(argv, wait);
	  
	  	clean(argc, argv);
	  	argv = NULL;
	}
	
	//printf("command?: ");
	printPrompt();
	fgets(s, MAX, stdin);
	strip(s);

  }// end while
  saveToFile(".ussh_history", LL_hist);
  LL_hist = cleanLocal(LL_hist);

  return 0;

}// end main



