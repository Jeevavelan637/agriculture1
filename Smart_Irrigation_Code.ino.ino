/*************************************************
 * Smart Agriculture IoT Irrigation System
 * Hardware: ESP8266 (NodeMCU) / ESP32
 * Features:
 *  - Temperature & Humidity (DHT11/DHT22)
 *  - Soil Moisture Sensor (Analog)
 *  - Relay Control for Pump
 *  - Blynk IoT Cloud Monitoring & Control
 *  - Precision Algorithms:
 *      - Moving Average Filtering
 *      - Dynamic Threshold (adjustable via Blynk)
 *      - Anomaly Detection & Alerts
 *************************************************/

// ---- User Configurations ----

// Wi-Fi & Blynk Credentials
char auth[] = "YourAuthTokenHere";   // From Blynk Device Info
char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

// Pin Configurations
#define DHTPIN D4       // GPIO2
#define DHTTYPE DHT11   // or DHT22
#define RELAY D2        // GPIO4
#define SOIL A0         // Analog Soil Sensor Pin

// Calibration factor for soil sensor readings
#define SOIL_CALIBRATION_FACTOR 1.0

// Initial soil moisture threshold (can be changed via Blynk slider)
int dynamicThreshold = 500;

// Moving average sample count
#define SAMPLE_COUNT 5

// Anomaly detection ranges
#define TEMP_MIN 0
#define TEMP_MAX 50
#define HUM_MIN 0
#define HUM_MAX 100
#define SOIL_MIN 0
#define SOIL_MAX 1023

// ---- Libraries ----
#include <ESP8266WiFi.h>        // For ESP8266
//#include <WiFi.h>             // For ESP32 (uncomment if using ESP32)
#include <BlynkSimpleEsp8266.h> // Change to ESP32 version if needed
#include <DHT.h>

// ---- Objects ----
DHT dht(DHTPIN, DHTTYPE);

// ---- Functions ----

// Moving Average Filter for soil moisture
float getFilteredSoilMoisture() {
  float total = 0;
  for (int i = 0; i < SAMPLE_COUNT; i++) {
    total += analogRead(SOIL);
    delay(50);
  }
  return (total / SAMPLE_COUNT) * SOIL_CALIBRATION_FACTOR;
}

// Manual pump control from Blynk app
BLYNK_WRITE(V4) {
  int pinValue = param.asInt();
  digitalWrite(RELAY, pinValue == 1 ? LOW : HIGH);
}

// Update threshold from Blynk slider
BLYNK_WRITE(V5) {
  dynamicThreshold = param.asInt();
}

// Anomaly detection and alerts
void checkAnomalies(float t, float h, float moisture) {
  if (t < TEMP_MIN || t > TEMP_MAX) {
    Serial.println("[WARNING] Temperature anomaly detected!");
    Blynk.logEvent("temp_anomaly", "Temperature out of range");
  }
  if (h < HUM_MIN || h > HUM_MAX) {
    Serial.println("[WARNING] Humidity anomaly detected!");
    Blynk.logEvent("hum_anomaly", "Humidity out of range");
  }
  if (moisture < SOIL_MIN || moisture > SOIL_MAX) {
    Serial.println("[WARNING] Soil moisture anomaly detected!");
    Blynk.logEvent("soil_anomaly", "Soil moisture out of range");
  }
}

// ---- Setup ----
void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH); // Pump OFF initially
  Serial.println("Smart Agriculture System Started...");
}

// ---- Loop ----
void loop() {
  Blynk.run();

  // Read sensors
  float soil = getFilteredSoilMoisture();
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  // Send to Blynk
  Blynk.virtualWrite(V1, temp);
  Blynk.virtualWrite(V2, hum);
  Blynk.virtualWrite(V3, soil);

  // Check anomalies
  checkAnomalies(temp, hum, soil);

  // Auto pump control
  if (soil < dynamicThreshold) {
    digitalWrite(RELAY, LOW); // Pump ON
  } else {
    digitalWrite(RELAY, HIGH); // Pump OFF
  }

  delay(2000); // Update every 2s
}
