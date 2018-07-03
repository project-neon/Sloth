#include "CheckpointReader.h"

static InterruptIn CheckpointSensorLeft(PIN_TRACK_MARKING_LEFT);
static InterruptIn CheckpointSensorRight(PIN_TRACK_MARKING_RIGHT);
volatile unsigned int checkpoint_index = 0;

void CheckpointReader::init() {
    // Activating Interrupt in fall for the checkpoint sensors
    CheckpointSensorLeft.fall(&CheckpointReader::checkPointLeftCallback);
    CheckpointSensorRight.fall(&CheckpointReader::checkPointRightCallback);
}

void CheckpointReader::checkPointLeftCallback() {
  checkpoint_list[checkpoint_index].id = checkpoint_index;
  checkpoint_list[checkpoint_index].position = DistanceReader::getDistance();
}

void CheckpointReader::checkPointRightCallback() {
  checkpoint_list[checkpoint_index].id = checkpoint_index;
  checkpoint_list[checkpoint_index].position = DistanceReader::getDistance();
}
