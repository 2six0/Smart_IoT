#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "Firebase-ESP8266-master/src/FirebaseESP8266.h"

#define FIREBASE_HOST "https://iot-kuu.firebaseio.com/"
#define FIREBASE_AUTH "5GUuI2hwFBMqDmwdhrcTEFuwZeLs8L89ZIW377BY"
#define SSID "b4871e"
#define PASS "277123586"

FirebaseData fbdo;
WiFiClient client;

int Start;
int dataRelay2;

void sendDataInt(int time, String path_db, int value);
int getDataInt(const String path_db, int a);
void randomNumber(int a, int b);

void setup()
{
  Serial.begin(115200);
  WiFi.begin(SSID, PASS);
  Serial.println("Sedang Menyambung WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Sukses Tersambung Internet Dengan IP = ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop()
{
  randomNumber(30, 30);
  sendDataInt(2000, "/Relay_1", Start);
  getDataInt("/Relay_2", dataRelay2);
}

void sendDataInt(int time, const String path_db, int value)
{
  Serial.print(F("Data Yang Dikirim Adalah = "));
  Serial.println(value);
  Firebase.setInt(fbdo, path_db, value);
  delay(time);
}

int getDataInt(const String path_db, int a){
  if (Firebase.getInt(fbdo, path_db)) {
    a = fbdo.intData();
    Serial.print(F("Data Yang Diterima Adalah = "));
    Serial.println(a);
    return a;
    }
    else{
      Serial.println(fbdo.errorReason());
    }
}

void randomNumber(int a, int b)
{
  Start = random(a) * b;
  delay(200);
}