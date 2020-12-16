#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>

#include "headers\structs.h"
#include "headers\vehicles.h"
#include "headers\functions.h"
#include "headers\traffic_light.h"

#include "source\traffic_light.c"
#include "source\vehicles.c"
#include "source\functions.c"

int main(void)
{
  srand(time(NULL));
  /* Defines input parameters */
  double thru_put = 1700.0;
  int duration_multiplier = 60;
  int iter_speed = 9999;
  int cars_sec = 30;
  int road_int = 0, bus_lane_int = 0;
  int duration = 0;
  prompt(&thru_put, &iter_speed, &cars_sec, &road_int, &bus_lane_int, &duration);
  duration *= duration_multiplier;
  double vehicles_per_hour = ceil(thru_put / 60.0 / 60.0 * cars_sec);

  /* Creates the roads from input */
  Road roads[road_int];
  for (int i = 0; i < bus_lane_int; i++)
  {
    roads[i] = create_road(50, PlusBus, 670);
  }
  for (int j = bus_lane_int; j < road_int; j++)
  {
    roads[j] = create_road(50, Car, 670);
  }


  /* Creates the vehicle and traffic lights array */
  int cars_int = 1;
  int lights_int = 3;
  Traffic_light lights[] = {
                            create_light(red, 1, 35, 30),
                            create_light(green, 300, 2000, 300),
                            create_light(red, 650, 25, 30)
                          };
  Vehicle *cars = Create_allocate_cars(cars_int, roads, road_int);

  int done = 0;
  int secs = 0;

  printf("RUNNING SIMULATION\n");
  while (!done)
  {
    done = 1;
    if (secs % cars_sec == 0 && secs < duration && secs > 1)
    {
      cars = Realloc_cars(cars, &cars_int, (int)ceil(vehicles_per_hour), roads, road_int);
    }

    for (int i = 0; i < cars_int; i++)
    {
      cars[i] = drive(cars[i], cars, cars_int, roads, lights, lights_int, road_int);
      if (cars[i].state != Done)
      {
        done = 0;
      }
    }

    if (secs < duration)
    {
      done = 0;
    }

    for (int j = 0; j < lights_int; j++)
    {
      lights[j] = count_timer(lights[j]);
    }
    secs += 1;

    if (secs % iter_speed == 0)
    {

      system("cls");
      printf("%d out of %d\n", secs, duration);
      pnt_avg_speed_bridge(cars, cars_int);
      printf("Avarage secs on bridge per lane : Total amount of Vehicles in lane\n");
      int vehicles_per_lane[road_int];

      double secs_on_bridge[road_int];
      for (int i = 0; i < road_int; i++)
      {
        secs_on_bridge[i] = 0;
        vehicles_per_lane[i] = 0;
      }
      for (int i = 0; i < cars_int; i++)
      {
        cars[i].avg_speed = ms_to_kmt(cars[i].avg_speed_total / cars[i].secs_on_bridge);
        vehicles_per_lane[cars[i].lane] += 1;
        secs_on_bridge[cars[i].lane] += cars[i].secs_on_bridge;
      }
      for (int i = 0; i < road_int; i++)
      {
        printf("%lf: %d\n", secs_on_bridge[i] / vehicles_per_lane[i], vehicles_per_lane[i]);
      }
      print_traffic_light(lights, lights_int);
      sort_lanes(cars, cars_int);
    }
    Sleep(10);
  }
  system("cls");

  int vehicles_per_lane[road_int];
  double secs_on_bridge[road_int];
  for (int i = 0; i < road_int; i++)
  {
    secs_on_bridge[i] = 0;
    vehicles_per_lane[i] = 0;
  }

  for (int i = 0; i < cars_int; i++)
  {
    cars[i].avg_speed = ms_to_kmt(cars[i].avg_speed_total / cars[i].secs_on_bridge);
    vehicles_per_lane[cars[i].lane] += 1;
    secs_on_bridge[cars[i].lane] += cars[i].secs_on_bridge;
  }
  save_to_file(cars, cars_int, secs, duration, thru_put, iter_speed, cars_sec, road_int, bus_lane_int);
  sort_lanes_done(cars, cars_int);
  printf("\n");
  printf("Duration of simulation %d,Time stopped spawning cars %d\n", secs, duration);
  printf("Avarage secs on bridge per lane\n");
  for (int i = 0; i < road_int; i++)
  {
    printf("%lf: %d\n", secs_on_bridge[i] / vehicles_per_lane[i] + 1, vehicles_per_lane[i]);
  }
  printf("Total Vehicles: %d", cars_int);
  

  return 0;
}
