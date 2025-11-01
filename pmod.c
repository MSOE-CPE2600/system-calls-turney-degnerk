/************************************************
* Filename: pmod.c
* Assignment: Lab 9- System Calls
* Section: 121
* Name: Kadie Degner
* Date: 11/01/2025
* Description: Program to use nice and nanosleep.
* Note: Compile with gcc -o pmod pmod.c
*       Run with ./pmod
************************************************/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

int main(int argc, char* argv[])
{
    errno = 0;
    // Reduce priority
    nice(10);
    if (errno != 0)
    {
        perror("Error: nice() failed.\n");
        exit(1);
    }

    // Sleep for 1,837,272,638 nanoseconds
    struct timespec ts;
    ts.tv_sec = 1;
    ts.tv_nsec = 837272638;
    nanosleep(&ts, NULL);

    // Print goodbye message
    printf("Goodbye!\n");

    return 0;
}