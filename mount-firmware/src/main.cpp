#include <Arduino.h>
#include <math.h>
#include "./steppers/scout_stepper.h"
#include "./pins.h"

typedef enum {
    RightAscension,
    Declination
} Axis;


ScoutStepper *ra_stepper;
ScoutStepper *dec_stepper;

ScoutStepper **steppers[] = { &ra_stepper, &dec_stepper };
Axis next = RightAscension;
hw_timer_t *timer = NULL;
void ARDUINO_ISR_ATTR on_timer();


void setup() {
    Serial.begin(9600);

    Serial.println("\n\nRA stepper init...");
    ra_stepper = new ScoutStepper(ra_pins, MicrostepMode::Full);
    Serial.println("done");

    // TODO: wire up dec stepper hardware
    Serial.println("DEC stepper init...");
    dec_stepper = new ScoutStepper(dec_pins, MicrostepMode::Full);
    dec_stepper->set_rpm(0);
    dec_stepper->set_dir(LOW);
    Serial.println("done");

    Serial.println("timer init...");
    double timer_resolution_s = 1e-6;       // 1e-6 means 1 us resolution
    uint16_t timer_divider = APB_CLK_FREQ * timer_resolution_s;
    timer = timerBegin(3, timer_divider, true);
    if (timer == NULL) {
        Serial.println("timer setup failed - timer is NULL");
    }
    timerAttachInterrupt(timer, &on_timer, false);
    Serial.println("done");

    ra_stepper->set_rpm(5);
    timerAlarmWrite(timer, 100, false);
    timerAlarmEnable(timer);
    ra_stepper->set_dir(LOW);
}

uint64_t i;

void loop() {
    Serial.println(i);
    delay(500);
}


void ARDUINO_ISR_ATTR on_timer() {
    i++;
    (*steppers[next])->step();

    uint64_t min_time = UINT64_MAX;

    for (int i = 0; i < sizeof(steppers)/sizeof(steppers[0]); i++) {
        uint64_t t = (*steppers[i])->get_next_step_time();
        if (t < min_time) {
            min_time = t;
            next = (Axis) i;
        }
    }


    // setup next interrupt
    timerAlarmWrite(timer, min_time, false);
    timerAlarmEnable(timer);
}
