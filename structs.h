#ifndef STRUCTS
#define STRUCTS

typedef enum {green, red, dummy} Light_color;
typedef enum {Bus_lane, Car_lane} Lane_type;

typedef struct  {
  Light_color color;
  double position;
  int timer, timer_green, timer_red;
} Traffic_light;

typedef struct {
  double speed;
  double breaks;
  double position;  /* så du ved hvor bilen er på broen */
  double length;
  double speed_limit;
  double speed_limit_time;
  double time_driving;
  double acceleration;
  double safe_distance;
  int ID;
  int lane;
} Car;

typedef struct {
  double speed_limit;
  Lane_type lane_type; /* Type can be "Bus_lane" or "Car_lane" */
  double len; /* Length of road */
} Road;

#endif
