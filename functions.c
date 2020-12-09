#include "functions.h"
#include "structs.h"




Vehicle state_waiting(Vehicle car, Vehicle *cars, int cars_int, Road roads[], Traffic_light lights[], int lights_int, int road_int) {
  Vehicle closest = get_nearest_car(car, cars, cars_int, roads, road_int);
  
  int is_safe = check_if_safe_distance(car, closest);
  if (is_safe == 1) {
   car.state = Driving;
   car = state_driving(car, cars, cars_int, roads, lights, lights_int, road_int);
 }

return car;
}

Vehicle state_driving(Vehicle car, Vehicle *cars, int cars_int, Road roads[], Traffic_light lights[], int lights_int, int road_int) {
  car = set_car_acceleration(car);
  Vehicle closest = get_nearest_car(car, cars, cars_int, roads, road_int);
  car = set_safe_distance(car);
  Traffic_light light = nearest_traffic_light(car, lights, lights_int);



  int is_safe = check_if_safe_distance(car, closest);

  if (is_safe == 1) {
      car = accelerate_car(car, roads, road_int);
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
  if (car.position > roads[car.lane].length) {
      car.state = Done;
  }
  return car;
}

void prompt(double *thru_put, int *iter_speed, int *cars_sec, int *road_int, int *bus_lane_int, int *duration){
  do{
    system("cls");
    printf("\nWhat throughput do you want per hour? ");
    scanf(" %lf", thru_put);
  }while(*thru_put < 0);

  do{
    system("cls");
    printf("\nWhat iteration speed do u want? (1: slow, 50: fast, 9999999: Really fast) ");
    scanf(" %d", iter_speed);
  }while(*iter_speed < 0);

  do{
    system("cls");
    printf("\nWhat interval between spawning cars? ");
    scanf(" %d", cars_sec);
  }while(*cars_sec < 0);

  do{
    system("cls");
    printf("\nHow many lanes in total? ");
    scanf(" %d", road_int);
  }while(*road_int < 1);

  do{
    system("cls");
    printf("\nHow many lanes should be PlusBus lanes? (Rest will be Car lanes) ");
    scanf(" %d", bus_lane_int);
  }while(*bus_lane_int < 0);
  
  do{
    system("cls");
    printf("\nHow many minutes do you want the simulation to run for? ");
    scanf(" %d", duration);
  }while(*duration < 0);

}

void pnt_avg_speed_bridge(Vehicle *cars, int cars_int){
  double collected_speed = 0.0, avg_speed = 0.0;
  for (int i = 0; i < cars_int; i++){
    collected_speed += cars[i].speed;
  }

  avg_speed = ms_to_kmt(collected_speed / (double) cars_int);
  printf("AVERAGE SPEED: %.2lfkm/t\n", avg_speed);
}

double ms_to_kmt(double x){
  return x * 3.6;
}


double kmt_to_ms(double x){
  return x / 3.6;
}


int check_if_safe_distance(Vehicle car, Vehicle car_in_front) {
    if (car_in_front.state == Mock) {
      return 1;
    }

    double delta = car_in_front.position - car.position -2.2;
    if (delta > car.safe_distance)
    {
      return 1;
    }
    return 0;
}
void print_vehicle(Vehicle car) {
  if (car.state != Done) {
    printf("Vehicle(%d:%s): Speed: %.3lf(%.1lf), position: %.2lf, secs_on_bridge: %d, speed_limit: %.1lf, acceleration: %.3lf, safe_distance: %.2lf, Lane: %d, State: %s, Time_waited: %d\n", car.ID, lane_to_string(car.type),car.speed, ms_to_kmt(car.speed), car.position, car.secs_on_bridge, ms_to_kmt(car.speed_limit), car.acceleration, car.safe_distance, car.lane, state_to_string(car.state), car.time_waited_for_green_light);

  }
    }

void print_all_vechile(Vehicle car) {
    printf("Vehicle(%5d:%s): Lane: %2d, secs_on_bridge: %3d, speed_limit: %4.1lf, avg_speed: %3.2lf, Time waited on green light: %3d\n", car.ID,lane_to_string(car.type), car.lane, car.secs_on_bridge, ms_to_kmt(car.speed_limit), car.avg_speed, car.time_waited_for_green_light);
}

void print_vehicles(Vehicle *cars, int cars_int) {
    int lane = 0;
    for (int i = 0; i < cars_int; i++) {
      if (cars[i].lane > lane) {
        printf("\n\n");
        lane = cars[i].lane;
      }
        print_vehicle(cars[i]);
    }
}

void print_all_vechiles(Vehicle *cars, int cars_int) {
int lane = 0;
    for (int i = 0; i < cars_int; i++) {
      if (cars[i].lane > lane) {
        printf("\n\n");
        lane = cars[i].lane;
      }
        print_all_vechile(cars[i]);
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
  return "Not Defined";
    break;
  }
}

char* lane_to_string(Lane_type type) {
  switch (type)
  {
  case Car:
    return "Car";
    break;
  case PlusBus:
    return "Plus Bus";
    break;
  case Bus:
    return "Bus";
    break;
  default:
    return "Not Defined";
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
  return "Not Defined";
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

Traffic_light nearest_traffic_light(Vehicle car, Traffic_light lights[], int lights_int) {
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


int cmpfunc (const void * a, const void * b) {
   Vehicle l = *(const Vehicle *)a;
   Vehicle r = *(const Vehicle *)b;
   if(l.lane == r.lane) {
     return l.ID - r.ID;
   }
   return l.lane - r.lane;
}

void save_to_file(Vehicle *cars, int cars_int, int secs, int duration, int total) {
  FILE * fp;
   int i;
   fp = fopen ("data.csv","w+");
   fprintf(fp,"Duration of simulation, %d,Time stopped spawning cars, %d, Total number of cars:,%d\n", secs, duration, total);
   fprintf(fp, "ID, TYPE, LANE, SECS ON BRIDGE, AVG SPEED, TIME WAITED FOR GREEN\n");
   for(i = 0; i < cars_int; i++){
       fprintf(fp, "%d,%s,%d,%d,%.3lf,%d\n", cars[i].ID,lane_to_string(cars[i].type), cars[i].lane +1, cars[i].secs_on_bridge, cars[i].avg_speed, cars[i].time_waited_for_green_light);
   }
  fclose (fp);
}

void sort_lanes(Vehicle *cars, int cars_int){
  Vehicle *print_cars = malloc(sizeof(Vehicle) * cars_int);
  for (int i = 0; i < cars_int; i++){
    print_cars[i] = cars[i];
  }
  qsort(print_cars, cars_int, sizeof(Vehicle), cmpfunc);
  print_vehicles(print_cars, cars_int);
  free(print_cars);
}

void sort_lanes_done(Vehicle *cars, int cars_int){
  Vehicle *print_cars = malloc(sizeof(Vehicle) * cars_int);
  for (int i = 0; i < cars_int; i++){
    print_cars[i] = cars[i];
  }
  qsort(print_cars, cars_int, sizeof(Vehicle), cmpfunc);
  print_all_vechiles(print_cars, cars_int);
  free(print_cars);
}





double rand_uniform(double min, double max){
  return (max - min) * ( (double)rand() / (double)RAND_MAX ) + min;
}

void print_traffic_light(Traffic_light lights[], int a) {
  for (int i = 0; i < a; i++) {
    if (lights[i].position > 1) {
      if (color_to_string(lights[i].color) == "Red") {
      printf("Position: %.0lf Color: %s   Timer: %d/%d\n", lights[i].position, color_to_string(lights[i].color), lights[i].timer, lights[i].timer_red);
      }
      else {
      printf("Position: %.0lf Color: %s Timer: %d/%d\n", lights[i].position, color_to_string(lights[i].color), lights[i].timer, lights[i].timer_green);
      }
    }
    else {
      if (color_to_string(lights[i].color) == "Red") {
      printf("Position:   %.0lf Color: %s   Timer: %d/%d\n", lights[i].position, color_to_string(lights[i].color), lights[i].timer, lights[i].timer_red);
      }
      else {
      printf("Position:   %.0lf Color: %s Timer: %d/%d\n", lights[i].position, color_to_string(lights[i].color), lights[i].timer, lights[i].timer_green);
      }
    }
  }
}
