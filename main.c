#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "structs.h"
#include "functions.c"

int main(void) {
    Car cars[] = {create_car(1,0, 150), create_car(2,0, 160), create_car(3,0, 120), create_car(4,0, 160), create_car(5,0, 160), create_car(6,0, 160)};
    int cars_int = 6;
    int lights_int = 2;
    Road road = create_road(50, Car_lane, 670);
    Traffic_light lights[] = {create_light(red, 300, 10, 100), create_light(red, 1, 25, 25)};
    int done = 0;

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

    return 0;
}
