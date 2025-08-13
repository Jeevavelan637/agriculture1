# 🌱 Smart Agriculture IoT Irrigation System

## 📖 Project Overview
This project is an **IoT-based Smart Irrigation System** 💧 using **ESP8266/ESP32** + **Blynk Cloud** ☁️ to monitor:
- 🌡 Temperature
- 💧 Humidity
- 🌱 Soil Moisture

It automatically controls a **water pump** via a **relay** based on soil moisture thresholds, with both **manual and automatic control modes** from your phone 📱 or web dashboard 🖥.

---

## 🛠 Components Required
| Component | Details | Link |
|-----------|---------|------|
| 🖥 Microcontroller | ESP8266 NodeMCU / ESP32 | [Buy ESP8266](https://www.amazon.in/s?k=esp8266+nodemcu) |
| 🌡 Sensor | DHT11 / DHT22 | [Buy DHT11](https://www.amazon.in/s?k=dht11+temperature+sensor) |
| 🌱 Sensor | Analog Soil Moisture Sensor | [Buy Soil Sensor](https://www.amazon.in/s?k=soil+moisture+sensor) |
| ⚡ Relay | 1-Channel Relay Module | [Buy Relay Module](https://www.amazon.in/s?k=relay+module) |
| 💧 Water Pump | Any 5V/12V DC pump | — |
| 🔌 Power | USB cable or adapter | — |

---

## 🖇 Wiring
| ESP8266 Pin | Component |
|-------------|-----------|
| D4 | DHT Data |
| A0 | Soil Sensor Analog Output |
| D2 | Relay IN |
| G | Common Ground |
| 3V3/5V | Power to sensors |

---

## ☁️ Blynk Setup
1. **Create an account** on **[Blynk Cloud](https://blynk.cloud)** or use the **Blynk IoT App** 📱 ([Android](https://play.google.com/store/apps/details?id=cloud.blynk) | [iOS](https://apps.apple.com/app/id1559317868)).
2. **Create a Template**:
   - Hardware: `ESP8266` or `ESP32`
   - Connection: `Wi-Fi`
3. **Add Virtual Pins**:
   - `V1` → 🌡 Temperature (Float)
   - `V2` → 💧 Humidity (Float)
   - `V3` → 🌱 Soil Moisture (Integer)
   - `V4` → 🖲 Pump Switch (Integer)
   - `V5` → 🎚 Moisture Threshold (Integer)
4. **Copy Auth Token** from **Device Info** → paste in your Arduino code.

---

## 🖥 Software Setup
1. **Download Arduino IDE** → [Arduino Official Site](https://www.arduino.cc/en/software)  
2. Install **libraries** in **Arduino IDE** → Sketch → Include Library → Manage Libraries:
   - 📦 [Blynk](https://github.com/blynkkk/blynk-library) (by Volodymyr Shymanskyy)
   - 📦 ESP8266WiFi / WiFi (for ESP32)
   - 📦 [DHT Sensor Library](https://github.com/adafruit/DHT-sensor-library) (by Adafruit)
   - 📦 [Adafruit Unified Sensor](https://github.com/adafruit/Adafruit_Sensor)
3. **Select Board & Port**:
   - Tools → Board → `NodeMCU 1.0 (ESP-12E)` (or your ESP32 board)
4. **Upload Code** (main_code.ino)

---

## ✨ Features
- ✅ **Real-time Monitoring** via Blynk Cloud
- ✅ **Manual & Automatic Pump Control**
- ✅ **Dynamic Threshold** adjustment from App/Web
- ✅ **Sensor Filtering Algorithm** (Moving Average)
- ✅ **Anomaly Detection** with Alerts 🚨

---

## 📸 Dashboard Example
_Blynk dashboard layout example:_  
![Dashboard Example](diagrams/dashboard_mockup.png)

---

## 📂 Project File Structure
