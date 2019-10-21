#include "callback.h"

class IOAlarm : public CallBackObj
{
private:
    void CallBack(); // called when the hardware
                     // timer generates an interrupt
public:
    IOAlarm() {}
    ~IOAlarm() {}
};