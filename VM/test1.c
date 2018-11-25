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
//#define MAP_HUGE_2MB    (21 << MAP_HUGE_SHIFT)

int main(int argc, const char *argv[])
{    
    const char *filepath = "/tmp/mmapped.bin";

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
    char *map = mmap(0, 100*1024*1024, PROT_READ, MAP_SHARED  , fd, 0);
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
    FILE *f = fopen("file.txt", "w");
if (f == NULL)
{
    printf("Error opening file!\n");
    exit(1);
}

    //for (i=1; i < 1000; i++)
    //{
     // var=map[i*4096];
   // }
    int avrg[2000];
    int j = 0;
    for (i1=0; i1 < 2000 ; i1++)
    {
         for (i=0; i < 2000 ; i++)
        {
        
            int average=0;
           
            a=rdtsc();
            char x =map[j];
             j+=pagesize;
            avrg[j]
            b=rdtsc();
      
        }
   
        printf ("%f cycles for Page number %d \n",avrg[i1]/200,i1);
        
 
      }  
    
    }     

        for (i=0; i < 700; i++)
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
        
        fprintf(f, "%d %f\n", i, avrg);
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
fclose(f);







    // Don't forget to free the mmapped memory
    if (munmap(map, 36 *1024*1024) == -1)
    {
        close(fd);
        perror("Error un-mmapping the file");
        exit(EXIT_FAILURE);
    }

    // Un-mmaping doesn't close the file, so we still need to do that.
    close(fd);
    
    return 0;
}
