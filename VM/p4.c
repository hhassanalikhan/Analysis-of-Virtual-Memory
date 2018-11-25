#include <stdlib.h>
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
    int fd = open("10mb.txt", O_RDONLY, (mode_t)0600);
    
    if (fd == -1)
    {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }        
    
    struct stat fileInfo = {0};
    
    if (fstat(fd, &fileInfo) == -1)
    {
        perror("Error getting the file size");
        exit(EXIT_FAILURE);
    }
    
    if (fileInfo.st_size == 0)
    {
        fprintf(stderr, "Error: File is empty, nothing to do\n");
        exit(EXIT_FAILURE);
    }
    
    printf("File size is %ji\n", (intmax_t)fileInfo.st_size);
    int pageSize = 4 * 1024;
    
    char * map = mmap(0, 100*1024*1024,  PROT_READ|PROT_WRITE, MAP_PRIVATE  , fd, 0);
   // char *map = mmap(0, 100*1024*1024, PROT_READ, MAP_SHARED  , fd, 0);

    if (map == MAP_FAILED)
    {
        close(fd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    double a,b,c,timerdifference;
    int var=0;
   
    int page=0;
    float avrg=0;
    int j=0;
    FILE *f1 = fopen("file1.txt", "w");
    FILE *f2 = fopen("file2.txt", "w");


if (f1 == NULL)
{
    printf("Error opening file!\n");
    exit(1);
}

    //for (i=1; i < 1000; i++)
    //{
     // var=map[i*4096];
   // }
map = mmap(0, 100*1024*1024, PROT_READ, MAP_SHARED  | MAP_POPULATE, fd, 0);
    
 for (i=0; i < 50; i++)
    {
        
        int average=0;

        for (average=0;average<1000;average++){
            for(page=i;page>=1;page--){
                
                j=page*pageSize;

                var=map[j];

            }
            j=i*pageSize;
            asm("cpuid");
            a=rdtsc();
            
            var=map[j];
            asm("cpuid");
            b=rdtsc();
            avrg=avrg+((b-a)/1.8);
        }
        avrg=avrg/1000;
        printf ("%f time  for page#  %d \n",avrg,i);
        
        fprintf(f1, "%d %f\n", i, avrg);
        avrg=0;
        

    
    }     

map = mmap(0, 100*1024*1024,  PROT_READ|PROT_WRITE, MAP_PRIVATE  , fd, 0);
        for (i=0; i < 50; i++)
    {
        
        int average=0;

        for (average=0;average<1000;average++){
            for(page=i;page>=1;page--){
                
                j=page*pageSize;

                map[j]='C';

            }
            j=i*pageSize;
            asm("cpuid");
            a=rdtsc();
            
            var=map[j];
            asm("cpuid");
            b=rdtsc();
            avrg=avrg+((b-a)/1.8);
        }
        avrg=avrg/1000;
        printf ("%f time  for page#  %d \n",avrg,i);
        
        fprintf(f2, "%d %f\n", i, avrg);
        avrg=0;
        

    
    }
    

/////////////////////////////////////////////




/* print some text 
const char *text = "Write this to the file";
fprintf(f, "Some text: %s\n", text);

/* print integers and floats */
/*
int i = 1;
float py = 3.1415927;
fprintf(f, "Integer: %d, float: %f\n", i, py);

/* printing single chatacters 
char c = 'A';
fprintf(f, "A character: %c\n", c);
*/
fclose(f1);
fclose(f2);






    // Don't forget to free the mmapped memory
    if (munmap(map, 100 *1024*1024) == -1)
    {
        close(fd);
        perror("Error un-mmapping the file");
        exit(EXIT_FAILURE);
    }

    // Un-mmaping doesn't close the file, so we still need to do that.
    close(fd);
    
    return 0;
}