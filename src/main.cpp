#include <Arduino.h>
#include <Secrets.h>
#include <ESP8266WiFi.h>
#include "Firebase-ESP8266-master/src/FirebaseESP8266.h"

#define FIREBASE_HOST FB_Host
#define FIREBASE_AUTH FB_Auth
#define SSID "b4871e"
#define PASS "277123586"

FirebaseData fbdo;
WiFiClient client;

int Relay_1 = 16;
int Relay_2 = 00;

int Start;
int dataRelay1;
int dataRelay2;

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

  pinMode(Relay_1, OUTPUT);
  pinMode(Relay_2, OUTPUT);
}

void sendDataInt(int time, String path_db, int value);
int getDataRelay_1(const String path_db);
int getDataRelay_2(const String path_db);
void mainRelay(int Relay, int Value);
void randomNumber(int a, int b);

void loop()
{
  //randomNumber(30, 30);
  //sendDataInt(2000, "/Relay_1", Start);
  getDataRelay_1("Relay_1");
  getDataRelay_2("Relay_2");
  Serial.println(" ");
  Serial.println(dataRelay1);
  Serial.println(dataRelay2);
  Serial.println(" ");
  //getDataInt("/Relay_2", dataRelay2);
  mainRelay(Relay_1, dataRelay1);
  mainRelay(Relay_2,dataRelay2);
}

void sendDataInt(int time, const String path_db, int value)
{
  Serial.print(F("Data Yang Dikirim Adalah = "));
  Serial.println(value);
  Firebase.setInt(fbdo, path_db, value);
  delay(time);
}

int getDataRelay_1(const String path_db)
{
  if (Firebase.getInt(fbdo, path_db))
  {
    dataRelay1 = fbdo.intData();
    Serial.print(F("Status Relay Adalah = "));
    Serial.println(dataRelay1);
  }
  else
  {
    Serial.println(fbdo.errorReason());
  }
  return dataRelay1;
}

int getDataRelay_2(const String path_db)
{
  if (Firebase.getInt(fbdo, path_db))
  {
    dataRelay2 = fbdo.intData();
    Serial.print(F("Status Relay Adalah = "));
    Serial.println(dataRelay2);
  }
  else
  {
    Serial.println(fbdo.errorReason());
  }
  return dataRelay2;
}

void mainRelay(int Relay, int Value)
{
  if (Value == 1)
  {
    digitalWrite(Relay, HIGH);
    Serial.print("Relay pin ke ");
    Serial.print(Relay);
    Serial.println(" Aktif");
  }
  else if (Value == 0)
  {
    digitalWrite(Relay, LOW);
    Serial.print("Relay ke ");
    Serial.print(Relay);
    Serial.println("Tidak Aktif");
  }
  else
  {
    Serial.println("Tidak Menerima Data");
  }
}

void randomNumber(int a, int b)
{
  Start = random(a) * b;
  delay(200);
}