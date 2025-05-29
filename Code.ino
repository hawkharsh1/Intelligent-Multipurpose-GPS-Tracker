#include <WiFi.h>
#include <FirebaseESP32.h>
// WiFi Credentials
#define WIFI_SSID "Harsh's iphone"
#define WIFI_PASSWORD "12345678"
// Firebase Configuration
#define FIREBASE_HOST "https://multipurpose-gps-tracker-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "wzftgtynwVyG0B7PxuMNVQ0frUvPyfZDOnimGMh6"
// SOS Number
#define SOS_NUM "+91-93353488xx"
// A9G Low Power Pin
#define A9G_LOWP 4
FirebaseData firebaseData; // Firebase Data Object
String res = ""; // For processing GPS response
String response = ""; // For final GPS data
String custom_message = ""; // Custom SMS message
void setup() {
Serial.begin(115200);
Serial1.begin(9600, SERIAL_8N1, 16, 17); // Pins 16 (RX) and 17 (TX) for A9G module
pinMode(A9G_LOWP, OUTPUT);
// Connect to WiFi
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.println("Connecting to WiFi...");
}
Serial.println("Connected to WiFi");
// Connect to Firebase
Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
Firebase.reconnectWiFi(true);
Serial.println("Connected to Firebase");
}

void Get_gmap_link(bool makeCall) {
digitalWrite(A9G_LOWP, LOW);
delay(1000);
Serial1.println("AT+LOCATION = 2");
Serial.println("AT+LOCATION = 2");
while (!Serial1.available());
while (Serial1.available()) {
char add = Serial1.read();
res = res + add;
delay(1);
}
res = res.substring(17, 38);
response = &res[0];
Serial.print("Received Data -
");
Serial.println(response); // Print the string
Serial.println("\n");
if (strstr(response, "GPS NOT")) {
Serial.println("No Location data");
custom_message = "Unable to fetch location. Please try again";
Send_SMS(custom_message);
} else {
int i = 0;
while (response[i] != ',') i++;
String location = (String)response;
String lat = location.substring(2, i);
String longi = location.substring(i + 1);
Serial.println(lat);
Serial.println(longi);
// Send data to Firebase
String path = "/device_data";
String timestamp = String(millis());
Firebase.setString(firebaseData, path + "/latitude", lat);
Firebase.setString(firebaseData, path + "/longitude", longi);
Firebase.setString(firebaseData, path + "/timestamp", timestamp);
if (Firebase.pushJSON(firebaseData, path)) {
Serial.println("Data sent to Firebase successfully!");
} else {
Serial.println("Error sending data to Firebase: " + firebaseData.errorReason());
}

String Gmaps_link = "I'm Here " + ("http://maps.google.com/maps?q=" + lat + "+" + longi);
custom_message = Gmaps_link;
Send_SMS(custom_message);
}
response = "";
res = "";
if (makeCall) {
Serial.println("Calling Now");
Serial1.println("ATD" + SOS_NUM);
}
}
void Send_SMS(String message) {
Serial1.println("AT+CMGF=1"); // Set SMS mode
delay(1000);
Serial1.println("AT+CMGS=\"" + SOS_NUM + "\"");
delay(1000);
Serial1.print(message);
delay(1000);
Serial1.write(26); // Send Ctrl+Z to end SMS
delay(1000);
Serial.println("SMS Sent");
}
void loop() {
// Call the function as needed
Get_gmap_link(false);
delay(30000); // Fetch location every 30 seconds
}
