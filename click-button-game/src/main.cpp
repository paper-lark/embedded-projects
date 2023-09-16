#include <Arduino.h>

#define PLAYER_COUNT 2
#define LED_PIN 9
#define BUTTON_PIN 3

const int ledPins[PLAYER_COUNT] = {9, 11};
const int buttonPins[PLAYER_COUNT] = {3, 5};

void setup()
{
    for (int player = 0; player < PLAYER_COUNT; player++)
    {
        pinMode(ledPins[player], OUTPUT);
        pinMode(buttonPins[player], INPUT_PULLUP);
    }
}

void loop()
{
    // initilize game
    for (int player = 0; player < PLAYER_COUNT; player++)
    {
        digitalWrite(ledPins[player], HIGH);
    }
    delay(random(5000, 10000));
    for (int player = 0; player < PLAYER_COUNT; player++)
    {
        digitalWrite(ledPins[player], LOW);
    }

    // TODO: check that at the beginning all buttons are not pressed

    // wait until any button is pressed
    for (int player = 0;; player = (player + 1) % PLAYER_COUNT)
    {
        int buttonPin = buttonPins[player];
        int ledPin = ledPins[player];

        if (!digitalRead(buttonPin))
        {
            // player hit the button
            digitalWrite(ledPin, HIGH);
            delay(3000);
            digitalWrite(ledPin, LOW);
            break;
        }
    }

    // cleanup
    for (int player = 0; player < PLAYER_COUNT; player++)
    {
        digitalWrite(ledPins[player], LOW);
    }
    delay(2000);
}
