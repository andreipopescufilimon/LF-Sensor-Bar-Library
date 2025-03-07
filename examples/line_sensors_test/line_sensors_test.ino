#include <Arduino.h>
#include "LF_SData.h"

LF_SData sensorData;

#define S0 0   // Multiplexer select pin S0
#define S1 1   // Multiplexer select pin S1
#define S2 2   // Multiplexer select pin S2
#define S3 4   // Multiplexer select pin S3
#define SIG A5 // Analog signal pin from multiplexer

void setup() {
    Serial.begin(115200);
    sensorData.setupLineSensors(S0, S1, S2, S3, SIG);
    sensorData.calibrateSensors(true);  // Perform full calibration
}

void loop() {
    long position = sensorData.getLinePosition();
    Serial.print("Line Position: ");
    Serial.println(position);
    
    // Print sensor values
    sensorData.getLiveSerialPrint(true, false);
    
    delay(100);
}
