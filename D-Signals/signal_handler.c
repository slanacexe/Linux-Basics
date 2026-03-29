#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void my_term(int sig_code) {
	signal(SIGINT, SIG_IGN);
	signal(SIGUSR1, SIG_IGN);
	signal(SIGUSR2, SIG_IGN);
	if (sig_code == SIGTERM){
		while(1){
			printf("I refuse to terminate!\n");
		}
	}
	if (sig_code == SIGKILL) {
		while(1){
			printf("I refuse to be killed!\n");
		}
	}
}
		
void signal_handle(int sig_code) {
	if (sig_code == SIGINT){
		printf("SIGINT. Illegal termination!\n");
		exit(5);
	}
	else if (sig_code == SIGUSR1){
		printf("SIGUSR1. Continuing!\n");
	}
	else if (sig_code == SIGUSR2){
		printf("SIGUSR2. Legal termination!\n");
		exit(0);
	}

}

int main() {
	if (signal(SIGINT, signal_handle) == SIG_ERR){
		exit(2);
	}
	if (signal(SIGUSR1, signal_handle) == SIG_ERR){
		exit(2);
	}
	if (signal(SIGUSR2, signal_handle) == SIG_ERR){
		exit(2);
	}
	if (signal(SIGTERM, my_term) == SIG_ERR){
		exit(2);
	}

	while(1)
		sleep(1);

	return 0;
}