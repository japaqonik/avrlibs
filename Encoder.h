#include <avr/io.h>
#include "ResistorHandlerIf.h"

#define LOW_STATE 0x0

class Encoder
{
private:
    uint8_t pinA;
    uint8_t pinB;

    uint8_t pinALastState;

    uint8_t pos = 0;

    IResistorHandler *resitorHandler;

    void setPinInputMode(uint8_t pin)
    {
        DDRB &= ~(1 << pin);
        PORTB &= ~(1 << pin);
    }

    int readPinValue(uint8_t pin)
    {
        return PINB & (1 << pin);
    }

public:
    Encoder(IResistorHandler *_resitorHandler, uint8_t _pinA, uint8_t _pinB) : pinA{_pinA}, pinB{_pinB}, resitorHandler{_resitorHandler}
    {
        setPinInputMode(_pinA);
        setPinInputMode(_pinB);
        pinALastState = readPinValue(pinA);
    }

    void pullEncoderPos()
    {
        auto currentPinAState = readPinValue(pinA);
        if (pinALastState != currentPinAState)
        {
            if (readPinValue(pinB) != currentPinAState)
            {
                resitorHandler->volumeUp();
            }
            else
            {
                resitorHandler->volumeDown();
            }
        }
        pinALastState = currentPinAState;
    }
};