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

Car set_safe_distance(Car car) {
    car.safe_distance = (ms_to_kmt(car.speed) / 2) + 1;
    return car;
}

int check_safe_distance(Car car, Car car_in_front) {
    double delta = car_in_front.position - car.position;
    if (delta > car.safe_distance)
    {
      return 0;
    }
    return 1;
}

Car drive(Car car, cars[], int cars_int, Road road) {
    car = accelerate_car(car, road);
    Car closest = get_nearest_car(car, cars, cars_int);

    return car;
}
void print_cars(Car cars[], int cars_int) {
    for (int i = 0; i < cars_int; i++) {
        print_car(cars[i]);
    }
}
Traffic_light nearest_traffic_light(Car car, Traffic_light lights[], int lights_int) {
  int i;
  Traffic_light nearest_light = {dummy, 99999};
  if (lights_int < 1) {
    return nearest_light;
  }
  for (i = 0; i < lights_int; i++) { /* remember variable for number of lights */
    if (lights[i].position > car.position && nearest_light.position > lights[i].position) {
      nearest_light = lights[i];
    }
  }
  return nearest_light;
}
void print_car(Car car) {
    printf("Car(%d): Speed: %.1lf, breaks: %.1lf, position: %.2lf, lenght: %.2lf, speed_limit: %.1lf, acceleration: %.3lf, safe_distance: %.2lf\n", car.ID, car.speed, car.breaks, car.position, car.length, car.speed_limit, car.acceleration, car.safe_distance);
}
Car create_car(int id, int dist) {
    Car car = {0, 0, dist, 0, 50, 4, 10, id, 1};
    return car;
}

Car get_nearest_car(Car car, Car cars[], int cars_int) {
    Car closest = create_car(-1, 99999999);
    if (cars_int < 1) {
        return closest;
    }
    for (int i = 0; i < cars_int; i++) {
        if (car.position < cars[i].position && cars[i].position < closest.position && car.lane == cars[i].lane) {
            closest = cars[i];
        }
    }
    return closest;
}

int check_light(Traffic_light light) {
  int drive = light.light_color == green ? 1 : 0;
  return drive;
}

double ms_to_kmt(double x){
  return x * 3.6;
}

double kmt_to_ms(double x){
  return x / 3.6;
}