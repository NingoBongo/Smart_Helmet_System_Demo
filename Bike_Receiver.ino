// RECEIVER CODE (Bike)

#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver(2000, 0, 11, 2);

int relayPin = 12;

void setup() {

    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, LOW);

    Serial.begin(9600);

    if (!driver.init()) {
        Serial.println("RF init failed");
    }

    Serial.println("Receiver ready...");
}

void loop() {

    uint8_t buf[3];
    uint8_t buflen = sizeof(buf);

    if (driver.recv(buf, &buflen)) {

        Serial.print("Message Received: ");
        Serial.println((char*)buf);

        if (buf[0] == '1' || buf[1] == '1') {

            digitalWrite(relayPin, LOW); // Unsafe → motor OFF
            Serial.println("Unsafe condition detected → Motor OFF");

        } else {

            digitalWrite(relayPin, HIGH); // Safe → motor ON
            Serial.println("Safe condition → Motor ON");
        }
    }
}
