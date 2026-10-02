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

int MODE_SWITCH = 0;
int LED_SWITCH = 0;
int LED_ON = 0;
int lastLedState = -1;

BLYNK_WRITE(V1) { LED_SWITCH = param.asInt(); }
BLYNK_WRITE(V2) { MODE_SWITCH = param.asInt(); }

void setup() {
  Serial.begin(9600);
  pinMode(LDR_PIN, INPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();

  int value_LDR = digitalRead(LDR_PIN);
  delay(100);

  // MODE 0 = MANUAL, MODE 1 = Auto,
  if (MODE_SWITCH == 1) {
    if (value_LDR < 1) {
      LED_ON = 0;
    } else {
      LED_ON = 1;
    }
  } else if (MODE_SWITCH == 0) {
    // SWITCH 0 = OFF, SWITCH 1 = ON
    if (LED_SWITCH == 1) {
      LED_ON = 1;
    } else {
      LED_ON = 0;
    }
  }

  if (LED_ON != lastLedState) {
    lastLedState = LED_ON;
    Blynk.virtualWrite(V0, LED_ON);
  }
}