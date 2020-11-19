int check_light(Traffic_light light) {
  int drive = light.light_color == green ? 1 : 0;
  return drive;
}
