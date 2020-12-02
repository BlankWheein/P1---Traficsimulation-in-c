#ifndef FUNCTIONS
#define FUNCTIONS

Vehicle * Create_allocate_cars(int n);
Vehicle create_random_vehicle(int id);
double rand_uniform(double min, double max);
void print_vehicles(Vehicle *cars, int cars_int);
Vehicle * Realloc_cars(Vehicle *ptr, int *cars_int, int new);
void print_all_vechile(Vehicle car);
void print_all_vechiles(Vehicle *cars, int cars_int);
void print_traffic_light(Traffic_light lights[], int a);


Vehicle set_car_acceleration(Vehicle car);
Vehicle accelerate_car(Vehicle car, Road road);
Vehicle drive(Vehicle car, Vehicle *cars, int cars_int, Road road, Traffic_light lights[], int lights_int);
double kmt_to_ms(double x);
Traffic_light create_light(Light_color color, double position, int timer_green, int timer_red);
Vehicle set_safe_distance(Vehicle car);
int check_if_safe_distance(Vehicle car, Vehicle car_in_front);
void print_vehicle(Vehicle car);
char* color_to_string(Light_color color);
char* state_to_string(State state);
char* type_to_string(Type type);
Traffic_light count_timer(Traffic_light light);
Traffic_light nearest_traffic_light(Vehicle car, Traffic_light lights[], int lights_int);
Vehicle create_vehicle(int id, int dist, double speed_limit_);
Vehicle get_nearest_car(Vehicle car, Vehicle *cars, int cars_int);
Vehicle check_light(Traffic_light light, Vehicle car, Vehicle closest);
Vehicle state_driving(Vehicle car, Vehicle *cars, int cars_int, Road road, Traffic_light lights[], int lights_int);
Vehicle state_waiting(Vehicle car, Vehicle *cars, int cars_int, Road road, Traffic_light lights[], int lights_int);
Road create_road(double speed_limit, Lane_type lane, double len);

#endif
