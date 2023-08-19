#include <Arduino.h>
#include "./steppers.h"


Stepper::Stepper(const uint8_t step_pin, const uint8_t dir_pin,
        const uint8_t ms1_pin, const uint8_t ms2_pin, const uint8_t ms3_pin,
        const uint8_t n_en_pin, const uint8_t n_sleep_pin, const uint8_t n_reset_pin) {

    this->step_pin = step_pin;
    this->dir_pin = dir_pin;
    this->ms1_pin = ms1_pin;
    this->ms2_pin = ms2_pin;
    this->ms3_pin = ms3_pin; 
    this->n_en_pin = n_en_pin;
    this->n_sleep_pin = n_sleep_pin;
    this->n_reset_pin = n_reset_pin;

    pinMode(step_pin, OUTPUT);
    pinMode(dir_pin, OUTPUT);
    pinMode(ms1_pin, OUTPUT);
    pinMode(ms2_pin, OUTPUT);
    pinMode(ms3_pin, OUTPUT);
    pinMode(n_en_pin, OUTPUT);
    pinMode(n_sleep_pin, OUTPUT);
    pinMode(n_reset_pin, OUTPUT);

    digitalWrite(step_pin, LOW);
    digitalWrite(dir_pin, LOW);
    digitalWrite(ms1_pin, LOW);
    digitalWrite(ms2_pin, LOW);
    digitalWrite(ms3_pin, LOW);
    digitalWrite(n_en_pin, LOW);
    digitalWrite(n_sleep_pin, LOW);
    digitalWrite(n_reset_pin, LOW);
}


void Stepper::set_step_mode(const StepMode mode) {
    digitalWrite(ms1_pin, (mode >> 0) & 0b001);
    digitalWrite(ms2_pin, (mode >> 1) & 0b001);
    digitalWrite(ms3_pin, (mode >> 2) & 0b001);
}


