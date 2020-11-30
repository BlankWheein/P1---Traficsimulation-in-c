#ifndef STRUCTS
#define STRUCTS

typedef enum {green, red, dummy} Light_color;
typedef enum {Bus_lane, Car_lane} Lane_type;
typedef enum {Waiting, Driving, Done, HoldingForRed, Mock} State;
typedef enum {Car, Bus} Type;

typedef struct  {
  Light_color color;
  double position;
  int timer;
  int timer_green;
  int timer_red;
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
  int secs_on_bridge;
  State state;
} Car;

typedef struct {
  double speed_limit;
  Lane_type lane_type; /* Type can be "Bus_lane" or "Car_lane" */
  double length; /* Length of road */
} Road;
#endif
