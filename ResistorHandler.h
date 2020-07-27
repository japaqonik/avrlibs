#ifndef RESISTOR_HANDLER_H
#define RESISTOR_HANDLER_H

#include <inttypes.h>
#include <avr/io.h>

class IResistorHandler
{
public:
    virtual void volumeUp(){};
    virtual void volumeDown(){};
};

class ResistorHandler : public IResistorHandler
{
private:
    uint8_t pinResistanceDown;
    uint8_t pinResistanceUp;

    int16_t callQueue = 0;

    bool isUpdateOngoing = false;
    bool volumeUpUpdate = false;

    void setPinStateHigh(uint8_t pin)
    {
        PORTB |= (1 << pin);
    }

    void setPinStateLow(uint8_t pin)
    {
        PORTB &= ~(1 << pin);
    }

    void setPinOutputMode(uint8_t pin)
    {
        DDRB |= (1 << pin);
        setPinStateHigh(pin);
    }

public:
    ResistorHandler(uint8_t _pinResistanceDown, uint8_t _pinResistanceUp)
        : pinResistanceDown{_pinResistanceDown}, pinResistanceUp{_pinResistanceUp}
    {
        setPinOutputMode(pinResistanceDown);
        setPinOutputMode(pinResistanceUp);
    }
    void updateVolume()
    {
        if (!isUpdateOngoing)
        {
            if (callQueue > 0)
            {
                setPinStateLow(pinResistanceDown);
                volumeUpUpdate = true;
                isUpdateOngoing = true;
            }
            else if (callQueue < 0)
            {
                setPinStateLow(pinResistanceUp);
                volumeUpUpdate = false;
                isUpdateOngoing = true;
            }
        }
        else
        {
            setPinStateLow(volumeUpUpdate ? pinResistanceDown : pinResistanceUp);
            isUpdateOngoing = false;
        }
    }
    void volumeUp() override
    {
        ++callQueue;
    }
    void volumeDown() override
    {
        --callQueue;
    }
};

#endif