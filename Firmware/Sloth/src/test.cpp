// #include "mbed.h"
// #include "DistanceReader.h"
// #include "LineReader.h"
//
// Serial PC(USBTX, USBRX);
//
// int main() {
//
//   PC.baud(115200);
//
//   DistanceReader::reset();
//
//   LineReader::calibrate(500);
//
//   while(1) {
//     PC.printf("Left: %i\t", DistanceReader::getPulsesLeft());
//     PC.printf("Right: %i\t", DistanceReader::getPulsesRight());
//     PC.printf("Distance: %.5fm\t", DistanceReader::getDistance());
//     PC.printf("Difference: %.5fm\t", DistanceReader::getDifference());
//     PC.printf("P2D: %.5fm\t", DistanceReader::pulsesToDistance(1790));
//
//     for (size_t sensor = 0; sensor < 6; sensor++) {
//       PC.printf("%i\t", LineReader::getValue(sensor));
//     }
//
//     PC.printf("Position: %.5f", LineReader::getPosition());
//
//     PC.printf("%s","\n");
//     wait(0.1);
//   }
// }
