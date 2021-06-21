#include <wiringPi.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int64_t my_ticks(void);
int grab_a_wave(int64_t * buffer, int numelem);
int analyze_wave(int64_t * buffer,int numedges);


main()
{  int64_t edges[1000];
   int x;
   int value;

   wiringPiSetupGpio();
   pinMode(21,INPUT);
 
   
    while(1)
    {
      x=grab_a_wave(edges,1000);
      if(x<0){ printf("Yikes bad wave\n"); continue;}
       if(analyze_wave(edges,x))
      {
       // value=get_value(edges,x);
        printf("value is %lx\n",value);
      }
      else
      {
        printf("bogus wave\n");
      }

    }



   
}
int64_t my_ticks(void)
{   
#include <time.h>
    struct timespec bruce;

    clock_gettime(CLOCK_REALTIME, &bruce);
    return (int64_t) bruce.tv_sec*1000000000L+bruce.tv_nsec;
}



int grab_a_wave(int64_t * edges, int numelem)
{  int x,current_state;
  while(digitalRead(21)); //wait for some signal
   edges[0]=my_ticks();
   x=1;
   current_state=0;
   while(x<numelem)
   {
     
     if(digitalRead(21) !=current_state)
     {
       edges[x++] = my_ticks();
       current_state = !current_state;
       }
     else if(current_state==1 && my_ticks()-edges[x-1] >500000000L) break;
   }
   if(x<5) return -1; //too short
   if(x==numelem) return -2; //too long

   //might want some more tests
   return x;
}

int analyze_wave(int64_t * edges, int x)
{
    int y;
    int nominal, test;
    
    
    if(x<24) return 0;
    nominal=(edges[3]-edges[2])>>13;  //units of 8 microseconds about 1/3 of a flash
    for(y=4;y<24&&y<x;y+=2)
    {  
        test=(edges[y+1]-edges[y])>>13;
        if(abs(test-nominal) > (nominal>>2)) 
        {
           printf("bursts are not the same length\n");
           return 0;
        }
     }
     return(1);
}
int get_value(int64_t * edges, int x)
{
  int nominal, value, y;
  value=0;

    nominal=(edges[4]-edges[3])>>13;
    for(y=4;y<x;y+=2)
    {
       //get space
       if((edges[y+1]-edges[y])>>13 > (nominal<<1)) value |=1;
       //stop on long burst
      
       if((edges[y+2]-edges[y+1])>>13 > (nominal<<1)) break;
       value <<=1;
    }
   return value;
}
      
       




