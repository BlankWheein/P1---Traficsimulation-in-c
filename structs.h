
typedef enum {green, yellow, red} Light_color;
typedef enum {Bus, Car} Lane_type;

typedef struct Traffic_light {
  Light_color light_color;
  double position;
} Traffic_light;

typedef struct Car {
  double speed;
  double breaks;
  double location;  /* så du ved hvor bilen er på broen */
  double car_length;
  double speed_limit;
  double acceleration;
  double safe_distance;
} Car;

typedef struct {
Lane_type lane_type; /* Type can be "Bus" or "Car" */
double len; /* Length of road */
} Road;