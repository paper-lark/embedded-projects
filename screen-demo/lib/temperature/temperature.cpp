#include <Arduino.h>
#include "temperature.hpp"

Thermistor::Thermistor(
    float t1,
    float r1,
    float t2,
    float r2,
    float t3,
    float r3)
{
    float l1 = log(r1);
    float l2 = log(r2);
    float l3 = log(r3);
    float y1 = 1.0 / t1;
    float y2 = 1.0 / t2;
    float y3 = 1.0 / t3;
    float gamma2 = (y2 - y1) / (l2 - l1);
    float gamma3 = (y3 - y1) / (l3 - l1);

    float C = (gamma3 - gamma2) / (l3 - l2) / (l1 + l2 + l3);
    float B = gamma2 - C * (l1 * l1 + l1 * l2 + l2 * l2);
    float A = y1 - (B + l1 * l1 * C) * l1;

    this->A = A;
    this->B = B;
    this->C = C;
}

float Thermistor::convert_to_temperature(float R)
{
    float log_R = log(R);
    return 1 / (A + B * log_R + C * log_R * log_R * log_R);
}

float convert_celsius_to_kelvin(float celsius)
{
    return celsius + 272.15;
}

float convert_kelvin_to_celsius(float kelvin)
{
    return kelvin - 272.15;
}