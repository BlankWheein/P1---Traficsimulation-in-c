#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "functions.c"

int main(void) {

    Traffic_light light = {
        red, 0, 0, 10, 5
    };
while (1)
{
    light = count_timer(light);
    Sleep(200);
    printf("%s %lf", color_to_string(light.color), light.timer);
}


return 0;
}
