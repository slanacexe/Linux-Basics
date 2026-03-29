#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

/*
* Priority Interrupt Handling Simulation - by @slanac (slanacexe on GitHub)
*
* This program simulates a priority-based interrupt handling mechanism.
* It models four interrupt priority levels and demonstrates how higher-
* priority interrupts can preempt lower-priority ones.
*
* Interrupt requests are triggered using SIGINT (Ctrl+C), after which
* the user enters the desired interrupt priority (1–4). If the new
* interrupt has a higher priority than the currently active one,
* it is immediately processed; otherwise, it is placed in a pending queue.
*
* A stack is used to simulate context saving and restoration during
* interrupt handling. The program also prints a timeline showing:
* - pending interrupts
* - currently active priority
* - stack state
* - processing events
*
* This simulation illustrates basic concepts of interrupt handling,
* prioritization, preemption, and context switching in operating systems(eg. Linux).
*/

#define stackSize 40

int wantedINT = 0;
int currentINT = 0;
int stack[stackSize] = {0};
static int stackPointer = -1;
static int timeline = 1;
int pendingINT[4] = {0};

bool isEmpty() {
	    return stackPointer == -1;
}

int highestPending() {
	for (int i = 3; i >= 0; i--) {
	        if (pendingINT[i] > 0)
            		return i + 1;
    	}
    	
    	return 0;
}

void pushINT(int INT)  {
    	for (int i = 0; i < 5; i++)
        	stack[++stackPointer] = INT;
}

void printTP(int priority) {
    	int bits[5] = {0, 0, 0, 0, 0};
    
    	if (priority >= 1 && priority <= 4)
        	bits[priority - 1] = 1;
    
    	for (int i = 0; i < 5; i++)
        	printf("%d", bits[i]);
}

void printKZ() {
    	printf("%d%d%d%d0", pendingINT[0], pendingINT[1], pendingINT[2], pendingINT[3]);
}

void printStack() {
    	if (isEmpty()) {
        	printf("-");
        	return;
    	}
    
    	if (currentINT == 0) {
        	printf("-");
        	return;
    	}
    
    	int i = stackPointer;
    	bool first = true;
    	int activeINT = stack[i];
    
    	while (i >= 0 && stack[i] == activeINT)
        	i--;
    
    	while (i >= 0) {
        	int priority = stack[i];
        	
        	while (i >= 0 && stack[i] == priority)
            		i--;
        
        	if (!first)
            		printf(" ; ");
        
        	printTP(priority);
        	printf(",reg[%d]", priority);
        	first = false;
    	}
    
    	if (!first)
        	printf(" ; ");
        	
    	printTP(0);
    	printf(",reg[0]");
}

void printInfo() {
    	printf("t: %2d <> K_Z: ", timeline);
    	printKZ();
    	printf(" | T_P: ");
    	printTP(currentINT);
    	printf(" | STOG: ");
    	printStack();
    	printf(" | ");
}

void printMessage(const char *opis, int priority) {
    	printInfo();
    
    	if (priority == 0) {
        	printf("%s\n", opis);
    	} else if (opis[0] == 'O') {
        	printf("Obrada prekida prioriteta %d\n", priority);
    	} else if (opis[0] == 'P') {
        	printf("Prekid prioriteta %d stavljen u cekanje\n", priority);
    	}
    	
    	timeline++;
}

void processPendingINT() {
    	while (1) {
        	int nextINT = highestPending();
        
        	if (nextINT > currentINT) {
            		pendingINT[nextINT - 1]--;
            		currentINT = nextINT;
            		pushINT(currentINT);
        	}
        
        	if (currentINT == 0 || isEmpty()) {
            		if (isEmpty())
                		currentINT = 0;
                		
            		break;
        	}
        
  		while (!isEmpty() && stack[stackPointer] == currentINT) {
            		printMessage("Obrada", stack[stackPointer]);
            		stack[stackPointer--] = 0;
            		sleep(1);
  		}
        
        	if (!isEmpty()) {
            		currentINT = stack[stackPointer];
        	} else {
        	    	currentINT = 0;
        	}
    	}
}

void handle_sigint(int sig) {
    	printf("Unesite prioritet prekida: ");
    	scanf("%d", &wantedINT);
    
    	if (wantedINT < 1 || wantedINT > 4) {
        	printMessage("!! NEISPRAVAN PREKID !!", 0);
        	sleep(1);
        	return;
    	}
    
    	if (wantedINT > currentINT) {
        	currentINT = wantedINT;
        	pushINT(currentINT);
        	processPendingINT();
    	} else {
        	pendingINT[wantedINT - 1] = 1;
        	printMessage("Prekid", wantedINT);
        	return;
    	}
}

int main(void) {
    	struct sigaction act;
    	sigemptyset(&act.sa_mask);
    	act.sa_flags = SA_NODEFER;
    	act.sa_handler = handle_sigint;
    	sigaction(SIGINT, &act, NULL);

    	printf("Pokretanje glavnog programa... PID (%ld)\n", (long)getpid());
    	
    	for (int i = 1; i <= 20; i++) {
        	printMessage("Obrada glavnog programa", 0);
        	sleep(1);
        	processPendingINT();
    	}
    	
    	return 0;
}