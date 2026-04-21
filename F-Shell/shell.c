#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <termios.h>

#define MAX_ARGS 64
#define MAX_HISTORY 100
#define MAX_PROCESSES 100
#define MAX_LEN_OF_PATH 2048

typedef struct {
	pid_t pid;
	char name[100];
	int running;
} Process;

Process processArr[MAX_PROCESSES];
int processCounter = 0;

char history[MAX_HISTORY][1024];
int historyCounter = 0;

struct sigaction before;
struct termios shellTermSettings;

void markProcessFinished(pid_t pid);

void handleSigint(int sig) {
	printf("\n> ljuska primila SIGINT\n");
}

void handleSigchld(int sig) {
	pid_t pid;

	while ((pid = waitpid(-1, NULL, WNOHANG)) > 0) {
		markProcessFinished(pid);
	}
}

void printShellPrompt() {
	char currentDir[MAX_LEN_OF_PATH];

	if (getcwd(currentDir, sizeof(currentDir))) {
		printf("USER : %s $ ", currentDir);
		fflush(stdout);
	} else {
		perror("!! getcwd() error !!");
	}
}

void printHistory() {
	for (int i = 0; i < historyCounter; i++)
		printf("%4d %s\n", i + 1, history[i]);
}

void printProcesses() {
	printf("PID\tNAME\n");

	for (int i = 0; i < processCounter; i++) {
		if (processArr[i].running)
			printf("%d\t%s\n", processArr[i].pid, processArr[i].name);
	}
}

int parseLine(char *line, char *args[], int *background) {
	int argCount = 0;
	*background = 0;

	args[argCount] = strtok(line, " \t\n");

	while (args[argCount] != NULL && argCount < MAX_ARGS - 1) {
		args[++argCount] = strtok(NULL, " \t\n");
	}

	if (argCount > 0 && strcmp(args[argCount - 1], "&") == 0) {
		*background = 1;
		args[argCount - 1] = NULL;
	}

	return argCount;
}

void markProcessFinished(pid_t pid) {
	for (int i = 0; i < processCounter; i++) {
		if (processArr[i].pid == pid) {
			processArr[i].running = 0;
			return;
		}
	}
}

void killProcess(char *sigStr, char *pidStr) {
	if (!sigStr || !pidStr) {
		printf("kill -SIGNAL pid\n");
		return;
	}

	if (sigStr[0] == '-')
		sigStr++;

	int sig;

	if (sigStr[0] >= '0' && sigStr[0] <= '9') {
		sig = atoi(sigStr);
	} else {
		if (!strcmp(sigStr, "SIGINT"))
			sig = 2;
		else if (!strcmp(sigStr, "SIGKILL"))
			sig = 9;
		else if (!strcmp(sigStr, "SIGTERM"))
			sig = 15;
		else if (!strcmp(sigStr, "SIGSTOP"))
			sig = 19;
		else {
			printf("Neadekvatan signal!\n");
			return;
		}
	}

	pid_t pid = atoi(pidStr);

	for (int i = 0; i < processCounter; i++) {
		if (processArr[i].pid == pid && processArr[i].running) {
			kill(pid, sig);
			return;
		}
	}

	printf("Proces nije iz ove ljuske/sesije\n");
}

void addProcess(pid_t pid, char *name) {
	if (processCounter >= MAX_PROCESSES)
		return;

	processArr[processCounter].pid = pid;
	strcpy(processArr[processCounter].name, name);
	processArr[processCounter].running = 1;

	processCounter++;
}

pid_t runProgram(char *instr[], int background) {
	pid_t pidNew;

	if ((pidNew = fork()) == 0) {
		sigaction(SIGINT, &before, NULL);
		setpgid(0, 0);

		if (!background)
			tcsetpgrp(STDIN_FILENO, getpid());

		execvp(instr[0], instr);

		perror("Program se ne moze pokrenuti!");
		exit(1);
	}

	addProcess(pidNew, instr[0]);

	return pidNew;
}

int main() {
	struct sigaction act;

	printf("<> ljuska (PID = %d) pokrenuta\n", getpid());

	act.sa_handler = handleSigint;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGINT, &act, &before);

	act.sa_handler = handleSigchld;
	sigaction(SIGCHLD, &act, NULL);

	act.sa_handler = SIG_IGN;
	sigaction(SIGTTOU, &act, NULL);

	tcgetattr(STDIN_FILENO, &shellTermSettings);

	char line[1024];
	char *args[MAX_ARGS];

	while (1) {
		printShellPrompt();

		if (fgets(line, sizeof(line), stdin) == NULL)
			continue;

		line[strcspn(line, "\n")] = '\0';

		if (strlen(line) == 0)
			continue;

		strcpy(history[historyCounter++], line);

		if (line[0] == '!') {
			int n = atoi(line + 1);
			if (n > 0 && n <= historyCounter) {
				strcpy(line, history[n - 1]);
				printf("%s\n", line);
			}
		}

		int background;
		int argCount = parseLine(line, args, &background);

		if (argCount == 0)
			continue;

		if (!strcmp(args[0], "exit")) {
			printf("> Izlaz iz ljuske\n");
			exit(0);
		}

		if (!strcmp(args[0], "history")) {
			printHistory();
			continue;
		}

		if (!strcmp(args[0], "cd")) {
			if (args[1])
				chdir(args[1]);
			else
				chdir(getenv("HOME"));
			continue;
		}

		if (!strcmp(args[0], "ps")) {
			printProcesses();
			continue;
		}

		if (!strcmp(args[0], "kill")) {
			killProcess(args[1], args[2]);
			continue;
		}

		pid_t pid = runProgram(args, background);

		if (!background) {
			pid_t pidFinished;

			do {
				pidFinished = waitpid(pid, NULL, 0);

				if (pidFinished > 0) {
					markProcessFinished(pidFinished);

					tcsetpgrp(STDIN_FILENO, getpgid(0));
					tcsetattr(STDIN_FILENO, 0, &shellTermSettings);

					break;
				}
			} while (pidFinished <= 0);
		}
	}

	return 0;
}