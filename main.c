#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


#include "functions.h"





int main(void) {

Car car = {0, 0, 0, 0, 50, 4, 10, 1};
Road road = {50, Car_lane, 670};
print_car(car);



return EXIT_SUCCESS;
}
