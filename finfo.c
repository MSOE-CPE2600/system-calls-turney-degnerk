/*********************************************************************
* Filename: finfo.c
* Assignment: Lab 9- System Calls
* Section: 121
* Name: Kadie Degner
* Date: 11/01/2025
* Description: Program to display file information using system calls.
* Note: Compile with gcc -o finfo finfo.c
*       Run with ./finfo
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/socket.h>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Error: Please provide a filename as an argument.\n");
        exit(1);
    }  

    const char* filename = argv[1];
    struct stat fileStat;

    // Get file information
    if (stat(filename, &fileStat) < 0)
    {
        printf("Error: stat() failed.\n");
        exit(1);
    }

    // Print file and type
    printf("File: %s\n", filename);
    printf("Type: ");

    switch (fileStat.st_mode & S_IFMT)
    {
        case S_IFREG:
            printf("Regular file\n");
            break;
        case S_IFDIR:
            printf("Directory\n");
            break;
        case S_IFLNK:
            printf("Symbolic link\n");
            break;
        case S_IFCHR:
            printf("Character device\n");
            break;
        case S_IFBLK:
            printf("Block device\n");
            break;
        case S_IFIFO:
            printf("FIFO/pipe\n");
            break;
        case S_IFSOCK:
            printf("Socket\n");
            break;
        default:
            printf("Unknown type\n");
            break;
    }

    // Print permissions
    printf("Permissions: ");
    printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");

    // Print owner
    printf("Owner UID: %d\n", fileStat.st_uid);

    // Print file size
    printf("Size: %ld bytes\n", (long int)fileStat.st_size);

    // Print last modification size
    printf("Last modified: %s", ctime(&fileStat.st_mtime));

    return 0;
}