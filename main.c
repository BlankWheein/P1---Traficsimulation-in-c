#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "structs.h"
#include "functions.c"

int main(void) {

  int cars_int = 1;
  Car *cars = Create_allocate_cars(cars_int);
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

      if (secs % 1800 == 0) {
        system("cls");
        for (int i = 0; i < lights_int; i++) {
            printf("%s, %d, %.1lf\n", color_to_string(lights[i].color), lights[i].timer, lights[i].position);
        }
        print_cars(cars, cars_int);
      }

  }
  system("cls");
  print_all_cars(cars, cars_int);


  /*
   input cars/hour
  */

  /*
    Car cars[] = {create_car(1,0, 150), create_car(2,0, 160), create_car(3,0, 120), create_car(4,0, 160), create_car(5,0, 160), create_car(6,0, 160)};
    int cars_int = 6;
    int lights_int = 2;
    Road road = create_road(50, Car_lane, 670);
    Traffic_light lights[] = {create_light(red, 300, 10, 100), create_light(red, 1, 25, 5)};
    int done = 0;
    print_cars(cars, cars_int);

    while(!done) {
        system("cls");
        printf("%s, %.1lf\n", color_to_string(lights[0].color), lights[0].position);
        done = 1;
        for(int i = 0; i < cars_int; i++) {
            cars[i] = drive(cars[i], cars, cars_int, road, lights, lights_int);
            if (cars[i].ID == -1) {
                cars_int += 1;
            }
            if (cars[i].state != Done) {
              done = 0;
            }
        }
        for (int j = 0; j < lights_int; j++) {
          lights[j] = count_timer(lights[j]);
        }
        print_cars(cars, cars_int);

        Sleep(200);

    }
    */

    return 0;
}
