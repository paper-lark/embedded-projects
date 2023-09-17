#pragma once

struct Thermistor
{
public:
    /**
     * @brief Construct a new Thermistor object
     *
     * @param t1 lowest temperature (in Kelvin)
     * @param r1 resistance at T1
     * @param t2 normal temperature (in Kelvin)
     * @param r2 resistance at T2
     * @param t3 highest temperature (in Kelvin)
     * @param r3 resistance at T3
     */
    Thermistor(
        float t1,
        float r1,
        float t2,
        float r2,
        float t3,
        float r3);

    /**
     * @brief Calculate temperature from resistance on the thermistor using [Steinhart-Hart equation](https://www.allaboutcircuits.com/industry-articles/how-to-obtain-the-temperature-value-from-a-thermistor-measurement/).
     *
     * @param R thermistor resistance
     * @return float calculated temperature (in Kelvin)
     */
    float convert_to_temperature(float R);

private:
    float A;
    float B;
    float C;
};

/**
 * @brief Convert temperature from Celsius to Kelvin
 *
 * @param celsius temperature in Celsius
 * @return float temperature in Kelvin
 */
float convert_celsius_to_kelvin(float celsius);

/**
 * @brief  Convert temperature from Kelvin to Celsius
 *
 * @param kelvin temperature in Kelvin
 * @return float temperature in Celsius
 */
float convert_kelvin_to_celsius(float kelvin);
