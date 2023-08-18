#include <Arduino.h>
#include "./steppers/steppers.h"

#define DIR     14
#define STEP    12


void setup() {
    pinMode(DIR, OUTPUT);
    pinMode(STEP, OUTPUT);
    digitalWrite(DIR, LOW);
}

void loop() {
    digitalWrite(STEP, LOW);
    delayMicroseconds(1000);
    digitalWrite(STEP, HIGH);
    delayMicroseconds(1000);
}
