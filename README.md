# Smart-alert-system 🚨
This project aims to create a smart surveillance system using an ESP32 microcontroller,
which integrates a flame sensor and an ultrasonic sensor to detect fire and movement,
respectively.
Flame Sensor : The flame sensor detects the presence of fire by sensing infrared radiation
emitted by flames. If a flame is detected, the ESP32 triggers an alert (e.g., a buzzer or LED).
Ultrasonic Sensor : The ultrasonic sensor measures the distance between the sensor and any
object in its range. If movement is detected (i.e., the distance changes beyond a threshold), it
triggers an alert.

**COMPONENTS REQUIRED:**

1.ESP32 Development Board - Used as the main microcontroller to control sensors and
web interface

2.Ultrasonic Sensor (HC-SR04) - To detect movement by measuring distance changes.

3.Flame Sensor (YF-Sensor) - To detect fire or flame.

4.Buzzer or Alarm - For sound alerts when fire or movement is detected.

5.LED (optional) - To indicate status of detection (fire or movement).

6.Jumper Wires - For connecting sensors to the ESP32 board.

7.Resistors (as required by sensors, e.g., pull-down resistors for flame sensor).

8.Breadboard - For prototyping the circuit.

9.Power Supply (e.g., 5V Adapter) - To power the ESP32 and sensors.

10.WiFi Access Point - For enabling web interface communication.

**PROCEDURE:**

**HARDWARE SETUP:**
1. Connect the Ultrasonic Sensor (HC-SR04):
2. Connect the VCC pin of the sensor to 3.3V or 5V (check sensor specifications).
3. Connect the Trig pin to a GPIO pin (e.g., GPIO 12) on the ESP32.
4. Connect the Echo pin to another GPIO pin (e.g., GPIO 13) on the ESP32.
5. Connect the GND pin of the sensor to the ground.
6. Connect the Flame Sensor:
7. Connect the VCC pin to the 3.3V or 5V pin on the ESP32.
8. Connect the OUT pin to a GPIO pin (e.g., GPIO 14).
9. Connect the GND pin to the ground.
10. Connect the Buzzer or Alarm:
11. Connect the positive lead of the buzzer to a GPIO pin (e.g., GPIO 27) and the
negative to ground.

**SOFTWARE SETUP:**
1. Program the ESP32 using the Arduino IDE (or any other suitable platform).
2. Install necessary libraries:
ESP32 WiFi Library for WiFi connectivity.
ESPAsyncWebServer for setting up a web server.
Ultrasonic Sensor Library (if applicable).
3. Code the Web Interface (HTML + JavaScript):
4. Create a simple HTML page with buttons to Start Surveillance and Stop Surveillance.
5. Include JavaScript code to send HTTP requests to the ESP32 when the buttons are
clicked.
