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
 * prioritization, preemption, and context switching in operating systems.
 */

#define STACK_SIZE 40

int requestedInterrupt = 0;
int currentInterrupt = 0;
int interruptStack[STACK_SIZE] = {0};
static int stackTop = -1;
static int timeCounter = 1;
int pendingInterrupts[4] = {0};

bool isStackEmpty() {
    return stackTop == -1;
}

int getHighestPending() {
    for (int i = 3; i >= 0; i--) {
        if (pendingInterrupts[i] > 0)
            return i + 1;
    }
    return 0;
}

void pushInterrupt(int interrupt) {
    for (int i = 0; i < 5; i++)
        interruptStack[++stackTop] = interrupt;
}

void printPriorityBits(int priority) {
    int bits[5] = {0, 0, 0, 0, 0};

    if (priority >= 1 && priority <= 4)
        bits[priority - 1] = 1;

    for (int i = 0; i < 5; i++)
        printf("%d", bits[i]);
}

void printPendingQueue() {
    printf("%d%d%d%d0",
           pendingInterrupts[0],
           pendingInterrupts[1],
           pendingInterrupts[2],
           pendingInterrupts[3]);
}

void printStack() {
    if (isStackEmpty() || currentInterrupt == 0) {
        printf("-");
        return;
    }

    int i = stackTop;
    bool first = true;
    int activeInterrupt = interruptStack[i];

    while (i >= 0 && interruptStack[i] == activeInterrupt)
        i--;

    while (i >= 0) {
        int priority = interruptStack[i];

        while (i >= 0 && interruptStack[i] == priority)
            i--;

        if (!first)
            printf(" ; ");

        printPriorityBits(priority);
        printf(",reg[%d]", priority);
        first = false;
    }

    if (!first)
        printf(" ; ");

    printPriorityBits(0);
    printf(",reg[0]");
}

void printState() {
    printf("t: %2d <> PENDING: ", timeCounter);
    printPendingQueue();
    printf(" | ACTIVE: ");
    printPriorityBits(currentInterrupt);
    printf(" | STACK: ");
    printStack();
    printf(" | ");
}

void printMessage(const char *messageType, int priority) {
    printState();

    if (priority == 0) {
        printf("%s\n", messageType);
    } else if (messageType[0] == 'P') {
        printf("Processing interrupt with priority %d\n", priority);
    } else if (messageType[0] == 'W') {
        printf("Interrupt with priority %d placed in waiting queue\n", priority);
    }

    timeCounter++;
}

void processPendingInterrupts() {
    while (1) {
        int nextInterrupt = getHighestPending();

        if (nextInterrupt > currentInterrupt) {
            pendingInterrupts[nextInterrupt - 1]--;
            currentInterrupt = nextInterrupt;
            pushInterrupt(currentInterrupt);
        }

        if (currentInterrupt == 0 || isStackEmpty()) {
            if (isStackEmpty())
                currentInterrupt = 0;
            break;
        }

        while (!isStackEmpty() &&
               interruptStack[stackTop] == currentInterrupt) {

            printMessage("Processing", interruptStack[stackTop]);
            interruptStack[stackTop--] = 0;
            sleep(1);
        }

        if (!isStackEmpty())
            currentInterrupt = interruptStack[stackTop];
        else
            currentInterrupt = 0;
    }
}

void handleSigint(int sig) {
    printf("Enter interrupt priority (1-4): ");
    scanf("%d", &requestedInterrupt);

    if (requestedInterrupt < 1 || requestedInterrupt > 4) {
        printMessage("!! INVALID INTERRUPT !!", 0);
        sleep(1);
        return;
    }

    if (requestedInterrupt > currentInterrupt) {
        currentInterrupt = requestedInterrupt;
        pushInterrupt(currentInterrupt);
        processPendingInterrupts();
    } else {
        pendingInterrupts[requestedInterrupt - 1] = 1;
        printMessage("Waiting", requestedInterrupt);
        return;
    }
}

int main(void) {
    struct sigaction action;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_NODEFER;
    action.sa_handler = handleSigint;
    sigaction(SIGINT, &action, NULL);

    printf("Starting main program... PID (%ld)\n", (long)getpid());

    for (int i = 1; i <= 20; i++) {
        printMessage("Processing main program", 0);
        sleep(1);
        processPendingInterrupts();
    }

    return 0;
}