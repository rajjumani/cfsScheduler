#include "main.h"

// Constructor - generate new IO request with random wait time
IORequest::IORequest(string msg, bool writeFlag, Thread *reqThreadPtr)
{
    int randTime;
    if (writeFlag)
    {
        setOpType("write");
        randTime = rand() % 50 + 20;
    }
    else
    {
        setOpType("read");
        randTime = rand() % 30 + 80;
    }
    setContent(msg);
    setWaitTime(randTime);
    setCompleteTime(kernel->stats->totalTicks + randTime);
    setReqThread(reqThreadPtr);
}

// ---------------------< Getters and Setters >------------------------------
void IORequest::setWaitTime(int time)
{
    waitTime = time;
}
int IORequest::getWaitTime()
{
    return waitTime;
}
void IORequest::setCompleteTime(int time)
{
    completeTime = time;
}

int IORequest::getCompleteTime()
{
    return completeTime;
}
void IORequest::setOpType(string oprType)
{
    opType = oprType;
}
string IORequest::getOpType()
{
    return opType;
}

void IORequest::setReqThread(Thread *reqThreadPtr)
{
    threadPtr = reqThreadPtr;
}

Thread *IORequest::getReqThread()
{
    return threadPtr;
}

void IORequest::setContent(string msg)
{
    content = msg;
}

string IORequest::getContent()
{
    return content;
}