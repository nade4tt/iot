#include "DHT.h"
#define DHT11_PIN 2

DHT dht11(DHT11_PIN, DHT11);

void setup() {
    Serial.begin(9600);
    dht11.begin(); // initialize the sensor
}

void loop() {
    float humidity = dht11.readHumidity();
    float temp_degc = dht11.readTemperature();

    // check if any reads failed
    if (isnan(humidity) || isnan(temp_degc)) {
        Serial.println("Failed to read from DHT11 sensor!");
    } else {
        Serial.print("DHT11# Humidity: ");
        Serial.print(humidity);
        Serial.print("%");

        Serial.print("  |  ");

        Serial.print("Temperature: ");
        Serial.print(temp_degc);
        Serial.print("°C ~ ");
        Serial.println("°F");
    }

    delay(10000);
}
