#include <WiFi.h>

// WiFi credentials
const char* ssid = "";
const char* password = "";

//THIS NEEDS TO HAVE AN INTERNET CONNECTION TO SEND DATA TO SERVER

// Node.js server details
const char* serverIP = "10.67.0.10";  // Make sure this is the IP of your computer running the server
const int serverPort = 2467;

// Sensor pin
#define AOUT_PIN 33  // ESP32 pin GPIO33 connected to AOUT pin of the moisture sensor

void setup() {
  Serial.begin(9600);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  pinMode(26, OUTPUT);
}

void loop() {
  int value = analogRead(AOUT_PIN);  // Read the analog value from sensor
  
  Serial.print("Moisture value: ");
  Serial.println(value);
 
  if (value == 4095) {
    Serial.println("No Water");
    digitalWrite(26, HIGH);
  } else {
    Serial.println("Water Detected");
    digitalWrite(26, LOW);
}
  // Send the moisture value to the Node.js server
  sendToServer(value);
  Serial.println("Value sent: " + String(value));
  
  delay(2000);  // Delay for 1 minute
}

void sendToServer(int moistureValue) {
  WiFiClient client;

  if (client.connect(serverIP, serverPort)) {
    // Form the HTTP POST request
    String postData = "moisture=" + String(moistureValue);
    client.print(String("POST /update HTTP/1.1\r\n") +
                 "Host: " + serverIP + "\r\n" +
                 "Content-Type: application/x-www-form-urlencoded\r\n" +
                 "Content-Length: " + String(postData.length()) + "\r\n\r\n" +
                 postData);

    delay(10);  // Give the server some time to respond

    // Read the server's response
    while (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }

    client.stop();
  } else {
    Serial.println("Failed to connect to server");
  }
}
