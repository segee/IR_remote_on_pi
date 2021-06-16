#include <wiringPi.h>
#include <stdio.h>
#include <stdint.h>
int64_t my_ticks(void);




main()
{  int64_t edges[1000];
   double pulses[1000];
   int x;
   int y;
   int current_state;
   double max_pulse, average_pulses, num_pulse;

   wiringPiSetupGpio();
   pinMode(21,INPUT);
   while(digitalRead(21)); //wait for some signal
   edges[0]=my_ticks();
   x=1;
   current_state=0;
   while(1)
   {
     
     if(digitalRead(21) !=current_state)
     {
       edges[x++] = my_ticks();
       current_state = !current_state;
       }
     else if(current_state==1 && my_ticks()-edges[x-1] >500000000L) break;
   }
  for(y=1;y<x;y++)
  {
//     current_state=1;
     printf("time %ld value %d\n",(int)(edges[y]-edges[y-1]),current_state);
     pulses[y-1]=((double) edges[y]-edges[y-1]);
     current_state=!current_state;
}
  for(y=0;y<=x;y++)
  {
      printf("%lf \n",pulses[y]);
  }

  max_pulse=0;
  average_pulses=0;
  num_pulse=0;
  for(y=0;y<x;y+=2)
  {
    if(pulses[y]!=0)
    {
      if(pulses[y] > max_pulse) max_pulse=pulses[y];
      average_pulses += pulses[y];
      num_pulse+=1;
    }
  }
  average_pulses /= num_pulse;
  printf("The average pulse was %lf the number of pulses was %lf \n",average_pulses, num_pulse);
  printf("The longest pulse was %lf\n",max_pulse);

   
}
int64_t my_ticks(void)
{   
#include <time.h>
    struct timespec bruce;

    clock_gettime(CLOCK_REALTIME, &bruce);
    return (int64_t) bruce.tv_sec*1000000000L+bruce.tv_nsec;
}


