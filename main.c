#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "functions.c"

int main(void) {

Car car = {0, 0, 0, 0, 50, 4, 10, 1};
Car car2 = {0, 0, 12, 0, 50, 4, 10, 2};
Car car3 = {0, 0, 56, 0, 50, 4, 10, 3};
Road road = {50, Car_lane, 670};
Car cars[] = {car, car2, car3};


Car closest = get_nearest_car(car, cars, 3);
print_cars(cars, 3);
printf("\n");
print_car(closest);


return 0;
}
