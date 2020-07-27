#include <inttypes.h>
#include "inc/IRremote/IRremote.h"
#include "ResistorHandlerIf.h"

class RemoteHandler
{
private:
    IRrecv irrecv;
    decode_results result;

    IResistorHandler *resitorHandler;

public:
    RemoteHandler(IResistorHandler *_resitorHandler, uint8_t pin) : resitorHandler{_resitorHandler}, irrecv{pin}
    {
        irrecv.enableIRIn();
    }
    void handleRemoteComand()
    {
        if(irrecv.decode(&result))
        {
            switch(result.value)
            {
                case 0x0:
                    resitorHandler->volumeUp();
                    break;
                case 0x1:
                    resitorHandler->volumeDown();
                    break;
            }
            irrecv.resume();
        }
    }
};