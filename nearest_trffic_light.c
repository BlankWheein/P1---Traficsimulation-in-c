#include <stdio.h>
#include "structs.h"

Traffic_light get_nearest_traffic_light(Car car, Traffic_light *lights[n]) {
  Traffic_light nearest_light = *lights[0];
  for (i = 0; i <= n; i++) {
    if (*lights[i + 1] > *lights[i])
      nearest_light = *lights[i + 1];
  }

}

int main(void) {
  Traffic_light Traffic_light1 = {green, 3};
  Traffic_light Traffic_light2 = {red, 9};

  Car car = {1, 1, 2, 1, 1, 1, 1};
  Traffic_light lights = {Traffic_light1, Traffic_light2};
  Traffic_light x = get_nearest_traffic_light(car, lights);
  printf("This is the neareast traffic light: %lf", x.position);
}
