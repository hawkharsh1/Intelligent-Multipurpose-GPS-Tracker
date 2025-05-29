# Intelligent Multipurpose GPS Tracker

A final-year IoT-based project integrating **GPS, GSM, and AI/ML** technologies for real-time tracking, anomaly detection, and predictive insights. Built using **ESP32, Neo-6M GPS**, and **SIM800L GSM module**, and powered by Firebase for cloud integration.

---

## 🚀 Features

- 📍 Real-time GPS tracking
- 📡 SMS-based location sharing with Google Maps link
- 📊 Data storage and retrieval via Firebase Realtime Database
- 📈 Predictive analytics using AI/ML (planned)
- 🔐 SOS feature for emergency alerts
- 🔋 Power-efficient hardware design

---

## 🛠️ Technologies Used

### Hardware:
- ESP32 Microcontroller
- NEO-6M GPS Module
- SIM800L GSM Module
- A9G Module (for GPS/GSM integration)
- Rechargeable battery with power management

### Software:
- Embedded C++ for ESP32
- FirebaseESP32 Library
- Google Firebase (Realtime DB)
- Google Maps for location visualization
- AT commands for GSM communication
- Future scope: AI/ML models for behavior analysis and prediction

---

## 📱 How It Works

1. Device fetches current location using the A9G/Neo-6M module.
2. Location is pushed to Firebase (latitude, longitude, timestamp).
3. A Google Maps link is generated and sent via SMS to a predefined SOS number.
4. Data is updated every 30 seconds.

---
## 🧠 Use Cases

- 👨‍👩‍👧 **Personal Safety**: Real-time tracking and emergency SOS for children, elders, and individuals.
- 🚚 **Fleet Management**: Monitor and optimize routes for delivery trucks and logistics services.
- 🧳 **Asset Tracking**: Track valuable goods, vehicles, or shipments in real time.
- 🐾 **Wildlife Monitoring**: Track the movement of animals for conservation purposes.
- 🏥 **Medical Aid**: Real-time location updates during patient transportation for hospitals or ambulances.

---

## 🔧 Code Snippet (Firebase Integration & SMS)

```cpp
Firebase.setString(firebaseData, path + "/latitude", lat);
Firebase.setString(firebaseData, path + "/longitude", longi);
Firebase.setString(firebaseData, path + "/timestamp", timestamp);
Serial1.println("AT+CMGS=\"" + SOS_NUM + "\"");
Serial1.print("I'm Here: http://maps.google.com/maps?q=" + lat + "+" + longi);
