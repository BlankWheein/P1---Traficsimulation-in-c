/**
 * @brief  Creates a traffic light struct
 * @param  color: The start color of the light
 * @param  position: The position of the light in meters
 * @param  timer_green: The duration of the green light in seconds
 * @param  timer_red: The duration of the red light in seconds 
 * @retval returns a new traffic light
 */
Traffic_light create_light(Light_color color, double position, int timer_green, int timer_red) {
    Traffic_light light = {color, position, 0, timer_green, timer_red};
    return light;
}

/**
 * @brief  Updates the lights timers
 * @param  light: The light to count up
 * @retval Returns the updated light
 */
Traffic_light count_timer(Traffic_light light) {
  light.timer += 1;
    if (light.color == green && light.timer == light.timer_green)
    {
      light.color = red;
      light.timer = 0;
    }
    else if (light.color == red && light.timer == light.timer_red)
    {
      light.color = green;
      light.timer = 0;
    }
  return light;
}


/**
 * @brief  Finds the closest traffic light in front of the car
 * @param  car: The car to check
 * @param  lights[]: The Array of traffic lights
 * @param  lights_int: The amount of traffic lights in lights[]
 * @retval 
 */
Traffic_light nearest_traffic_light(Vehicle car, Traffic_light lights[], int lights_int) {
  int i;
  Traffic_light nearest_light = {dummy, 99999, 0, 0, 0};
  if (lights_int < 1) {
    return nearest_light;
  }
  for (i = 0; i < lights_int; i++) { /* remember variable for number of lights */
    if (lights[i].position > car.position && nearest_light.position > lights[i].position) {
      nearest_light = lights[i];
    }
  }
  return nearest_light;
}



/**
 * @brief  Prints the traffic light array
 * @param  lights[]: The array of traffic lights
 * @param  a: The amount of lights in the lights array
 * @retval None
 */
void print_traffic_light(Traffic_light lights[], int a) {
  for (int i = 0; i < a; i++) {
    if (lights[i].position > 1) {
      if (color_to_string(lights[i].color) == "Red") {
      printf("Position: %.0lf Color: %s   Timer: %d/%d\n", lights[i].position, color_to_string(lights[i].color), lights[i].timer, lights[i].timer_red);
      }
      else {
      printf("Position: %.0lf Color: %s Timer: %d/%d\n", lights[i].position, color_to_string(lights[i].color), lights[i].timer, lights[i].timer_green);
      }
    }
    else {
      if (color_to_string(lights[i].color) == "Red") {
      printf("Position:   %.0lf Color: %s   Timer: %d/%d\n", lights[i].position, color_to_string(lights[i].color), lights[i].timer, lights[i].timer_red);
      }
      else {
      printf("Position:   %.0lf Color: %s Timer: %d/%d\n", lights[i].position, color_to_string(lights[i].color), lights[i].timer, lights[i].timer_green);
      }
    }
  }
}
