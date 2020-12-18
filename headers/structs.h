#ifndef STRUCTS
#define STRUCTS

/*
  The Enumeration of Light Color 
*/
typedef enum {green, /**< When the light is Green */
              red,   /**< When the light is Red */
              dummy  /**< When the light is a mock light. This means the Vehicles will ignore this light (This is used to Check for the nearest Traffic light) */
} Light_color;

/*
  The Enumeration of Lane_type
*/
typedef enum {PlusBus, /**< When the Vehicle is a Plusbus */
              Car,     /**< When the Vehicle is a Car */
              Bus      /**< When the Vehicle is a Bus */
} Lane_type;

/*
  The Enumeration of State
*/
typedef enum {Waiting,       /**< The state of the Vehicle if it is waiting to get on the bridge */
              Driving,       /**< The state of the Vehicle if it is driving on the bridge */
              Done,          /**< The state of the Vehicle if it is done driving on the bridge */
              HoldingForRed, /**< The state of the Vehicle if it is holding for red on the bridge */
              Mock           /**< This is a mock Vehicle. This means the Vehicles will ignore this Vehicle (This is used for getting the nearest Vehicle)*/
} State;



/*
  A structure to represent Traffic lights 
*/
typedef struct  {
  /*@{*/
  Light_color color; /**< The color of the Traffic light */
  double position;   /**< The position of the traffic light on the road */
  int timer;         /**< The current Traffic light timer (This counts from 0 to either timer_green or timer_red) */
  int timer_green;   /**< How long the Traffic light should stay Green (In seconds) */
  int timer_red;     /**< How long the Traffic light should stay Red (In seconds) */
} Traffic_light;

/*
  A structure to represent A Vehicle 
*/
typedef struct {
  double speed;                      /**< The current speed of the Vehicle (In M/s)*/
  double position;                   /**< The current position of the Vehicle (This goes from 0 to the distance of the road) */
  double speed_limit;                /**< The Speed limit of the Vehicle (In Km/h)*/
  double speed_limit_time;           /**< How long it takes for the Vehicle to reach its speed speed_limit (In Seconds)*/
  double time_driving;               /**< This is used for calculating the acceleration (this is a constant) */
  double acceleration;               /**< The Vehicles acceleration in meter per second squared */
  double safe_distance;              /**< The distance the vehicle tries to keep from the car infront (In Meters) */
  int ID;                            /**< The ID of the car */
  int lane;                          /**< The lane the Vehicle is driving in */
  int secs_on_bridge;                /**< The amount of seconds the Vehicle has been on the bridge */
  State state;                       /**< The State the Vehicle is in (This is of Type State) */
  Lane_type type;                    /**< The Type of lanes the Vehicle can drive in (This is of Type Lane_type) */
  double avg_speed;                  /**< The Average speed of the Vehicle across the bridge */
  double avg_speed_total;            /**< This is used to calculate the average speed of the Vehicle */
  int time_waited_for_green_light;   /**< The amount of seconds the Vehicle has waited for a green light */
} Vehicle;


/*
  A structure to represent Roads 
*/
typedef struct {
  double speed_limit;  /**< The speed limit on the road (In m/s)*/
  Lane_type lane_type; /**< The type of lane the road is (This is of Type Lane_type) */
  double length;       /**< The length of the road (In Meters) */
} Road;
#endif

