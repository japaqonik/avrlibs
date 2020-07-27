#include <inttypes.h>
#include <avr/io.h>

class IResistorHandler
{
public:
    virtual void volumeUp() {};
    virtual void volumeDown() {};
};

class ResistorHandler : public IResistorHandler
{
private:
    uint8_t pinResistanceDown;
    uint8_t pinResistanceUp;

    int16_t callQueue = 0;

    void setPinOutputMode(uint8_t pin)
    {
        DDRB |= (1 << pin);
        PORTB |= (1 << pin);
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