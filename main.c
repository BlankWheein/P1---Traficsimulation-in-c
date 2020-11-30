#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "structs.h"
#include "functions.c"

int main(void) {

  srand(time(NULL));
  int cars_int = 1;
  Vehicle *cars = Create_allocate_cars(cars_int);
  cars = Realloc_cars(cars, &cars_int, 1);
  int lights_int = 2;
  Road road = create_road(50, Car_lane, 670);
  Traffic_light lights[] = {create_light(red, 1, 25, 23), create_light(red, 300, 10, 100)};
  int done = 0;
  int secs = 0;

  while(!done) {
      done = 1;

      if (secs % 34 == 0 && secs > 1 && secs < 60*60) {
        cars = Realloc_cars(cars, &cars_int, 2);
      }

      for(int i = 0; i < cars_int; i++) {
          cars[i] = drive(cars[i], cars, cars_int, road, lights, lights_int);
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
        for (int i = 0; i < lights_int; i++) {
            printf("%s, %d, %.1lf\n", color_to_string(lights[i].color), lights[i].timer, lights[i].position);
        }
        print_vehicles(cars, cars_int);
      }

  }
  system("cls");
  print_all_vechiles(cars, cars_int);


  /*
   input cars/hour
  */

    return 0;
}
