#include "functions.h"
#include "structs.h"
Car set_car_acceleration(Car car){
  car.acceleration = (2 * (1 - (car.time_driving/car.speed_limit_time)) * (car.speed_limit - 0)) / car.speed_limit_time;
  return car;
}

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

Car state_waiting(Car car, Car *cars, int cars_int, Road road, Traffic_light lights[], int lights_int) {
  Car closest = get_nearest_car(car, cars, cars_int);
  int is_safe = check_if_safe_distance(car, closest);
  if (is_safe == 1) {
   car.state = Driving;
   car = state_driving(car, cars, cars_int, road, lights, lights_int);
 }
return car;
}


Car state_driving(Car car, Car *cars, int cars_int, Road road, Traffic_light lights[], int lights_int) {
  car = set_car_acceleration(car);
  Car closest = get_nearest_car(car, cars, cars_int);
  car = set_safe_distance(car);
  Traffic_light light = nearest_traffic_light(car, lights, lights_int);



  int is_safe = check_if_safe_distance(car, closest);

  if (is_safe == 1) {
      car = accelerate_car(car, road);
      if (car.state == HoldingForRed) {
        car.state = Driving;
      }
  }

  if (is_safe == 0) {

    if (closest.state == Mock) {
      return car;
    }
      if (car.speed > closest.position - car.position) {
        car.speed = closest.speed;
      }

       // Needs a check if car will end up in other car, if so deaccelerate
  }

  car = check_light(light, car, closest);
  car.position += car.speed;
  if (car.position > 0) {
      car.secs_on_bridge += 1;
  }
  if (car.position > road.length) {
      car.state = Done;
  }
  return car;
}


Car drive(Car car, Car *cars, int cars_int, Road road, Traffic_light lights[], int lights_int) {
   if (car.state == Waiting) {
car = state_waiting(car, cars, cars_int, road, lights, lights_int);
   } else if(car.state == Driving) {
     car = state_driving(car, cars, cars_int, road, lights, lights_int);
   } else if(car.state == HoldingForRed) {
     car = state_driving(car, cars, cars_int, road, lights, lights_int);
   }
 return car;
}

double ms_to_kmt(double x){
  return x * 3.6;
}


double kmt_to_ms(double x){
  return x / 3.6;
}
Car set_safe_distance(Car car) {
    car.safe_distance = (ms_to_kmt(car.speed) / 2) + 1;
    return car;
}

int check_if_safe_distance(Car car, Car car_in_front) {
    if (car_in_front.state == Mock) {
      return 1;
    }

    double delta = car_in_front.position - car.position -1;
    if (delta > car.safe_distance)
    {
      return 1;
    }
    return 0;
}
void print_car(Car car) {
  if (car.state != Done) {
    if (car.ID % 2 == 1) {
      printf("\n");
    }
    printf("Car(%d): Speed: %.3lf(%.1lf), position: %.2lf, secs_on_bridge: %d, speed_limit: %.1lf, acceleration: %.3lf, safe_distance: %.2lf, State: %s\n", car.ID, car.speed, ms_to_kmt(car.speed), car.position, car.secs_on_bridge, ms_to_kmt(car.speed_limit), car.acceleration, car.safe_distance, state_to_string(car.state));

  }
    }

void print_all_car(Car car) {
        if (car.ID % 2 == 1) {
          printf("\n");
        }
        printf("Car(%d): Speed: %.3lf(%.1lf), position: %.2lf, secs_on_bridge: %d, speed_limit: %.1lf, acceleration: %.3lf, safe_distance: %.2lf, State: %s\n", car.ID, car.speed, ms_to_kmt(car.speed), car.position, car.secs_on_bridge, ms_to_kmt(car.speed_limit), car.acceleration, car.safe_distance, state_to_string(car.state));
}

void print_cars(Car *cars, int cars_int) {

    for (int i = 0; i < cars_int; i++) {
        print_car(cars[i]);
    }
}

