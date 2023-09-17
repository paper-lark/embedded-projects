#include <Arduino.h>

#define ROW_COUNT 2
#define COLUMN_COUNT 2

int row_pins[ROW_COUNT] = {3, 5};
int column_pins[COLUMN_COUNT] = {9, 11};
bool is_button_pressed[ROW_COUNT][COLUMN_COUNT] = {{false, false}, {false, false}};

void setup()
{
    for (int i = 0; i < ROW_COUNT; i++)
    {
        pinMode(row_pins[i], INPUT);
        digitalWrite(row_pins[i], LOW);
    }

    for (int j = 0; j < COLUMN_COUNT; j++)
    {
        pinMode(column_pins[j], INPUT);
    }

    Serial.begin(9600);
}

void loop()
{
    for (int j = 0; j < COLUMN_COUNT; j++)
    {
        pinMode(column_pins[j], OUTPUT);
        digitalWrite(column_pins[j], LOW);

        for (int i = 0; i < ROW_COUNT; i++)
        {
            pinMode(row_pins[i], INPUT_PULLUP);
            bool is_pressed = !digitalRead(row_pins[i]);
            pinMode(row_pins[i], INPUT);

            bool was_pressed = is_button_pressed[i][j];
            if (is_pressed && !was_pressed)
            {
                Serial.print(i * COLUMN_COUNT + j);
                Serial.print("\n");
            }
            is_button_pressed[i][j] = is_pressed;
        }

        pinMode(column_pins[j], INPUT);
    }
}
