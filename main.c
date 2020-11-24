#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "functions.c"

int main(void) {

    Traffic_light light = {red, 0, 0, 10, 5};
    Traffic_light light2 = {red, 0, 0, 100, 20};
    Traffic_light lights[] = {light, light2};
while (1)
{
    for (int i = 0; i < 2; i++) {
      lights[i] = count_timer(lights[i]);
      printf("%s %d\n", color_to_string(lights[i].color), lights[i].timer);
    }
    printf("\n");
    Sleep(500);

}


return 0;
}
