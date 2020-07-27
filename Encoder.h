#include "IO.h"

class Encoder
{
private:
    uint8_t pinA;
    uint8_t pinB;

    uint8_t pinALastState = LOW;

    uint8_t pos = 0;

public:
    Encoder(uint8_t _pinA, uint8_t _pinB) : pinA{_pinA}, pinB{_pinB}
    {
        setPinMode(_pinA, INPUT);
        setPinMode(_pinB, INPUT);
    }

    void pullEncoderState()
    {
        auto currentPinAState = readPinValue(pinA);
        if (pinALastState == LOW && currentPinAState == HIGH)
        {
            if (readPinValue(pinB) == LOW)
            {
                if (pos > 0)
                {
                    pos--;
                }
            }
            else
            {
                if (pos < 255)
                {
                    pos++;
                }
            }
            pinALastState = currentPinAState;
        }
    }

    uint8_t getEncoderPosition()
    {
        return pos;
    }
};