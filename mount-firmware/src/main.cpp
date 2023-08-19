#include <Arduino.h>
#include "./steppers/steppers.h"


Stepper stepper0(12, 14, 27, 26, 25, 0, 0, 0);


void setup() {
    stepper0.set_step_mode(Sixteenth);
}

void loop() {
    digitalWrite(12, LOW);
    delayMicroseconds(1000);
    digitalWrite(12, HIGH);
    delayMicroseconds(1000);
}
