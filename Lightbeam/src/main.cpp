#include <Arduino.h>

#define LED_PIN 9

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
    int i = 0;
    for (; i < 200; i++) {
        analogWrite(LED_PIN, i);
        delay(6);
    }
    for (; i >= 0; i -= 2) {
        analogWrite(LED_PIN, i);
        delay(6);
    }
    delay(100);
}