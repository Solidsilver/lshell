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
	if (isBuiltin(argv[0]) == 1) {
		runBuiltin(argv);
		exit(0);
	} else {
		execvp(argv[0], argv);
		fprintf(stderr, "%s: %s: command not found\n", SHN, argv[0]);
		exit(-1);
	}
}

int isBuiltin(char * cmd) {
	if (strcmp(cmd, "cd") == 0) {
		return 1;
	}
	if (strcmp(cmd, "history") == 0) {
		return 1;
	}
	if (strcmp(cmd, "alias") == 0) {
		return 1;
	}
	return 0;
}

int runBuiltin(char ** argv) {
	if (strcmp(argv[0], "cd") == 0) {
		int fail;
		if (argv[1] == NULL) {
			fail = chdir(getenv("HOME"));
		}
		fail = chdir(argv[1]);

		if (fail) {
			fprintf(stderr, "%s: %s: %s: No such file or directory\n", SHN, argv[0], argv[1]);
			return 1;
		}
		return 0;
	}
	if (strcmp(argv[0], "history") == 0) {
		return 1;
	}
	if (strcmp(argv[0], "alias") == 0) {
		fprintf(stderr, "Aliasing not supported\n");
		return 1;
	}
	return 1;
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

