#include "LF_SData.h"

#define S0_PIN 8
#define S1_PIN 9
#define S2_PIN 10
#define S3_PIN 12
#define ANALOG_INPUT_PIN A0
#define PWM_LEFT 3      // PWM LEFT MOTOR
#define LEFT_MOTOR1 5   // LEFT1 MOTOR
#define LEFT_MOTOR2 4   // LEFT2 MOTOR
#define PWM_RIGHT 11    // PWM RIGHT MOTOR
#define RIGHT_MOTOR1 6  // RIGHT1 MOTOR
#define RIGHT_MOTOR2 7  // RIGHT2 MOTOR

LF_SData sensors;
 
// PID parameters
float KP = 0.78;     // Proportional constant
float KD = 20;        // Derivative constant
float KI = 0.02;    // Integral constant
int maxSpeed = 220;  // Maximum robot speed (max 255)

// Brake speeds
int forwardBrakeSpeed = 250;   // Speed for moving forward during braking
int backwardBrakeSpeed = 200;  // Speed for moving backward during braking

// Data for the integral term
int error1 = 0;
int error2 = 0;
int error3 = 0;
int error4 = 0;
int error5 = 0;
int error6 = 0;

// PID variables
int proportional = 0;
int integral = 0;
int derivative = 0;
int differential = 0;
int lastProportional;
int setpoint = 7500;

void setup() {
  pinMode(LEFT_MOTOR1, OUTPUT);
  pinMode(LEFT_MOTOR2, OUTPUT);
  pinMode(RIGHT_MOTOR1, OUTPUT);
  pinMode(RIGHT_MOTOR2, OUTPUT);
  pinMode(S0_PIN, OUTPUT);
  pinMode(S1_PIN, OUTPUT);
  pinMode(S2_PIN, OUTPUT);
  pinMode(S3_PIN, OUTPUT);


  sensors.setupLineSensors(S0_PIN, S1_PIN, S2_PIN, S3_PIN, ANALOG_INPUT_PIN);
  sensors.calibrateSensors(true);
}

void loop() {
  while (true) {
    applyBrakes();
    readSensors();
    calculatePID();
  }
}

void readSensors() {
  long currentPosition = sensors.getLinePosition();
}

void calculatePID() {
  long currentPosition = sensors.getLinePosition();
  proportional = currentPosition - setpoint;
  derivative = proportional - lastProportional;
  integral = error1 + error2 + error3 + error4 + error5 + error6;
  lastProportional = proportional;
  error6 = error5;
  error5 = error4;
  error4 = error3;
  error3 = error2;
  error2 = error1;
  error1 = proportional;
  differential = (proportional * KP) + (derivative * KD) + (integral * KI);
  if (differential > maxSpeed) differential = maxSpeed;
  else if (differential < -maxSpeed) differential = -maxSpeed;
  if (differential < 0) {
    controlMotors(maxSpeed, maxSpeed + differential);
  } else {
    controlMotors(maxSpeed - differential, maxSpeed);
  }
}

void applyBrakes() {
  long currentPosition = sensors.getLinePosition();
  if (currentPosition <= 1500) {
    controlMotors(forwardBrakeSpeed, -backwardBrakeSpeed);
  }
  if (currentPosition >= 13500) {
    controlMotors(-backwardBrakeSpeed, forwardBrakeSpeed);
  }
}

void controlMotors(int leftSpeed, int rightSpeed) {
  // Motor LEFT
  if (leftSpeed >= 0) {
    digitalWrite(LEFT_MOTOR1, HIGH);
    digitalWrite(LEFT_MOTOR2, LOW);
  } else {
    digitalWrite(LEFT_MOTOR1, LOW);
    digitalWrite(LEFT_MOTOR2, HIGH);
    leftSpeed = -leftSpeed;
  }
  analogWrite(PWM_LEFT, leftSpeed);

  // Motor RIGHT
  if (rightSpeed >= 0) {
    digitalWrite(RIGHT_MOTOR1, HIGH);
    digitalWrite(RIGHT_MOTOR2, LOW);
  } else {
    digitalWrite(RIGHT_MOTOR1, LOW);
    digitalWrite(RIGHT_MOTOR2, HIGH);
    rightSpeed = -rightSpeed;
  }
  analogWrite(PWM_RIGHT, rightSpeed);
}
