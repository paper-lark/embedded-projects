#include <Arduino.h>
#include "protothreads.h"

#define FIRST_LED_PIN 2
#define SECOND_LED_PIN 3

static pt pt1, pt2;

PT_THREAD(blinkCoro(struct pt* pt, int led_pin, int interval)) {
    PT_BEGIN(pt);

    for(;;) {
        PT_SLEEP(pt, interval);
        digitalWrite(led_pin, HIGH);
        PT_SLEEP(pt, interval);
        digitalWrite(led_pin, LOW);
    }

    PT_END(pt);
}

void setup() {
    PT_INIT(&pt1);
    PT_INIT(&pt2);

    pinMode(FIRST_LED_PIN, OUTPUT);
    pinMode(SECOND_LED_PIN, OUTPUT);
}

void loop() {
    blinkCoro(&pt1, FIRST_LED_PIN, 1000);
    blinkCoro(&pt2, SECOND_LED_PIN, 2000);
}