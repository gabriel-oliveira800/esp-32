#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#define SOUND_SPEED 0.034
#define MIN_DISTANCE_IN_CM 60.0

const int trig = 27;
const int echo = 26;

HTTPClient http;
WiFiMulti wifiMulti;

void checkWifiConnection(){
  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[WIFI_SETUP] aguarde %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  wifiMulti.addAP("WIFI-IFBA", "");
}

void setup() {
  Serial.begin(115200);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  checkWifiConnection();
}

void loop() {
  clearAll();

  float distance = getDistance(); // cm
  Serial.println("Distancia Sensor 01: " + String(distance) + " cm");
  if (distance > MIN_DISTANCE_IN_CM) return;

  delayMicroseconds(2);

  if ((wifiMulti.run() != WL_CONNECTED)) {
    Serial.println("Wifi não conectado");
    return;
  } 

  http.setReuse(false);
  http.begin("https://esp-32-two.vercel.app/add");

  Serial.print("[HTTP] --> Registrando uma pessoa na sala");

  int statusCode = http.GET();
  handleResponse(statusCode);

  http.end();

  delay(5000);
}

void handleResponse(int statusCode){
  if(statusCode <= 0) {
    Serial.printf("[HTTP] --> Request falhou: %s\n", http.errorToString(statusCode).c_str());

    return;
  }

  Serial.printf("[HTTP] --> Request finalizada: %d\n", statusCode);
  Serial.printf("Mensagem: %s", http.getString());
}


int getDistance() {
  emitPulse();
  long duration = pulseIn(echo, HIGH);
  return (duration * SOUND_SPEED) / 2;
}

void emitPulse() {
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
}

void clearAll() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
}