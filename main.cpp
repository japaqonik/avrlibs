#include "ThreadManager.h"
#include "Encoder.h"

uint64_t millis() { return 0; }

int main()
{
    ResistorHandler rh{2, 3};
    Encoder enc{&rh, 0, 1};
    TaskManager taskMgr{millis};

    taskMgr.addTask(5, enc.pullEncoderPos);
}