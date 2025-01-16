#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <MFRC522.h>
#include <SPI.h>
#include <ESP32Servo.h>

// WiFi credentials
const char* ssid = "masaba";
const char* password = "masaba139";

// Flask server URL
const char* serverURL = "http://192.168.0.116:5000/get_data";

// RFID pins
#define RST_PIN 22
#define SS_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN);

//#define SERVO_PIN1 25
//#define SERVO_PIN2 25
#define SERVO_PIN3 25
//#define SERVO_PIN4 25
//#define SERVO_PIN5 25
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

void setup() {
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();
 // servo1.attach(SERVO_PIN1);
  //servo1.write(0); // Set servo to initial position
 // servo2.attach(SERVO_PIN2);
 // servo2.write(0); // Set servo to initial position
  servo3.attach(SERVO_PIN3);
  servo3.write(0); // Set servo to initial position
  //servo4.attach(SERVO_PIN4);
  //servo4.write(0); // Set servo to initial position
   //servo5.attach(SERVO_PIN5);
  //servo5.write(0); // Set servo to initial position  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Check for RFID card
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    delay(1000); // Longer delay when idle
    return;
  }

  // Read and format RFID UID
  String uid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    uid += String(mfrc522.uid.uidByte[i], HEX);
  }
  uid.toUpperCase();
  Serial.print("RFID UID: ");
  Serial.println(uid);

  // HTTP request
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverURL);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String payload = http.getString();
      //Serial.println("Server Response:");
      //Serial.println(payload);
      processExcelData(payload, uid);
    } else {
      Serial.printf("HTTP Request failed, Error Code: %d\n", httpResponseCode);
      if (httpResponseCode == -1) {
        Serial.println("Check server URL or Flask server status.");
      }
    }
    http.end();
  } else {
    Serial.println("WiFi Disconnected. Reconnecting...");
    WiFi.reconnect();
  }

  delay(1000); // Wait before next scan
}

void processExcelData(String json, String uid) {
  StaticJsonDocument<2048> doc;
  DeserializationError error = deserializeJson(doc, json);

  if (error) {
    Serial.print("JSON Parsing Error: ");
    Serial.println(error.c_str());
    return;
  }

 for (JsonObject row : doc.as<JsonArray>()) {
    String rfid = row["RFID NO "].as<String>();
    if (uid.equalsIgnoreCase(rfid)) { // Match found
      Serial.println("Match found!");

      // Save medicine values in variables
      int medicine1 = row["MEDICINE 1"].as<int>();
      int medicine2 = row["MEDICINE 2"].as<int>();
      int medicine3 = row["MEDICINE 3"].as<int>();
      int medicine4 = row["MEDICINE 4"].as<int>();
      int medicine5 = row["MEDICINE 5"].as<int>();

      // Control the servo motor based on values
      controlServo1(medicine1, "MEDICINE 1");
      delay(5000);
      controlServo2(medicine2, "MEDICINE 2");
      delay(5000);
      controlServo3(medicine3, "MEDICINE 3");
      delay(5000);
      controlServo4(medicine4, "MEDICINE 4");
      delay(5000);
      controlServo5(medicine5, "MEDICINE 5");
      delay(5000);

      return; // Exit loop after processing the matched row
    }
  }

  // If no match found
  Serial.println("No match found for this UID.");
}


void controlServo1(int value, String medicineName) {
  if (value == 1) {
    Serial.print(medicineName);
    Serial.println(": Servo Rotating...");
    servo1.write(90); // Rotate the servo to 90 degrees
    delay(1000);     // Keep it rotated for 1 second
    servo1.write(0);  // Return to the initial position
    delay(500);      // Wait before the next action
  } else {
    Serial.print(medicineName);
    Serial.println(": No action.");
  }
}
void controlServo2(int value, String medicineName) {
  if (value == 1) {
    Serial.print(medicineName);
    Serial.println(": Servo Rotating...");
    servo2.write(90); // Rotate the servo to 90 degrees
    delay(1000);     // Keep it rotated for 1 second
    servo2.write(0);  // Return to the initial position
    delay(500);      // Wait before the next action
  } else {
    Serial.print(medicineName);
    Serial.println(": No action.");
  }
}
void controlServo3(int value, String medicineName) {
  if (value == 1) {
    Serial.print(medicineName);
    Serial.println(": Servo Rotating...");
    servo3.write(90); // Rotate the servo to 90 degrees
    delay(1000);     // Keep it rotated for 1 second
    servo3.write(0);  // Return to the initial position
    delay(500);      // Wait before the next action
  } else {
    Serial.print(medicineName);
    Serial.println(": No action.");
  }
}
void controlServo4(int value, String medicineName) {
  if (value == 1) {
    Serial.print(medicineName);
    Serial.println(": Servo Rotating...");
    servo4.write(90); // Rotate the servo to 90 degrees
    delay(1000);     // Keep it rotated for 1 second
    servo4.write(0);  // Return to the initial position
    delay(500);      // Wait before the next action
  } else {
    Serial.print(medicineName);
    Serial.println(": No action.");
  }
}
void controlServo5(int value, String medicineName) {
  if (value == 1) {
    Serial.print(medicineName);
    Serial.println(": Servo Rotating...");
    servo5.write(90); // Rotate the servo to 90 degrees
    delay(1000);     // Keep it rotated for 1 second
    servo5.write(0);  // Return to the initial position
    delay(500);      // Wait before the next action
  } else {
    Serial.print(medicineName);
    Serial.println(": No action.");
  }
}