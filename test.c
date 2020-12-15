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
   int road_int = 1;
   Road roads[road_int];
   for (int i = 0; i < road_int; i++){
     roads[i] = create_road(50, Car, 670);
   }
   int cars_int = 1;
   Vehicle *cars = Create_allocate_cars(cars_int, roads, road_int);
   cars[0].speed_limit = 150;
   cars[0].speed_limit_time = 60;
   printf("testing set_car_acceleration \n");
   cars[0] = set_car_acceleration(cars[0]);
 if (cars[0].acceleration == 5) {
   printf("set_car_acceleration no errors \n\n");
 }
   int lights_int = 2;
   Traffic_light lights[] = {
                             create_light(red, 1, 35, 30),
                             create_light(red, 650, 25, 30)
                           };
   cars[0].state = Driving;
   cars[0].position = 300;
   cars[0] = state_driving(cars[0], cars, cars_int, roads, lights, lights_int, road_int);

   printf("Starting at 300 after acceleration = %lf \n %s \n",cars[0].position, state_to_string(cars[0].state) );


int min = 170, max = 250;
int count = 0;
for (int i = 0; i < 1000; i++) {
  double x = rand_uniform(min, max);
  if (x >= min && x <= max) {
    count += 1;
  }
}
printf("%d\n",count );
}
