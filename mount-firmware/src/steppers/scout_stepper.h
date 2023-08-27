#ifndef _SCOUT_STEPPER_H_
#define _SCOUT_STEPPER_H_

#include <Arduino.h>
#include <array>

#define FULL_STEPS_PER_REV      200


typedef enum {
    Full      = 0b000,
    Half      = 0b001,
    Quarter   = 0b010,
    Eighth    = 0b011,
    Sixteenth = 0b111,
} MicrostepMode;


typedef struct {
    uint8_t step_pin;
    uint8_t dir_pin;
    uint8_t ms1_pin;
    uint8_t ms2_pin;
    uint8_t ms3_pin;
    uint8_t n_sleep_pin;
    uint8_t n_reset_pin;
    uint8_t n_enable_pin;
} ScoutStepperPins;


class ScoutStepper {
public:
    ScoutStepper(ScoutStepperPins pins, MicrostepMode ms);
    MicrostepMode get_microstep_mode(void);
    void set_microstep_mode(MicrostepMode ms);
    uint16_t get_pulses_per_rev(void);

    void set_rpm(double rpm);
    double get_rpm(void);
    void set_dir(uint8_t val);
    uint8_t get_dir(void);
    uint64_t get_step_period_us(void);
    uint64_t get_next_step_time(void);
    bool is_stopped(void);

    void step(void);
protected:
    ScoutStepperPins pins;
private:
    MicrostepMode microstep_mode;
    uint64_t step_period_us;
    uint64_t next_step_us;
    uint8_t dir;
};

#endif
