#include "ThreadManager.h"
#include "ResistorHandler.h"
#include "Encoder.h"
#include "RemoteHandler.h"

uint64_t millis() { return 0; }

ResistorHandler rh{2, 3};
Encoder enc{&rh, 0, 1};
RemoteHandler rmH{&rh, 4};
TaskManager taskMgr{millis};

void inputsHanling()
{
    enc.pullEncoderPos();
}

void volumeAdjustment()
{
    rh.updateVolume();
}

int main()
{
    taskMgr.addTask(50, inputsHanling);
    taskMgr.addTask(20, volumeAdjustment);

    taskMgr.executeTasks();
}