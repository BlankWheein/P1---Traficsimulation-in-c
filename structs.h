
typedef enum {green, yellow, red} Light_color;
typedef enum {Bus_lane, Car_lane} Lane_type;

typedef struct  {
  Light_color light_color;
  double position;
} Traffic_light;

typedef struct {
  double speed;
  double breaks;
  double location;  /* så du ved hvor bilen er på broen */
  double car_length;
  double speed_limit;
  double acceleration;
  double safe_distance;
} Car;

typedef struct {
Lane_type lane_type; /* Type can be "Bus_lane" or "Car_lane" */
double len; /* Length of road */
} Road;