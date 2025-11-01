/***************************************************************************
 * Filename: info.c
 * Name: Kadie Degner
 * Date: 10/29/2025
 * Description: Program to use various information maintenance system calls.
 * Note: Compile with gcc -o info info.c
 *       Run with ./info
 ***************************************************************************/

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h> 


int main(int argc, char* argv[])
{
    // Get current time in nanoseconds since the Epoch
    struct timespec currentTime;
    if (clock_gettime(CLOCK_REALTIME, &currentTime) == 0) {
        printf("Current time: %ld nanoseconds since the Epoch.\n",
           (long int)((currentTime.tv_sec * 1000000000LL) + currentTime.tv_nsec));
    }

    // Get system's hostname
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == 0) {
        printf("Network Name (hostname): %s\n", hostname);
    }
    
    // Get the os name, os release, os version, and hardware type
    struct utsname sysInfo;
    if (uname(&sysInfo) == 0) {
        printf("Operating System Name: %s\n", sysInfo.sysname);
        printf("Operating System Release: %s\n", sysInfo.release);
        printf("Operating System Version: %s\n", sysInfo.version);
        printf("Hardware Type: %s\n", sysInfo.machine);
    }

    // Get number of CPUs on the system
    int numCPUs = get_nprocs();
    if (numCPUs > 0) {
        printf("Number of CPUs: %d\n", numCPUs);
    }

    // Get total physical memory in bytes
    long pageSize = getpagesize();
    long numPages = sysconf(_SC_PHYS_PAGES);
    long totalMemory = pageSize * numPages;
    if (totalMemory >= 0) {
        printf("Total Physical Memory: %ld bytes\n", totalMemory);
    }

    // Get the total amount of free memory in bytes
    long freePages = sysconf(_SC_AVPHYS_PAGES);
    long freeMemory = pageSize * freePages;
    if (freeMemory >= 0) {
        printf("Total Free Memory: %ld bytes\n", freeMemory);
    }
    
    return 0;
}