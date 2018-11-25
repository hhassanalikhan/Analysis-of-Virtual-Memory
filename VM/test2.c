/*#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include "rdtsc.h"
#include <sys/time.h>
#include <sys/resource.h>
#define MAP_HUGE_2MB    (21 << MAP_HUGE_SHIFT)

int main(int argc, const char *argv[])
{    
    const char *filepath = "/tmp/mmapped.bin";
unsigned long cpuMask;
cpuMask = 2; // bind to cpu 1
if(!sched_setaffinity(0, sizeof(cpuMask), &cpuMask)){
fprintf(stderr,"Running on one core!\n");
setpriority(PRIO_PROCESS, 0, 20);}
    
    char *vect;
    int pageSize= 4096;
    int numPages = 60*pageSize;
    void *addr=(malloc(numPages));// mmap(NULL, numPages, PROT_READ, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    //(length + pageSize - 1) / pageSize;
    numPages = (numPages) / 4096;
    vect = malloc(numPages);

    char * ma = (char * )addr;
    int j = mincore(addr, 300, vect) ;  
    printf("%d",j);
    int i =0;
     for( i =0;i<numPages;i++)
     {
        char q = ma[i];
    }
    vect = malloc(numPages);

     
     j = mincore(addr, 300, vect) ;  
    printf("%d",j);
    return 0;
}
*/

/*
 * Example of mincore(2).  Print out which blocks of the file are cached.
 *
 * Copyright (C) 2010, Marek Polacek <mmpolacek@gmail.com>
 */

#include <error.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main(int argc, char *argv[])
{
      int fd;
    struct stat stat;
    char *addr;
    unsigned char *vec;
    const size_t ps = sysconf(_SC_PAGESIZE);

 
    //fd = open("10mb.txt", 0);
    if (fd == -1)
        error(EXIT_FAILURE, errno, "open failed");

    if (fstat(fd, &stat) == -1)
        error(EXIT_FAILURE, errno, "fstat failed");

    addr=mmap(NULL, 60*4096,  PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    //mmap(NULL, len, PROT_READ, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
     if (addr == MAP_FAILED){
        printf("Map failed\n");
        return EXIT_FAILURE;
    }
    int numberOfPages =  ((60*4096) + 4096 - 1) / 4096;
    vec = malloc(numberOfPages);

    //(length+PAGE_SIZE-1) / PAGE_SIZE

    //vec = calloc(1, ((60*4096) + 4096 - 1) / 4096);
    //char c = addr[10] ;
    int j = mincore(addr, 60*4096, vec);

    if(j == -1){
        printf("min core error\n");
        return EXIT_FAILURE;
    } 57
 58

    

    int t = addr[10];
    //printf("Cached blocks of `%s':\n",addr);

    size_t i ;
    for (i= 0; i <= (60); ++i){
        if (vec[i] & 1)
            printf("%lu\n ", (unsigned long int)i);


    }
    
    //fputc('\n', stdout);

    free(vec);
    munmap(addr, 60*4096);
    close(fd);

    return EXIT_SUCCESS;
}