void print_all_cars(Car *cars, int cars_int) {

    for (int i = 0; i < cars_int; i++) {
        print_all_car(cars[i]);
    }
}

char* color_to_string(Light_color color) {
  switch (color)
  {
  case red:
    return "Red";
    break;
  case green:
    return "Green";
    break;
  case dummy:
    return "Dummy";
    break;
  default:
    break;
  }
}

char* state_to_string(State state) {
  switch (state)
  {
  case Waiting:
    return "Waiting";
    break;
  case Driving:
    return "Driving";
    break;
  case Done:
    return "Done";
    break;
    case HoldingForRed:
      return "Holding For Red";
      break;
    case Mock:
      return "Mock";
      break;
  default:
    break;
  }
}

Road create_road(double speed_limit, Lane_type lane, double len) {
    Road road = {kmt_to_ms(speed_limit), lane, len};
    return road;
}

Traffic_light create_light(Light_color color, double position, int timer_green, int timer_red) {
    Traffic_light light = {color, position, 0, timer_green, timer_red};
    return light;
}

Traffic_light count_timer(Traffic_light light) {
  light.timer += 1;
    if (light.color == green && light.timer == light.timer_green)
    {
      light.color = red;
      light.timer = 0;
    }
    else if (light.color == red && light.timer == light.timer_red)
    {
      light.color = green;
      light.timer = 0;
    }
  return light;
}

Traffic_light nearest_traffic_light(Car car, Traffic_light lights[], int lights_int) {
  int i;
  Traffic_light nearest_light = {dummy, 99999, 0, 0, 0};
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

Car create_car(int id, int dist, double speed_limit_) {
    double speed = 0;
    double breaks = 0;
    double position = dist;
    double length = 0;
    double speed_limit = kmt_to_ms(speed_limit_);
    double speed_limit_time = 65.5;
    double time_driving = 0;
    double acceleration = 0;
    double safe_distance = 1;
    int ID = id;
    int lane = 1;
    int secs_on_bridge = 0;
    State state = Waiting;
    Car car = {speed, breaks, position, length, speed_limit, speed_limit_time, time_driving, acceleration, safe_distance, ID, lane, secs_on_bridge, state};
    return car;
}

Car get_nearest_car(Car car, Car *cars, int cars_int) {
    Car closest = create_car(-1, 99999999, 160);
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

Car create_random_car(int id) {
  double speed_limit = rand_uniform(170, 250);
  Car car = create_car(id, 0, speed_limit);
  return car;
}

Car * randomize_cars(Car *cars,int m, int n) {
  int id = m;
  for (int i = m; i < n; i++) {
    id += 1;
    cars[i] = create_random_car(id);
  }
  return cars;
}

Car * Create_allocate_cars(int n) {
 Car *cars = malloc(sizeof(Car) * n);
 cars = randomize_cars(cars, 0, n);
 return cars;
}

Car * Realloc_cars(Car *ptr, int *cars_int, int new) {
  Car *cars = malloc(sizeof(Car) * (*cars_int + new));
  for (int i = 0; i < *cars_int; i++) {
    cars[i] = ptr[i];
  }
  free(ptr);
  int id = *cars_int;
  for (int i = *cars_int; i < *cars_int + new; i++) {
    id += 1;
    cars[i] = create_random_car(id);
  }
  *cars_int += new;
  return cars;
}

Car check_light(Traffic_light light, Car car, Car closest) {
  if (light.color == red) {
    if (light.position - car.position < 30) {
      car.speed = 5;
      if (closest.position - car.position < 10) {
        car.speed = closest.position - car.position - 1;
        if (car.speed < 0) {
          car.speed = 0;
        }
      }
    }
    if (light.position - car.position < 10) {
      car.speed = 0;
    }
    if (car.speed == 0 && car.position > 1) {
      car.state = HoldingForRed;
    }
}
  return car;
}

double rand_uniform(double min, double max){
  return (max - min) * ( (double)rand() / (double)RAND_MAX ) + min;
}
