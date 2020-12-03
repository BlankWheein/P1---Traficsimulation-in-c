#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <windows.h>
#include <math.h>

#include "structs.h"
#include "functions.c"

int main(void) {
  srand(time(NULL));
  double thru_put = 709.0;
  int duration = 60*15;
  int iter_speed = 0;
  prompt(&thru_put, &iter_speed);

  double vehicles_per_hour = thru_put/60.0*30.0/60.0;
  printf("%lf", vehicles_per_hour);
  
  int cars_int = 1;
  int lights_int = 3;
  Road roads[] = {create_road(50, Car, 670), create_road(50, PlusBus, 670)};
  Traffic_light lights[] = {create_light(red, 1, 30, 30), create_light(red, 300, 3600, 1), create_light(red, 650, 31, 31)};
  Vehicle *cars = Create_allocate_cars(cars_int, roads);
  
  int done = 0;
  int secs = 0;
  double vehicles = 0;

  while(!done) {
      done = 1;
      if (secs % 30 == 0 && secs < duration && secs > 1) {
        cars = Realloc_cars(cars, &cars_int, (int)ceil(vehicles_per_hour), roads);
      }

      for(int i = 0; i < cars_int; i++) {
          cars[i] = drive(cars[i], cars, cars_int, roads, lights, lights_int);
          if (cars[i].state != Done) {
            done = 0;
          }
      }

      if ( secs < duration ) {
        done = 0;
      }

      for (int j = 0; j < lights_int; j++) {
        lights[j] = count_timer(lights[j]);
      }
      secs += 1;

      if (secs % iter_speed == 0) {
        Sleep(1);
        system("cls");
        printf("%d out of %d\n", secs,duration);
        pnt_avg_speed_bridge(cars, cars_int);
        print_traffic_light(lights, lights_int);
        sort_lanes(cars, cars_int);
      }

  }
  system("cls");

  int vehicles_per_lane[ROAD_COUNT];
  double secs_on_bridge[ROAD_COUNT];
  for (int i = 0; i < ROAD_COUNT; i++) {
    secs_on_bridge[i] = 0;
    vehicles_per_lane[i] = 0;
  }

  for (int i = 0; i < cars_int; i++) {
    cars[i].avg_speed = ms_to_kmt(cars[i].avg_speed_total / cars[i].secs_on_bridge);
    vehicles_per_lane[cars[i].lane] += 1;
    secs_on_bridge[cars[i].lane] += cars[i].secs_on_bridge;
  }
      sort_lanes_done(cars, cars_int);
  printf("%d out of %d\n", secs,duration);
  printf("Avarage secs on bridge per lane\n");
  for (int i = 0; i < ROAD_COUNT; i++) {
    printf("%lf: %d\n", secs_on_bridge[i] / vehicles_per_lane[i], vehicles_per_lane[i]);
  }
  

  return 0;
}
