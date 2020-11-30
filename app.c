#include <stdio.h>
#include <stdlib.h>
#include <time.h>


double rand_uniform(double min, double max){
  return (max - min) * ( (double)rand() / (double)RAND_MAX ) + min;
}

int main(void) {
    srand(time(NULL));
    for(int i = 0; i < 100 ; i++)
      printf("%lf  ", rand_uniform(6.4, 8.2));
    return 0;
}