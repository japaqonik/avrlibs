#include <inttypes.h>
#include "vector.h"

struct TaskData
{
public:
    uint16_t taskId;
    uint16_t interval;
    void (*callbackFuntion)(void);
};

class TaskManager
{
private:
    avr::vector<TaskData> _tasks;
    uint64_t _prevTime = 0;
    uint16_t __current_avail_index = 0;

    uint64_t (*getTimeFuncPtr)(void) = 0;

    bool isReadyToCall(uint16_t _interval)
    {
        return getTimeFuncPtr() - _prevTime >= _interval;
    }

public:
    TaskManager(uint64_t (*_getTimeFuncPtr)(void)) : getTimeFuncPtr{_getTimeFuncPtr} {}
    uint16_t addTask(uint16_t _interval, void (*_callbackFunct)(void))
    {
        TaskData task;
        task.taskId = __current_avail_index++;
        task.interval = _interval;
        task.callbackFuntion = _callbackFunct;
        _tasks.push_back(task);

        return task.taskId;
    }
    uint16_t addTask(void (*_callbackFunct)(void))
    {
        return addTask(0, _callbackFunct);
    }
    void executeTasks()
    {
        for (uint16_t i = 0; i < _tasks.size(); i++)
        {
            if (isReadyToCall(_tasks[i].interval))
            {
                _tasks[i].callbackFuntion();
            }
        }
    }
    void removeTask(uint16_t _taskId)
    {
        uint32_t index = UINT32_MAX;
        for (uint16_t i = 0; i < _tasks.size(); i++)
        {
            if (_tasks[i].taskId == _taskId)
            {
                index = i;
            }
        }

        if (index != UINT32_MAX)
        {
            _tasks.erase(index);
        }
    }
};