#ifndef VEHICLES
#define VEHICLES

Vehicle * Create_allocate_cars(int n, Road roads[], int road_int);
Vehicle * Realloc_cars(Vehicle *ptr, int *cars_int, int new, Road roads[], int road_int);
Vehicle * randomize_cars(Vehicle *cars,int m, int n, Road roads[], int road_int);
Vehicle create_random_vehicle(int id, Road roads[], int road_int);
Vehicle set_car_acceleration(Vehicle car);
Vehicle accelerate_car(Vehicle car, Road roads[], int road_int);
Vehicle drive(Vehicle car, Vehicle *cars, int cars_int, Road roads[], Traffic_light lights[], int lights_int, int road_int);
Vehicle set_safe_distance(Vehicle car);
Vehicle create_vehicle(int id, int dist, double speed_limit_, Road roads[], int road_int);
Vehicle get_nearest_car(Vehicle car, Vehicle *cars, int cars_int, Road roads[], int road_int);
Vehicle check_light(Traffic_light light, Vehicle car, Vehicle closest);
Vehicle state_driving(Vehicle car, Vehicle *cars, int cars_int, Road roads[], Traffic_light lights[], int lights_int, int road_int);
Vehicle state_waiting(Vehicle car, Vehicle *cars, int cars_int, Road roads[], Traffic_light lights[], int lights_int, int road_int);

void print_all_vechile(Vehicle car);
void print_all_vechiles(Vehicle *cars, int cars_int);
void print_vehicles(Vehicle *cars, int cars_int);
void print_vehicle(Vehicle car);

#endif