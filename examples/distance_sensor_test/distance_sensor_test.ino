#include "LF_SData.h"

LF_SData sensorData;

#define DISTANCE_SENSOR_PIN A0  // Adjust to your setup

void setup() {
    Serial.begin(115200);
    sensorData.setupDistanceSensor(DISTANCE_SENSOR_PIN);
}

void loop() {
    int16_t distance = sensorData.getDistance();
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" mm");
    delay(500);
}
