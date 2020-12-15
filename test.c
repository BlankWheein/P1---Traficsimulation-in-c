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



int main(void) {
printf("RUNNING SIMULATION\n");
int roads_int = 4;
Road roads[roads_int];

 for (int i = 0; i < 2; i++)
  {
    roads[i] = create_road(50, PlusBus, 670);
  }
  for (int j = 2; j < 4; j++)
  {
    roads[j] = create_road(50, Car, 670);
  }

  int cars_int = 1;
  int lights_int = 3;
  Traffic_light lights[] = {create_light(red, 1, 35, 30), create_light(red, 300, 5400, 300), create_light(red, 650, 25, 30)};

  Vehicle *cars = Create_allocate_cars(cars_int, roads, 4);
  cars[0].position = 100;
  cars[0].speed = 0;
  cars[0].acceleration = 2.00;
  print_vehicle(cars[0]);
  cars[0] = accelerate_car(cars[0], roads, roads_int);
  print_vehicle(cars[0]);

return 0;
}
