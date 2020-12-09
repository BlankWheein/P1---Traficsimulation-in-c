#ifndef FUNCTIONS
#define FUNCTIONS

void prompt(double *thru_put, int *iter_speed, int *cars_sec);
void sort_lanes(Vehicle *cars, int cars_int);
void save_to_file(Vehicle *cars, int cars_int, int secs, int duration);
int cmpfunc (const void * a, const void * b);

double rand_uniform(double min, double max);
void print_vehicles(Vehicle *cars, int cars_int);
double kmt_to_ms(double x);
double ms_to_kmt(double x);
char* color_to_string(Light_color color);
char* state_to_string(State state);
char* lane_to_string(Lane_type type);

void print_vehicle(Vehicle car);
void print_all_vechile(Vehicle car);
void pnt_avg_speed_bridge(Vehicle *cars, int cars_int);
void print_all_vechiles(Vehicle *cars, int cars_int);

int check_if_safe_distance(Vehicle car, Vehicle car_in_front);



Vehicle * Create_allocate_cars(int n, Road roads[]);
Vehicle create_random_vehicle(int id, Road roads[]);
Vehicle create_vehicle(int id, int dist, double speed_limit_, Road roads[]);
Vehicle * Realloc_cars(Vehicle *ptr, int *cars_int, int new, Road roads[]);
Vehicle * randomize_cars(Vehicle *cars,int m, int n, Road roads[]);
Vehicle set_car_acceleration(Vehicle car);
Vehicle accelerate_car(Vehicle car, Road roads[]);
Vehicle set_safe_distance(Vehicle car);
Vehicle state_driving(Vehicle car, Vehicle *cars, int cars_int, Road roads[], Traffic_light lights[], int lights_int);
Vehicle state_waiting(Vehicle car, Vehicle *cars, int cars_int, Road roads[], Traffic_light lights[], int lights_int);
Vehicle drive(Vehicle car, Vehicle *cars, int cars_int, Road roads[], Traffic_light lights[], int lights_int);
Vehicle get_nearest_car(Vehicle car, Vehicle *cars, int cars_int, Road roads[]);
Vehicle check_light(Traffic_light light, Vehicle car, Vehicle closest);

Traffic_light create_light(Light_color color, double position, int timer_green, int timer_red);
Traffic_light count_timer(Traffic_light light);
Traffic_light nearest_traffic_light(Vehicle car, Traffic_light lights[], int lights_int);

Road create_road(double speed_limit, Lane_type lane, double len);

#endif
