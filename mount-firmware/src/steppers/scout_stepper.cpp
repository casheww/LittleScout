#include "./scout_stepper.h"


ScoutStepper::ScoutStepper(ScoutStepperPins pins, MicrostepMode ms) {
    this->pins = pins;

    pinMode(pins.step_pin, OUTPUT);
    pinMode(pins.dir_pin, OUTPUT);
    pinMode(pins.ms1_pin, OUTPUT);
    pinMode(pins.ms2_pin, OUTPUT);
    pinMode(pins.ms3_pin, OUTPUT);
    pinMode(pins.n_sleep_pin, OUTPUT);
    pinMode(pins.n_reset_pin, OUTPUT);
    pinMode(pins.n_enable_pin, OUTPUT);

    set_microstep_mode(ms);
    digitalWrite(pins.step_pin, LOW);
    digitalWrite(pins.dir_pin, LOW);
    digitalWrite(pins.n_sleep_pin, LOW);
    digitalWrite(pins.n_reset_pin, LOW);
}


void ScoutStepper::set_microstep_mode(MicrostepMode ms) {
    microstep_mode = ms;
    digitalWrite(pins.ms1_pin, (ms >> 0) & 1);
    digitalWrite(pins.ms2_pin, (ms >> 1) & 1);
    digitalWrite(pins.ms3_pin, (ms >> 2) & 1);
}


MicrostepMode ScoutStepper::get_microstep_mode(void) {
    return microstep_mode;
}


uint16_t ScoutStepper::get_pulses_per_rev(void) {
    uint16_t div;
    switch (microstep_mode) {
        defualt:
        case Full:
            div = 1;
            break;
        case Half:
            div = 2;
            break;
        case Quarter:
            div = 4;
            break;
        case Eighth:
            div = 8;
            break;
        case Sixteenth:
            div = 16;
            break;
    }
    return FULL_STEPS_PER_REV * div;
}


void ScoutStepper::set_rpm(double rpm) {
    if (rpm == 0) {
        step_period_us = 0;
        return;
    }

    double rev_hz = rpm / 60.0;
    double step_hz = rev_hz * get_pulses_per_rev();
    step_period_us = 1e6 / step_hz;

    next_step_us = micros() + step_period_us;
}

double ScoutStepper::get_rpm(void) {
    if (step_period_us == 0) {
        return 0;
    }

    double step_hz = 1e6 / step_period_us;
    double rev_hz = step_hz / get_pulses_per_rev();
    return rev_hz * 60.0;
}

void ScoutStepper::set_dir(uint8_t v) {
    dir = v & HIGH;
    digitalWrite(pins.dir_pin, dir);
}

uint8_t ScoutStepper::get_dir(void) {
    return dir & HIGH;
}

uint64_t ScoutStepper::get_step_period_us(void) {
    return step_period_us;
}

uint64_t ScoutStepper::get_next_step_time(void) {
    return next_step_us;
}

bool ScoutStepper::is_stopped(void) {
    return get_rpm() == 0;
}


void ScoutStepper::step(void) {
    next_step_us += step_period_us;
    digitalWrite(pins.step_pin, HIGH);
    delayMicroseconds(1);
    digitalWrite(pins.step_pin, LOW);
}
