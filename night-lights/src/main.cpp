#include <Arduino.h>

#define FIRST_LED_PIN 2
#define LAST_LED_PIN 11
#define LDR_PIN A0
#define MIN_LIGHTNESS 500
#define MAX_LIGHTNESS 1000

void setup() {
    Serial.begin(9600);
    for (int i = FIRST_LED_PIN; i <= LAST_LED_PIN; i++) {
        pinMode(i, OUTPUT);
    }
}

void loop() {
    int lightness = analogRead(LDR_PIN);
    Serial.println(lightness);

    int adjusted_lightness = max(0, min(MAX_LIGHTNESS, lightness) - MIN_LIGHTNESS);
    int pins_to_light = int((1 - adjusted_lightness / float(MAX_LIGHTNESS - MIN_LIGHTNESS)) * (LAST_LED_PIN - FIRST_LED_PIN + 1));

    for (int i = FIRST_LED_PIN; i <= LAST_LED_PIN; i++) {
        if (i < pins_to_light) {
            digitalWrite(i, HIGH);
        } else {
            digitalWrite(i, LOW);
        }
    }
    delay(100);
}