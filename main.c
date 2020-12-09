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
  double thru_put = 1700.0;
  int duration = 60*60;
  int iter_speed = 9999;
  int cars_sec = 30;
  prompt(&thru_put, &iter_speed, &cars_sec);

  double vehicles_per_hour = ceil(thru_put/60.0/60.0*cars_sec);
  printf("%lf", vehicles_per_hour);

  int cars_int = 1;
  int lights_int = 3;
  Road roads[] = {create_road(50, Car, 670), create_road(50, PlusBus, 670)};
  Traffic_light lights[] = {create_light(red, 1, 35, 30), create_light(red, 300, 3600, 1), create_light(red, 650, 25, 30)};
  Vehicle *cars = Create_allocate_cars(cars_int, roads);

  int done = 0;
  int secs = 0;
  double vehicles = 0;

  while(!done) {
      done = 1;
      if (secs % cars_sec == 0 && secs < duration && secs > 1) {
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
        Sleep(100);
        system("cls");
        printf("%d out of %d\n", secs,duration);
        pnt_avg_speed_bridge(cars, cars_int);
        printf("Average secs on bridge per lane\n");
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
        for (int i = 0; i < ROAD_COUNT; i++) {
          printf("%lf: %d\n", secs_on_bridge[i] / vehicles_per_lane[i], vehicles_per_lane[i]);
        }
              //print_traffic_light(lights, lights_int);
              //sort_lanes(cars, cars_int);
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
  printf("Duration of simulation %d,Time stopped spawning cars %d\n", secs, duration);
  printf("Avarage secs on bridge per lane\n");
  for (int i = 0; i < ROAD_COUNT; i++) {
    printf("%lf: %d\n", secs_on_bridge[i] / vehicles_per_lane[i], vehicles_per_lane[i]);
  }
  save_to_file(cars, cars_int, secs, duration);


  return 0;
}
