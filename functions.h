#ifndef FUNCTIONS
#define FUNCTIONS

double rand_uniform(double min, double max);
double kmt_to_ms(double x);
double ms_to_kmt(double x);

void pnt_avg_speed_bridge(Vehicle *cars, int cars_int);
void prompt(double *thru_put, int *iter_speed, int *cars_sec, int *road_int, int *bus_lane_int, int *duration);
void sort_lanes(Vehicle *cars, int cars_int);
void save_to_file(Vehicle *cars, int cars_int, int secs, int duration, int total);

int cmpfunc (const void * a, const void * b);
int check_if_safe_distance(Vehicle car, Vehicle car_in_front);

char* color_to_string(Light_color color);
char* state_to_string(State state);
char* lane_to_string(Lane_type type);

Road create_road(double speed_limit, Lane_type lane, double len);

#endif
