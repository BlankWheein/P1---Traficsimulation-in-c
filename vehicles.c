#include "vehicles.h"
#include "structs.h"

/**
 * @brief  Used to create a new array with n amount of Vehicles
 * @param  n: The amount of Vehicles in the array
 * @param  roads[]: The Road array (Used to create the cars)
 * @param  road_int: The amount of roads in the roads array
 * @retval Returns an array of Vehicles
 */
Vehicle * Create_allocate_cars(int n, Road roads[], int road_int) {
 Vehicle *cars = malloc(sizeof(Vehicle) * n);
 cars = randomize_cars(cars, 0, n, roads, road_int);
 return cars;
}

/**
 * @brief  Adds n amount of Vehicles to the *ptr array
 * @param  *ptr: The old array of Vehicles
 * @param  *cars_int: The amount of Vehicles in *ptr
 * @param  new: The amount of cars to add to the *ptr array
 * @param  roads[]: The Road array (Used to create the cars)
 * @param  road_int: The amount of roads in the roads array
 * @retval Returns an updated array of Vehicles 
 */
Vehicle * Realloc_cars(Vehicle *ptr, int *cars_int, int new, Road roads[], int road_int) {
  Vehicle *cars = malloc(sizeof(Vehicle) * (*cars_int + new));
  for (int i = 0; i < *cars_int; i++) {
    cars[i] = ptr[i];
  }
  free(ptr);
  int id = *cars_int;
  for (int i = *cars_int; i < *cars_int + new; i++) {
    id += 1;
    cars[i] = create_random_vehicle(id, roads, road_int);
  }
  *cars_int += new;
  return cars;
}

/**
 * @brief Creates random Vehicles from n to n in the *cars array
 * @param  *cars: The array of Vehicles
 * @param  m: The start index value
 * @param  n: The end index value
 * @param  roads[]: The Road array (Used to create the cars)
 * @param  road_int: The amount of roads in the roads array
 * @retval Returns an updated array of Vehicles 
 */
Vehicle * randomize_cars(Vehicle *cars,int m, int n, Road roads[], int road_int) {
  int id = m;
  for (int i = m; i < n; i++) {
    id += 1;
    cars[i] = create_random_vehicle(id, roads, road_int);
  }
  return cars;
}

/**
 * @brief  Creates a new car with the gived id
 * @param  id: The ID to give the Vehicle
 * @param  roads[]: The Road array (Used to create the cars)
 * @param  road_int: The amount of roads in the roads array
 * @retval Returns a new random Vehicle
 */
Vehicle create_random_vehicle(int id, Road roads[], int road_int) {
  double speed_limit = rand_uniform(170, 250);
  Vehicle car = create_vehicle(id, 0, speed_limit, roads, road_int);
  return car;
}

/**
 * @brief  Updates a Vehicles acceleration
 * @param  car: The car to update
 * @retval Returns an updated Vehicle
 */
Vehicle set_car_acceleration(Vehicle car){
  car.acceleration = (2 * (1 - (car.time_driving/car.speed_limit_time)) * (car.speed_limit - 0)) / car.speed_limit_time;
  return car;
}

/**
 * @brief  Updates a Vehicles speed
 * @param  car: the Vehicle to accelerate 
 * @param  roads[]: The Road array (Used to create the cars)
 * @param  road_int: The amount of roads in the roads array
 * @retval Returns an updated Vehicle
 */
Vehicle accelerate_car(Vehicle car, Road roads[], int road_int){
  car.speed += car.acceleration;
  if (car.speed > car.speed_limit) {
    car.speed = car.speed_limit;
  }
  if (car.speed > roads[car.lane].speed_limit) {
    car.speed = roads[car.lane].speed_limit;
  }
  return car;
}

/**
 * @brief  This functions checks if the Vehicle can drive, if so then drive
 * @param  car: The Vehicle to move forward 
 * @param  *cars: The array of Vehicles 
 * @param  cars_int: The amount of Vehicles in *cars
 * @param  roads[]: The Road array (Used to create the cars)
 * @param  lights[]: The array of Traffic of lights on the road
 * @param  lights_int: The amount of traffic lights in the lights array
 * @param  road_int: The amount of roads in the roads array
 * @retval Returns the updated Vehicle
 */
