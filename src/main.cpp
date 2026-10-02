#include <Arduino.h>

#define BLYNK_TEMPLATE_ID "TMPL6KAAypUQu"
#define BLYNK_TEMPLATE_NAME "Lab12 IOT 2"
#define BLYNK_AUTH_TOKEN "8ltaTm70iMlHbUgvlzmCpZt1R6KqDJCD"

#define BLYNK_PRINT Serial
#define LDR_PIN 2

#include <BlynkSimpleEsp32.h>
#include <WiFi.h>
#include <WiFiClient.h>

char ssid[] = "Wokwi-GUEST";
char pass[] = "";

int autoMode = 0;
int ledOn = 0;

BLYNK_WRITE(V1) { ledOn = param.asInt(); }

BLYNK_WRITE(V2) { autoMode = param.asInt(); }

void setup() {
  Serial.begin(9800);
  pinMode(LDR_PIN, INPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();

  int value_LDR = digitalRead(LDR_PIN);
  delay(100);

  if (autoMode == 1) {
    if (value_LDR < 1) {
      Blynk.virtualWrite(V0, 0);
    } else {
      Blynk.virtualWrite(V0, 1);
    }
  } else {
    if (ledOn == 1) {
      Blynk.virtualWrite(V0, 1);
    } else {
      Blynk.virtualWrite(V0, 0);
    }
  }
}