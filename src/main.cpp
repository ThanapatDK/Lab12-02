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

enum SystemMode { MODE_MANUAL = 0, MODE_AUTO = 1 };
enum LedState { LED_OFF = 0, LED_ON = 1 };
enum LedSwitchState { SWITCH_OFF = 0, SWITCH_ON = 1 };

SystemMode currentMode = MODE_MANUAL;
LedSwitchState ledSwitchState = SWITCH_OFF;
LedState ledState = LED_OFF;
LedState lastLedState = (LedState)-1;

BLYNK_WRITE(V1) { ledSwitchState = (LedSwitchState)param.asInt(); }
BLYNK_WRITE(V2) { currentMode = (SystemMode)param.asInt(); }

void setup() {
  Serial.begin(9600);
  pinMode(LDR_PIN, INPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();

  int value_LDR = digitalRead(LDR_PIN);
  delay(100);

  if (currentMode == MODE_AUTO) {
    if (value_LDR < 1) {
      ledState = LED_OFF;
    } else {
      ledState = LED_ON;
    }
  } else if (currentMode == MODE_MANUAL) {
    if (ledSwitchState == SWITCH_ON) {
      ledState = LED_ON;
    } else {
      ledState = LED_OFF;
    }
  }

  if (ledState != lastLedState) {
    lastLedState = ledState;
    Blynk.virtualWrite(V0, ledState);
  }
}