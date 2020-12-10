#ifndef LIGHTS
#define LIGHTS

Traffic_light count_timer(Traffic_light light);
Traffic_light nearest_traffic_light(Vehicle car, Traffic_light lights[], int lights_int);
Traffic_light create_light(Light_color color, double position, int timer_green, int timer_red);
void print_traffic_light(Traffic_light lights[], int a);
#endif