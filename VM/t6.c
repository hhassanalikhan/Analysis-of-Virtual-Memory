
#include "inttypes.h"
#include <error.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/io.h>

int main(int argc, char *argv[])


    {

          int *p=(int *)malloc(sizeof(int));
           printf("\n After freeing memory :: %d ",p );
 printf ( "Child : Child’s PID: %d\n", getpid());
  
  while(1)
  {

  }
   return 0;
    }
