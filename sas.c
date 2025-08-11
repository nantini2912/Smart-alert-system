#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <NewPing.h>
// Pin definitions
const int flameSensorPin = 32; // Flame sensor digital pin (D32)
const int buzzerPin = 25; // Buzzer pin (D25)
const int ledPin = 22; // LED pin (D22) - Optional for visual feedback
// Ultrasonic Sensor Pins
#define TRIG_PIN 27 // Trigger pin
#define ECHO_PIN 26 // Echo pin
#define MAX_DISTANCE 2000 // Max distance in cm (20 meters)
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); // Create NewPing object
// Network credentials (your SSID and password)
const char* ssid = "Galaxy M13 FDE6"; // Your SSID (network name)
const char* password = "krushhh1234"; // Your Wi-Fi password
// Create web server on port 80
AsyncWebServer server(80);
// Flags
bool surveillanceActive = false; // Flag to control surveillance process
void setup() {
// Start serial communication
Serial.begin(115200);
// Set up the pins
pinMode(flameSensorPin, INPUT);
pinMode(buzzerPin, OUTPUT);
pinMode(ledPin, OUTPUT);
// Connect to Wi-Fi
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.println("Connecting to WiFi...");
}
Serial.println("Connected to WiFi");
// Serve the HTML page
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
String html = "<html><body><h1>Fire and Distance Detection</h1>";
if (surveillanceActive) {
html += "<p>Surveillance Status: <b>Active</b></p>";
} else {
html += "<p>Surveillance Status: <b>Inactive</b></p>";
}
html += "<p>Flame Sensor: " + String(digitalRead(flameSensorPin) == LOW ? "Fire
Detected" : "No Fire") + "</p>";
html += "<p>Ultrasonic Sensor Distance: " + String(sonar.ping_cm()) + " cm</p>";
if (surveillanceActive) {
// Button to stop surveillance
html += "<p><a href='/stop'>Stop Surveillance</a></p>";
} else {
// Button to start surveillance
html += "<p><a href='/start'>Start Surveillance</a></p>";
}
html += "</body></html>";
request->send(200, "text/html", html);
});
// Handle Start Surveillance button
server.on("/start", HTTP_GET, [](AsyncWebServerRequest *request){
surveillanceActive = true; // Activate surveillance
request->send(200, "text/html", "<html><body><h1>Surveillance Started</h1><a
href='/'>Go back</a></body></html>");
});
// Handle Stop Surveillance button
server.on("/stop", HTTP_GET, [](AsyncWebServerRequest *request){
surveillanceActive = false; // Deactivate surveillance
digitalWrite(buzzerPin, LOW); // Turn off buzzer
digitalWrite(ledPin, LOW); // Turn off LED
request->send(200, "text/html", "<html><body><h1>Surveillance Stopped</h1><a
href='/'>Go back</a></body></html>");
});
// Start the server
server.begin();
}
void loop() {
// Only check sensors if surveillance is active
if (surveillanceActive) {
// Read the flame sensor (LOW means fire detected)
int flameState = digitalRead(flameSensorPin);
// Measure distance using ultrasonic sensor
int distance = sonar.ping_cm();
// Check if fire is detected or if distance is less than 20 meters
if (flameState == LOW || distance < 20) { // Fire detected or object within 20 meters
Serial.println("Fire or Object Detected!");
digitalWrite(buzzerPin, HIGH); // Turn on buzzer
digitalWrite(ledPin, HIGH); // Turn on LED
} else {
// No fire detected and distance greater than 20 meters, turn off buzzer and LED
digitalWrite(buzzerPin, LOW);
digitalWrite(ledPin, LOW);
}
// Display sensor values in Serial Monitor
Serial.print("Flame Sensor State: ");
Serial.println(flameState == LOW ? "Fire Detected" : "No Fire");
Serial.print("Ultrasonic Sensor Distance: ");
Serial.print(distance);
Serial.println(" cm");
} else {
// If surveillance is not active, make sure the buzzer and LED are off
digitalWrite(buzzerPin, LOW);
digitalWrite(ledPin, LOW);
}
delay(100); // Small delay to stabilize the readings
}
