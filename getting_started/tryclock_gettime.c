#include <stdio.h>
#include <limits.h>
#include <stdint.h>


int64_t my_ticks(void);

main()
{  int64_t array[1000];
   int x;
   for(x=0;x<1000;x++) array[x]=my_ticks()+my_ticks();
   for(x=1;x<1000;x++) printf("%ld\n",(long)(array[x]-array[x-1]));

    printf("total time %ld\n",(long)(array[999]-array[0]));
   
}


int64_t my_ticks(void)
{   
#include <time.h>
    struct timespec bruce;

    clock_gettime(CLOCK_REALTIME, &bruce);
    return (int64_t) bruce.tv_sec*1000000000L+bruce.tv_nsec;
}

