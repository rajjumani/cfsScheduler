#include "main.h"

// called at each IO interrupt and executes all interrupts from pending queue which are handled by Handler
void IOAlarm::CallBack()
{
    IOHandler handler;
    while (!kernel->pendingIO->IsEmpty() && kernel->pendingIO->Front()->getCompleteTime() <= kernel->stats->totalTicks)
    {
        IORequest *currReq = kernel->pendingIO->RemoveFront();
        cout << "IO Interrupt occurred from " << currReq->getReqThread()->getName() << endl;
        if (currReq->getOpType() == "write")
        {
            handler.write();
            cout << " '" << currReq->getContent() << "' from thread " << currReq->getReqThread()->getName() << endl
                 << endl;
            kernel->interrupt->YieldOnReturn();
        }
        else
        {
            handler.read();
            cout << " '" << currReq->getContent() << "' from thread " << currReq->getReqThread()->getName() << endl
                 << endl;
            kernel->interrupt->YieldOnReturn();
        }
        kernel->scheduler->ReadyToRun(currReq->getReqThread());
    }
}