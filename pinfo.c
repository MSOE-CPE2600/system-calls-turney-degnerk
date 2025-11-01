/*******************************************************************
* Filename: pinfo.c
* Name: Kadie Degner
* Date: 11/01/2025
* Description: Program to use various process control system calls.
* Note: Compile with gcc -o pinfo pinfo.c
*       Run with ./pinfo
*******************************************************************/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/resource.h>
#include <sched.h>

int main(int argc, char* argv[])
{
    pid_t pid;
    int scheduler;
    int priority;

    // Determine which PID to use
    if (argc == 1) {
        pid = getpid(); // current process
    } else if (argc == 2) {
        pid = atoi(argv[1]); // user-specified PID
    } else {
        printf("Usage: %s\n", argv[0]);
        exit(1);
    } 

    // Get priority and scheduler
    errno = 0;
    priority = getpriority(PRIO_PROCESS, pid);
    if (errno != 0) {
        printf("Error: getpriority() failed.\n");
        exit(1);
    }

    scheduler = sched_getscheduler(pid);
    if (scheduler == -1) {
        printf("Error: sched_getscheduler() failed.\n");
        exit(1);
    }

    // Scheduler to text
    char* scheduler_text;
    switch (scheduler) {
        case SCHED_OTHER: scheduler_text = "SCHED_OTHER"; break;
        case SCHED_FIFO:  scheduler_text = "SCHED_FIFO"; break;
        case SCHED_RR:    scheduler_text = "SCHED_RR"; break;
        #ifdef SCHED_BATCH
        case SCHED_BATCH: scheduler_text = "SCHED_BATCH"; break;
        #endif
        #ifdef SCHED_IDLE
        case SCHED_IDLE:  scheduler_text = "SCHED_IDLE"; break;
        #endif
        #ifdef SCHED_DEADLINE
        case SCHED_DEADLINE: scheduler_text = "SCHED_DEADLINE"; break;
        #endif
        default: scheduler_text = "UNKNOWN"; break;
    }

    // Output results
    printf("Process ID: %d\n", pid);
    printf("Scheduling Policy: %s\n", scheduler_text);
    printf("Priority: %d\n", priority);

    return 0;
}