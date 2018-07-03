#include "mbed.h"
#include "DistanceReader.h"

class Checkpoint {
public:
  int id;
  float position;
};

class CheckpointReader {
public:
  static void init();
  static void checkPointLeftCallback();
  static void checkPointRightCallback();
  
  // Trying to avoid dynamic lists.
  static Checkpoint checkpoint_list[100];
};