Vehicle drive(Vehicle car, Vehicle *cars, int cars_int, Road roads[], Traffic_light lights[], int lights_int, int road_int) {
  if (car.state == Done) {
    return car;
  }
   if (car.state == Waiting) {
car = state_waiting(car, cars, cars_int, roads, lights, lights_int, road_int);
   } else if(car.state == Driving) {
     car = state_driving(car, cars, cars_int, roads, lights, lights_int, road_int);
   } else if(car.state == HoldingForRed) {
     car = state_driving(car, cars, cars_int, roads, lights, lights_int, road_int);
   }

if (car.position > 0 && car.position < roads[0].length) {
  car.avg_speed_total += car.speed;
}

return car;
}

/**
 * @brief  Updates a Vehicles Safe distance
 * @param  car: The Vehicle to update safe distance 
 * @retval Returns an update Vehicle
 */
Vehicle set_safe_distance(Vehicle car) {
    car.safe_distance = (ms_to_kmt(car.speed) / 2) + 1;
    return car;
}

/**
 * @brief  Creates a new Vehicle
 * @param  id: The ID of the vehicle
 * @param  dist: The Position where to spawn the Vehicle
 * @param  speed_limit_: The Speed limit of the Vehicle (Busses have half)
 * @param  roads[]: The Road array (Used to create the cars)
 * @param  road_int: The amount of roads in the roads array
 * @retval Returns a new vehicle
 */
Vehicle create_vehicle(int id, int dist, double speed_limit_, Road roads[], int road_int) {
    Lane_type type;
    double chance = rand_uniform(0, 100);
    if (chance <= 92.98) {
      type = Car;
    } else if (chance > 92.98 && chance < 93.68) {
      type = PlusBus;
    } else {
      type = Bus;
    }
    int canbeplusbus = 0;
    for (int i = 0; i < road_int; i++) {
      if (roads[i].lane_type == PlusBus) {
        canbeplusbus = 1;
      }
    }

    if (canbeplusbus == 0 && type == PlusBus) {
      type = Bus;
    }
    
    int lane;
    int waiting = 0;
    do {
    lane = rand() % road_int;
    if (roads[lane].lane_type == type) {
      waiting = 1;
    } else if(roads[lane].lane_type == Car && type == Bus) {
      waiting = 1;
    }
    } while (!waiting);

    double speed = 0;
    double position = dist;
    double speed_limit;
    if (type == Car) {
      speed_limit = kmt_to_ms(speed_limit_);
    } else {
      speed_limit = kmt_to_ms(speed_limit_ / 2);
    }
    
    double speed_limit_time = 65.5;
    double time_driving = 0;
    double acceleration = 0;
    double safe_distance = 1;
    int ID = id;
    int secs_on_bridge = 0;
    State state = Waiting;
    int time_waited_for_green_light = 0;

    Vehicle car = {speed, position, speed_limit, speed_limit_time, time_driving, acceleration, safe_distance, ID, lane, secs_on_bridge, state, type, time_waited_for_green_light};
    return car;
}

/**
 * @brief  Finds the neares Vehicle to the car thats infront of it
 * @param  car: The main Vehicle
 * @param  *cars: The Array of Vehicles
 * @param  cars_int: The amount of Vehicles in *cars
 * @param  roads[]: The Road array (Used to create the cars)
 * @param  road_int: The amount of roads in the roads array
 * @retval Returns the closest Vehicle to the car
 */
Vehicle get_nearest_car(Vehicle car, Vehicle *cars, int cars_int, Road roads[], int road_int) {
    Vehicle closest = create_vehicle(-1, 99999999, 160, roads, road_int);
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

/**
 * @brief  Checks if a Vehicle is too close to a red light
 * @param  light: The Traffic light you want to check 
 * @param  car: The Vehicle you want to check
 * @param  closest: The closest Vehicle
 * @retval returns the updated Vehicle
 */
Vehicle check_light(Traffic_light light, Vehicle car, Vehicle closest) {
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
      car.time_waited_for_green_light += 1; 
      car.state = HoldingForRed;
    }
}
  return car;
}