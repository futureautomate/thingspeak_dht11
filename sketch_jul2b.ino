#include "DHT.h"
#define DHTPIN 2 // what pin we're connected to
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);

void setup() 
{
    Serial.begin(9600);
    dht.begin();
}

void loop() {

    // Wait a few seconds between measurements.
    delay(2000);

    float h = dht.readHumidity();
    // Read temperature as Celsius
    float t = dht.readTemperature();
    // Read temperature as Fahrenheit
    float f = dht.readTemperature(true);

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
    }

    // Compute heat index
    // Must send in temp in Fahrenheit!
    float hi = dht.computeHeatIndex(f, h);

    // Serial.print("Humidity: ");
    // Serial.print(h);
    // Serial.print(",");
    // Serial.print("Temperature *C : ");
    // Serial.print(t);
    // Serial.print(",");
    // Serial.print("*F");
    // Serial.print(f);
    // Serial.print(",");
    // Serial.print("Heat index: *F ");
    // Serial.print(hi);
    
    Serial.print("Humidity:");
    Serial.print(h);
    Serial.print(",");
    Serial.print("*C:");
    Serial.print(t);
    Serial.print(",");
    Serial.print("*F:");
    Serial.print(f);
    Serial.print(",");
    Serial.print("HeatIndex:");
    Serial.println(hi);
} 