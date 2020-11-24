#include <stdio.h>
#include "structs.h"

Car acceleration(Car car, Road road){
  car.speed_limit = 26.82;
  car.speed_limit_time= 8.5;
  /* Constant acceleraton formula. */
  /*acceleration = 2(1-theta)(v_final - v_0) m/s / t_accTime s (m/s^2) */
  car.acceleration = (2 * (1 - (car.time_driving/car.speed_limit_time)) * (car.speed_limit - 0)) / car.speed_limit_time;
  return car;
}
