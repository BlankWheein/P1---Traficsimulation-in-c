#ifndef FUNCTIONS
#define FUNCTIONS

double rand_uniform(double min, double max);
void print_vehicles(Vehicle *cars, int cars_int);
double kmt_to_ms(double x);
double ms_to_kmt(double x);
void print_all_vechile(Vehicle car);
void print_all_vechiles(Vehicle *cars, int cars_int);

void pnt_avg_speed_bridge(Vehicle *cars, int cars_int);
void prompt(double *thru_put, int *iter_speed, int *cars_sec, int *road_int, int *bus_lane_int, int *duration);
int cmpfunc (const void * a, const void * b);
void sort_lanes(Vehicle *cars, int cars_int);
void save_to_file(Vehicle *cars, int cars_int, int secs, int duration, int total);

Traffic_light create_light(Light_color color, double position, int timer_green, int timer_red);
int check_if_safe_distance(Vehicle car, Vehicle car_in_front);
void print_vehicle(Vehicle car);
char* color_to_string(Light_color color);
char* state_to_string(State state);
char* lane_to_string(Lane_type type);
Traffic_light count_timer(Traffic_light light);
Traffic_light nearest_traffic_light(Vehicle car, Traffic_light lights[], int lights_int);
Road create_road(double speed_limit, Lane_type lane, double len);

#endif
