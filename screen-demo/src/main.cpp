#include <Arduino.h>
#include <LiquidCrystal.h>
#include <RunningAverage.h>
#include "temperature.hpp"

#define TEMPERATURE_PIN A0

// Datasheet (R/T No. 2904): https://files.amperka.ru/datasheets/B57164.pdf
Thermistor thermistor(
    convert_celsius_to_kelvin(-55.0),
    121.46 * 10000.0,
    convert_celsius_to_kelvin(25.0),
    10000.0,
    convert_celsius_to_kelvin(155.0),
    0.011754 * 10000.0);
RunningAverage temperature_history(5);
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

void setup()
{
    lcd.begin(16, 2);
}

float calculate_temperature(float v_out)
{
    // NOTE: we are using voltage divider w/ 10kOhm resistor
    float R = 10000.0 * v_out / (5.0 - v_out);
    return convert_kelvin_to_celsius(thermistor.convert_to_temperature(R));
}

void loop()
{
    // collect information
    // NOTE: pin is returning value in range [0; 1023]
    float current_v_out = analogRead(TEMPERATURE_PIN) * 5.0 / 1023.0;
    temperature_history.add(current_v_out);

    // calculate stats
    float average_v_out = temperature_history.getAverage();
    float temperature = calculate_temperature(average_v_out);
    unsigned long seconds_running = millis() / 1000;

    // print info
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature, 0);
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("Time: ");
    lcd.print(seconds_running);
}
