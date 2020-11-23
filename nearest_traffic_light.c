Traffic_light nearest_traffic_light(Car car, Traffic_light lights[], int lights_int) {
  int i;
  Traffic_light nearest_light = {dummy, 99999};
  for (i = 0; i < lights_int; i++) { /* remember variable for number of lights */
    if (lights[i].position > car.location && nearest_light.position > lights[i].position) {
      nearest_light = lights[i];
    }
  }
  return nearest_light;
}
