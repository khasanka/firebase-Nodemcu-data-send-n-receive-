#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "tronicslab-1dbeb.firebaseio.com" //Without http:// or https:// schemes
#define FIREBASE_AUTH "IjxWPKCSH61TQhfwxh6EKAminl97NgNfxjdeJaF3"
#define WIFI_SSID "TronicsLab"
#define WIFI_PASSWORD "Kasun Hasanka"

FirebaseData firebaseData;
String path = "/Test/Stream";
unsigned long count = 0;

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  firebaseData.setBSSLBufferSize(1024, 1024);
  firebaseData.setResponseSize(1024);

  if (!Firebase.beginStream(firebaseData, path)) {
    Serial.println("Can't begin stream connection...");
  }

} // --- setup end

void loop() {
  if (!Firebase.readStream(firebaseData)) {
    Serial.println("Can't read stream data...");
  }

  if (firebaseData.streamAvailable()) {
    Serial.println(firebaseData.stringData());
  }
  
} // -- end loop
