# LF_SData - Line Follower Sensor Data Library

LF_SData is an Arduino library for handling **16-sensor bars with a multiplexer (MUX)** and a **distance sensor**. This library provides easy setup, calibration, and real-time data reading.

<p align="center">
  <img src="https://hyperlinerobotics.com/assets/images/products/16-sensors-array.jpg" alt="Sensor Image" width="400">
</p>

## 🚀 Features
- Supports **16 sensor bars** connected via a **multiplexer**.
- Works with a **single distance sensor**.
- **Calibration system** using EEPROM for persistent settings.
- **Real-time data output** for debugging.

## 📌 Installation
1. Clone the repository or download it as a ZIP.
2. Place the `LF_SData` folder inside your Arduino `libraries` directory.
3. Restart the **Arduino IDE** if it's already open.

## 📡 Pin Configuration
- **Distance Sensor:** Uses a single analog pin.
- **Multiplexer Setup:** Uses 4 control pins (S0-S3) and 1 signal pin (SIG).

## 🛠 Functions Overview

### Distance Sensor Functions
- `setupDistanceSensor(uint8_t distancePin)`: Initializes the distance sensor.
- `getDistance()`: Returns the measured distance in **millimeters (mm)**.

### Line Sensors Functions
- `setupLineSensors(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t sig)`: Initializes the line sensors using the multiplexer.
- `calibrateSensors(bool fullCalibration)`: Performs full or partial calibration.
- `getLinePosition()`: Returns the **line position** based on sensor readings.
- `getLiveSerialPrint(bool printSensors, bool printDistance)`: Prints real-time sensor data to **Serial Monitor**.
