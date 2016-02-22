
#include <hal.h>

const uint8_t pin_table[8] = {
    GPIOD_PIN3,
    GPIOD_PIN4,
    GPIOD_PIN5,
    GPIOD_PIN6,
    GPIOD_PIN7,
    GPIOD_PIN8,
    GPIOD_PIN9,
    GPIOD_PIN10
}

void trace_toggle(unsigned int pin)
{
    if (pin < sizeof(pin_table)) {
        palTogglePad(GPIOD, pin_table[pin]);
    }
}

void trace_set(unsigned int pin)
{
    if (pin < sizeof(pin_table)) {
        palSetPad(GPIOD, pin_table[pin]);
    }
}

void trace_clear(unsigned int pin)
{
    if (pin < sizeof(pin_table)) {
        palClearPad(GPIOD, pin_table[pin]);
    }
}
