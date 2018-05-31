struct Setup {
  float speed;
  float kp;
  float ki;
  float kd;
};
struct Mark {
  float position; // distance in meters
  float acceleration; // mark acceleration
  Setup setup; // robot setup
};
