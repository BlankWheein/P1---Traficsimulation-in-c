#include "structs.h"
Car accelerate_car(Car car, Road road){
  car.speed += car.acceleration;
  if (car.speed > car.speed_limit) {
    car.speed = car.speed_limit;
  }
  if (car.speed > road.speed_limit) {
    car.speed = road.speed_limit;
  }
  return car;
}

void print_car(Car car) {
printf("Car(%d): Speed: %.2lf, breaks: %.2lf, location: %.2lf, lenght: %.2lf, speed_limit: %.1lf, acceleration: %.3lf, safe_distance: %.2lf\n", car.ID, car.speed, car.breaks, car.location, car.length, car.speed_limit, car.acceleration, car.safe_distance);


}

int check_light(Traffic_light light) {
  int drive = light.light_color == green ? 1 : 0;
  return drive;
}
