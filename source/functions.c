
/**
 * @brief  Sets config values for the program
 * @param  *thru_put: The throughput of the program
 * @param  *iter_speed: The iteration speed of the program
 * @param  *cars_sec: The amount of time between spawning cars
 * @param  *road_int: The amount of roads
 * @param  *bus_lane_int: The amount of plusbus lanes
 * @param  *duration: The amount of minutes the program runs for
 * @retval None
 */
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

/**
 * @brief  Prints the avarage speed of all Vehicles on the bridge
 * @param  *cars: The array of cars
 * @param  cars_int: The amount of cars in the cars array
 * @retval None
 */
void pnt_avg_speed_bridge(Vehicle *cars, int cars_int){
  double collected_speed = 0.0, avg_speed = 0.0;
  int vehicles = 0;
  for (int i = 0; i < cars_int; i++){
    if (cars[i].state != Done) {
       collected_speed += cars[i].speed;
       vehicles += 1;
    }
    
  }

  avg_speed = ms_to_kmt(collected_speed / (double) vehicles);
  printf("AVERAGE SPEED ON BRIDGE: %.2lfkm/t\n", avg_speed);
}

/**
 * @brief  Converts x from m/s to Km/h
 * @param  x:  the value to convers
 * @retval returns a value in Km/h
 */
double ms_to_kmt(double x){
  return x * 3.6;
}

/**
 * @brief  Converts x from Km/h to m/s
 * @param  x:  the value to convers
 * @retval returns a value in m/s
 */
double kmt_to_ms(double x){
  return x / 3.6;
}

/**
 * @brief  Checks if the Vehicle in front is within the safe distance of the vehicle
 * @param  car: The car to check
 * @param  car_in_front: The vehicle infront of the car
 * @retval 
 */
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





/**
 * @brief  Converts the type Light_color to string
 * @param  color: The variable to convert
 * @retval returns the Light_color in a string
 */
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

/**
 * @brief  Converts the type Lane_type to string
 * @param  type: The variable to convert
 * @retval returns the Lane_type in a string
 */
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

/**
 * @brief  Converts the type State to string
 * @param  state: The variable to convert
 * @retval returns the State in a string
 */
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


/**
 * @brief  Creates a road
 * @param  speed_limit: The speed limit on the road
 * @param  lane: What type of lane
 * @param  len: The length of the road
 * @retval Returns a new road
 */
Road create_road(double speed_limit, Lane_type lane, double len) {
    Road road = {kmt_to_ms(speed_limit), lane, len};
    return road;
}


/**
 * @brief  Compares a to b
 * @param  a: value 1 of array
 * @param  b: value 2 of array
 * @retval returns an int
 */
int cmpfunc (const void * a, const void * b) {
   Vehicle l = *(const Vehicle *)a;
   Vehicle r = *(const Vehicle *)b;
   if(l.lane == r.lane) {
     return l.ID - r.ID;
   }
   return l.lane - r.lane;
}

/**
 * @brief  Saves variables to a csv formatted file
 * @param  *cars: The array of Vehicles
 * @param  cars_int: The amount of vehicles in cars
 * @param  secs: The time it took to run the simulation
 * @param  duration: The target time of simulation
 * @param  total: The total amount of Vehicles
 * @retval None
 */
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

/**
 * @brief  Sorts the cars array by lane and prints it with more data
 * @param  *cars: The array of Vehicles
 * @param  cars_int: The amount Vehicles in cars
 * @retval None
 */
void sort_lanes(Vehicle *cars, int cars_int){
  Vehicle *print_cars = malloc(sizeof(Vehicle) * cars_int);
  for (int i = 0; i < cars_int; i++){
    print_cars[i] = cars[i];
  }
  qsort(print_cars, cars_int, sizeof(Vehicle), cmpfunc);
  print_vehicles(print_cars, cars_int);
  free(print_cars);
}

/**
 * @brief  Sorts the cars array by lane and prints it with less data
 * @param  *cars: The array of Vehicles
 * @param  cars_int: The amount Vehicles in cars
 * @retval None
 */
void sort_lanes_done(Vehicle *cars, int cars_int){
  Vehicle *print_cars = malloc(sizeof(Vehicle) * cars_int);
  for (int i = 0; i < cars_int; i++){
    print_cars[i] = cars[i];
  }
  qsort(print_cars, cars_int, sizeof(Vehicle), cmpfunc);
  print_all_vechiles(print_cars, cars_int);
  free(print_cars);
}

/**
 * @brief  Creates a random value between min and max
 * @param  min: the min value
 * @param  max: the max value
 * @retval returns a random value
 */
double rand_uniform(double min, double max){
  return (max - min) * ( (double)rand() / (double)RAND_MAX ) + min;
}
