#ifndef _STEPPERS_H_
#define _STEPPERS_H_


typedef enum {
    Full      = 0b000,
    Half      = 0b001,
    Quarter   = 0b010,
    Eighth    = 0b011,
    Sixteenth = 0b111,
} StepMode;


class Stepper {
public:
    Stepper(const uint8_t step_pin, const uint8_t dir_pin,
        const uint8_t ms1_pin, const uint8_t ms2_pin, const uint8_t ms3_pin,
        const uint8_t n_en_pin, const uint8_t n_sleep_pin, const uint8_t n_reset_pin);
    void set_step_mode(const StepMode mode);

private:
    uint8_t step_pin;
    uint8_t dir_pin;
    uint8_t ms1_pin;
    uint8_t ms2_pin;
    uint8_t ms3_pin;
    uint8_t n_en_pin;
    uint8_t n_sleep_pin;
    uint8_t n_reset_pin;
};


#endif
