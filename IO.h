#include <avr/io.h>


#define INPUT 0x0
#define LOW 0x0
#define HIGH 0x1

void setPinMode(uint8_t pin, uint8_t mode)
{
    switch(mode)
    {
        case INPUT:
            DDRB &= ~(1 << pin);
            PORTB &= ~(1 << pin);
            break;
    }
}

int readPinValue(uint8_t pin)
{
    return PINB & (1<<pin);
}
