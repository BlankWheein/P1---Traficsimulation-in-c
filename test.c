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

int testVecAccel(void);
int testVecDriving(void);
int testVecRedLight(void);
int testDoubleRng(void);
int testState_waiting_withlight(void);
int testState_waiting_withoutlight(void);
int test ( int (*f)(void), int *tests, int *error );

int main(void)
{
  int error = 0, tests = 0;
  printf("Startings unit tests:\n\n");
  
  test( testVecAccel, &tests, &error);
  test( testVecDriving, &tests, &error);
  test( testVecRedLight, &tests, &error);
  test( testDoubleRng, &tests, &error);
  test( testState_waiting_withlight, &tests, &error);
  test( testState_waiting_withoutlight, &tests, &error);
  
  printf("\nRan %d tests with a total of %d errors", tests, error);

}

int test ( int (*f)(void), int *tests, int *error ){
  int err = f();
  *tests += 1;
  *error += err;
  printf("Ran test %d with %d error(s)\n\n", *tests, err);
}

INT testVecAccel(void)
{
  /* Test 1: Testing Vehicle Acceleration*/
  printf("testing set_car_acceleration... ");
  int road_int = 1;
  int error = 0;
  Road roads[road_int];
  for (int i = 0; i < road_int; i++)
  {
    roads[i] = create_road(50, Car, 670);
  }
  int cars_int = 1;
  Vehicle *cars = Create_allocate_cars(cars_int, roads, road_int);

  cars[0].speed_limit = 150;
  cars[0].speed_limit_time = 60;
  cars[0] = set_car_acceleration(cars[0]);

  if (cars[0].acceleration != 5)
  {
    error = 1;
    printf("Error!\n  set_car_acceleration had 1 error\n");
  }
else
{
  printf("Done!\n");
}
return error;
}

int testVecDriving(void)
{
  /* Test 2: Testing vehicle driving with multiple vehicles*/
  printf("testing vehicle driving... ");
  int error = 0;
  int road_int = 1;
  Road roads[road_int];
  for (int i = 0; i < road_int; i++)
  {
    roads[i] = create_road(50, Car, 670);
  }
  int cars_int = 3;
  Vehicle *cars = Create_allocate_cars(cars_int, roads, road_int);
  cars[0].speed_limit = 0;
  int lights_int = 2;
  double pos = 300;

  Traffic_light lights[] = {
      create_light(red, 1, 35, 30),
      create_light(red, 650, 25, 30)};

  for (int i = 0; i < 3; i++)
  {
    cars[i].state = Driving;
    if (i == 1)
      pos -= 3;
    if (i == 2)
      pos -= 8;
    cars[i].position = pos;

    cars[i] = state_driving(cars[i], cars, cars_int, roads, lights, lights_int, road_int);
    if (i < 0)
    {
      if (cars[i].position - cars[i - 1].position < cars[i].safe_distance)
        error = 1;
    }
  }
  if (error == 1)
  {
    printf("Error!\n  A vehicle's position got too close to the vehicle in front\n");
  }
  else
  {
    printf("Done!\n");
  }
  return error;
}

int testVecRedLight(void)
{
  /* Test 3: Stopping at red light*/
  printf("testing vehicle driving and holding for red... ");
  int road_int = 1;
  int error = 0;
  Road roads[road_int];
  for (int i = 0; i < road_int; i++)
  {
    roads[i] = create_road(50, Car, 670);
  }
  int cars_int = 1;
  Vehicle *cars = Create_allocate_cars(cars_int, roads, road_int);

  int lights_int = 2;
  double pos = 649;
  Traffic_light lights[] = {
      create_light(red, 1, 35, 30),
      create_light(red, 650, 25, 30)};

  cars[0].state = Driving;
  cars[0].position = pos;
  lights[1].color = red;

  cars[0] = state_driving(cars[0], cars, cars_int, roads, lights, lights_int, road_int);

  if (cars[0].position > 650)
  {
    printf("Error!\n  The vehicle drove past a red light\n");
    error = 1;
  }
  else
  {
    printf("Done!\n");
  }

  return error;
}

