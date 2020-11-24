#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "structs.h"
#include "functions.c"

int main(void) {
    Car cars[100] = {create_car(1, 0, 40), create_car(2, 0, 160)};
    int cars_int = 2;
    Road road = create_road(50, Car_lane, 670);
    Traffic_light lights[] = {create_light(red, 0, 10, 10)};

    while(1) {
        system("cls");
        for(int i = 0; i < cars_int; i++) {
            cars[i] = drive(cars[i], cars, cars_int, road);
            if (cars[0].position > 500) {
                cars[0].speed_limit = kmt_to_ms(30);
            }
            if (cars[i].ID == -1) {
                cars_int += 1;
            }
        }
        print_cars(cars, cars_int);

        Sleep(500);

    }

    return 0;
}
