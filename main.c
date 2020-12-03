#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>

#include "structs.h"
#include "functions.c"

int main(void) {
  srand(time(NULL));
  double vehicles_per_hour = (709.0)/60.0*30.0/60.0;
  printf("%lf", vehicles_per_hour);
  
  int cars_int = 1;
  int lights_int = 3;
  Road roads[] = {create_road(50, Car, 670), create_road(50, Car, 670), create_road(20, PlusBus, 670)};
  Traffic_light lights[] = {create_light(red, 1, 30, 30), create_light(red, 300, 1500, 50), create_light(red, 650, 31, 31)};
  Vehicle *cars = Create_allocate_cars(cars_int, roads);
  
  int done = 0;
  int secs = 0;
  double vehicles = 0;

  while(!done) {
      done = 1;
      if (secs % 30 == 0 && secs < 60*60 && secs > 1) {
        cars = Realloc_cars(cars, &cars_int, (int)ceil(vehicles_per_hour), roads);
      }

      for(int i = 0; i < cars_int; i++) {
          cars[i] = drive(cars[i], cars, cars_int, roads, lights, lights_int);
          if (cars[i].ID == -1) {
              cars_int += 1;
          }
          if (cars[i].state != Done) {
            done = 0;
          }
      }

      if ( secs < 60*60 ) {
        done = 0;
      }

      for (int j = 0; j < lights_int; j++) {
        lights[j] = count_timer(lights[j]);
      }
      secs += 1;

      if (secs % 1 == 0) {
        system("cls");
        
        print_traffic_light(lights, lights_int);
        sort_lanes(cars, cars_int);
      }

  }
  system("cls");
  sort_lanes_done(cars, cars_int);
  return 0;
}