int testScenario1(void)
{
  /* Test 4: One vehicle holding for red and another driving and holding behind vehicle*/
  printf("testing vehicle driving scenario 1: vehicle 1 holding for red and vehicle 2 driving to vehicle 1");
  int road_int = 1;
  Road roads[road_int];
  for (int i = 0; i < road_int; i++)
  {
    roads[i] = create_road(50, Car, 670);
  }
  int cars_int = 2;
  Vehicle *cars = Create_allocate_cars(cars_int, roads, road_int);

  int lights_int = 2;
  double pos = 649;
  int error = 0;
  Traffic_light lights[] = {
      create_light(red, 1, 35, 30),
      create_light(red, 650, 25, 30)};

  for (int i = 0; i < 2; i++)
  {
    cars[i].state = Driving;

    if (i == 0)
      pos -= 3;
    else if (i == 1)
      pos;

    cars[i].position = pos;
    cars[i] = state_driving(cars[i], cars, cars_int, roads, lights, lights_int, road_int);

    if (i == 1)
    {
      if (cars[1].position - cars[0].position < 5)
      {
        error = 1;
        break;
      }
    }
  }
  if (error == 0) {
    printf("Done!\n");
  }
  return error;
}

int testDoubleRng(void)
{
  /* Test 5: Random double in range */
  printf("testing double in range...");
  int min = 170, max = 250;
  int error = 0;
  int count = 0;
  for (int i = 0; i < 1000; i++)
  {
    double x = rand_uniform(min, max);
    if (x >= min && x <= max)
    {
      count += 1;
    }
  }
  if (count < 1000) {
printf("Error!\n  a random double number went outside the range\n");
error = 1;
  }
    
  else {
    printf("Done!\n");
  }
  return error;
}

int testState_waiting_withlight(void)
{
  /* Test 6: Testing vehicles entering the bridge */
  printf("testing vehicle entering bridge with multiple vehicles and 1 light... ");
  int error = 0;
  int road_int = 1;
  Road roads[road_int];
  for (int i = 0; i < road_int; i++)
  {
    roads[i] = create_road(50, Car, 670);
  }
  int cars_int = 3;
  Vehicle *cars = Create_allocate_cars(cars_int, roads, road_int);

  int lights_int = 1;
  double pos = 300;
  Traffic_light lights[] = {
      create_light(red, 1, 35, 30)};

  for (int j = 0; j < 40; j++)
  {
    for (int i = 0; i < cars_int; i++)
    {
      cars[i] = drive(cars[i], cars, cars_int, roads, lights, lights_int, road_int);
    }
    lights[0] = count_timer(lights[0]);
  }

  for (int i = 0; i < cars_int; i++)
  {
    if (cars[i].position < 1)
    {
      error += 1;
    }
  }

  if (error > 0)
  {
    printf("Error!\n  There was an error, rip\n");
  }
  else if (error == 0)
  {
    printf("Done!\n");
  }

  return error;
}

int testState_waiting_withoutlight(void)
{
  /* Test 7: Testing vehicles entering the bridge */
  printf("testing vehicle entering bridge with multiple vehicles and no lights... ");
  int error = 0;
  int road_int = 1;
  Road roads[road_int];
  for (int i = 0; i < road_int; i++)
  {
    roads[i] = create_road(50, Car, 670);
  }
  int cars_int = 3;
  Vehicle *cars = Create_allocate_cars(cars_int, roads, road_int);

  int lights_int = 1;
  double pos = 300;
  Traffic_light lights[] = {
      create_light(red, 9999, 25, 30)};

  for (int j = 0; j < 10; j++)
  {
    for (int i = 0; i < cars_int; i++)
    {
      cars[i] = drive(cars[i], cars, cars_int, roads, lights, lights_int, road_int);
    }
  }

  for (int i = 0; i < cars_int; i++)
  {
    if (cars[i].position < 1)
    {
      error += 1;
    }
  }

  if (error > 0)
  {
    printf("Error!\n  There was an error, rip\n");
  }
  else if (error == 0)
  {
    printf("Done!\n");
  }

  return error;
}
