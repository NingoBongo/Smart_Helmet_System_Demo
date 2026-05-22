// TRANSMITTER CODE (Helmet)

#include <RH_ASK.h>
#include <SPI.h> // Required by RH_ASK

int mq3Pin = A0;
int irHelmetPin = 3;
int buzzerPin = 12;

int mq3Value = 0;
int irHelmetValue = 0;

int alcoholThreshold = 900;

RH_ASK driver(2000, 11, 0, 2);

void setup() {
    pinMode(irHelmetPin, INPUT_PULLUP);
    pinMode(buzzerPin, OUTPUT);

    Serial.begin(9600);

    if (!driver.init()) {
        Serial.println("RF init failed");
    }

    delay(2000);
}

void loop() {

    mq3Value = analogRead(mq3Pin);
    irHelmetValue = digitalRead(irHelmetPin);

    Serial.print("Alcohol: ");
    Serial.print(mq3Value);

    Serial.print(" Helmet IR: ");
    Serial.println(irHelmetValue);

    bool unsafeCondition = false;

    if (mq3Value > alcoholThreshold)
        unsafeCondition = true;

    if (irHelmetValue == LOW)
        unsafeCondition = true;

    digitalWrite(buzzerPin, unsafeCondition ? HIGH : LOW);

    char msg[3];

    msg[0] = (mq3Value > alcoholThreshold) ? '1' : '0';
    msg[1] = (irHelmetValue == LOW) ? '1' : '0';
    msg[2] = '\0';

    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();

    delay(500);
}
