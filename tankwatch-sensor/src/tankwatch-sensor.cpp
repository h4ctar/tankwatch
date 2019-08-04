/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "application.h"
#line 1 "c:/Users/Ben/dev/nice/nice/src/nice.ino"
#include "Adafruit_DHT.h"

void setup();
void loop();
#line 3 "c:/Users/Ben/dev/nice/nice/src/nice.ino"
#define DHT_PIN D7
#define TRIG_PIN D1
#define ECHO_PIN D0

DHT dht(DHT_PIN, DHT22, 40);

void setup()
{
    dht.begin();

    pinMode(ECHO_PIN, INPUT);
    pinMode(TRIG_PIN, OUTPUT);

    delay(1000);
}

void loop()
{
    float humidity = dht.getHumidity();
    float temperature = dht.getTempCelcius();

    // Clears the TRIG_PIN
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    // Sets the TRIG_PIN on HIGH state for 10 micro seconds
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    long duration = pulseIn(ECHO_PIN, HIGH);
    // Calculating the distance
    float distance = duration * 0.034 / 2;

    char json[100];
    sprintf(json, "{ \"humidity\": %f, \"temperature\": %f, \"distance\": %f }", humidity, temperature, distance);
    Particle.publish("reading", json, PRIVATE);

    System.sleep(SLEEP_MODE_SOFTPOWEROFF, 60 * 60);
}
