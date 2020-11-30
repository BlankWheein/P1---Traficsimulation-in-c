#ifndef FUNCTIONS
#define FUNCTIONS

Car * Create_allocate_cars(int n);
Car create_random_car(int id);
double rand_uniform(double min, double max);
void print_cars(Car *cars, int cars_int);
Car * Realloc_cars(Car *ptr, int *cars_int, int new);
void print_all_car(Car car);
void print_all_cars(Car *cars, int cars_int);


Car set_car_acceleration(Car car);
Car accelerate_car(Car car, Road road);
Car drive(Car car, Car *cars, int cars_int, Road road, Traffic_light lights[], int lights_int);
double kmt_to_ms(double x);
Traffic_light create_light(Light_color color, double position, int timer_green, int timer_red);
Car set_safe_distance(Car car);
int check_if_safe_distance(Car car, Car car_in_front);
void print_car(Car car);
char* color_to_string(Light_color color);
char* state_to_string(State state);
Traffic_light count_timer(Traffic_light light);
Traffic_light nearest_traffic_light(Car car, Traffic_light lights[], int lights_int);
Car create_car(int id, int dist, double speed_limit_);
Car get_nearest_car(Car car, Car *cars, int cars_int);
Car check_light(Traffic_light light, Car car, Car closest);
Car state_driving(Car car, Car *cars, int cars_int, Road road, Traffic_light lights[], int lights_int);
Car state_waiting(Car car, Car *cars, int cars_int, Road road, Traffic_light lights[], int lights_int);
Road create_road(double speed_limit, Lane_type lane, double len);

#endif
