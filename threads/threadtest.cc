#include "kernel.h"
#include "main.h"
#include "math.h"
#include "thread.h"
#include "redblacktree.h"

using namespace std;

void SimpleThread(int which)
{
    int num;

    for (num = 0; num < 5; num++)
    {
        printf("*** thread %d looped %d times\n", which, num);
        kernel->currentThread->Yield();
    }
}

// reads the data from file
void IORead()
{
    cout << "Reading request received from thread " << kernel->currentThread->getName() << endl;
    IORequest *ioRequest = new IORequest("File message", false, kernel->currentThread);
    kernel->pendingIO->Insert(ioRequest);
    cout << "Interrupt scheduled to occur at " << ioRequest->getCompleteTime() << endl
         << endl;
    kernel->interrupt->Schedule(kernel->ioalarm, ioRequest->getWaitTime(), IOInt);
    kernel->currentThread->startTime = 0;
    kernel->interrupt->SetLevel(IntOff);
    kernel->currentThread->Sleep(false);
    delete ioRequest;
}

// write the data to file
void IOWrite(string msg)
{
    cout << "Writing request received from thread " << kernel->currentThread->getName() << endl;
    IORequest *ioRequest = new IORequest(msg, true, kernel->currentThread);
    kernel->pendingIO->Insert(ioRequest);
    cout << "Interrupt scheduled to occur at " << ioRequest->getCompleteTime() << endl
         << endl;
    kernel->interrupt->Schedule(kernel->ioalarm, ioRequest->getWaitTime(), IOInt);
    kernel->currentThread->startTime = 0;
    kernel->interrupt->SetLevel(IntOff);
    kernel->currentThread->Sleep(false);
    delete ioRequest;
}

// manage CPU intensive operations
void CPUBound()
{
    cout << "CPU request received from thread " << kernel->currentThread->getName() << endl;
    for (int i = 0; i < 15; i++)
    {
        cout << "Incrementing counter from " << kernel->currentThread->getName() << ": " << i << endl;
        kernel->interrupt->SetLevel(IntOff);
        kernel->interrupt->SetLevel(IntOn);
    }
}

// IOIntensive Thread for read
void IOThread()
{
    cout << endl;
    IORead();
}

// IOIntensive Thread for write
void IOThread1()
{
    cout << endl;
    IOWrite("Message for Writing from IOThread");
}

// CPU Intensive Thread
void CPUThread()
{
    cout << endl;
    CPUBound();
}

// Hybrid Thread for CPU and IO operations
void HybridThread()
{
    cout << endl;
    IOWrite("Message for Writing from hybrid thread");
    CPUBound();
}

// Hybrid Thread for CPU and IO operations
void HybridThread1()
{
    cout << endl;
    IORead();
    CPUBound();
}

// Forks IO and CPU threads
void ThreadTest()
{
    srand(time(NULL));
    kernel->currentThread->Yield();

    Thread *readThread = new Thread("Read Thread");
    readThread->Fork((VoidFunctionPtr)IOThread, (void *)1);

    Thread *writeThread = new Thread("Write Thread");
    writeThread->Fork((VoidFunctionPtr)IOThread1, (void *)1);

    Thread *cpuThread = new Thread("CPU Thread");
    cpuThread->Fork((VoidFunctionPtr)CPUThread, (void *)1);

    Thread *hybridThread = new Thread("Hybrid Thread");
    hybridThread->Fork((VoidFunctionPtr)HybridThread, (void *)1);

    Thread *readThread1 = new Thread("Read Thread1");
    readThread1->Fork((VoidFunctionPtr)IOThread, (void *)1);

    Thread *writeThread1 = new Thread("Write Thread1");
    writeThread1->Fork((VoidFunctionPtr)IOThread1, (void *)1);

    Thread *cpuThread1 = new Thread("CPU Thread1");
    cpuThread1->Fork((VoidFunctionPtr)CPUThread, (void *)1);

    Thread *hybridThread1 = new Thread("Hybrid Thread1");
    hybridThread1->Fork((VoidFunctionPtr)HybridThread1, (void *)1);

    Thread *readThread2 = new Thread("Read Thread2");
    readThread2->Fork((VoidFunctionPtr)IOThread, (void *)1);

    Thread *writeThread2 = new Thread("Write Thread2");
    writeThread2->Fork((VoidFunctionPtr)IOThread1, (void *)1);

    Thread *cpuThread2 = new Thread("CPU Thread2");
    cpuThread2->Fork((VoidFunctionPtr)CPUThread, (void *)1);

    Thread *hybridThread2 = new Thread("Hybrid Thread2");
    hybridThread2->Fork((VoidFunctionPtr)HybridThread, (void *)1);

    Thread *readThread3 = new Thread("Read Thread3");
    readThread3->Fork((VoidFunctionPtr)IOThread, (void *)1);

    Thread *writeThread3 = new Thread("Write Thread3");
    writeThread3->Fork((VoidFunctionPtr)IOThread1, (void *)1);

    Thread *cpuThread3 = new Thread("CPU Thread3");
    cpuThread3->Fork((VoidFunctionPtr)CPUThread, (void *)1);

    Thread *hybridThread3 = new Thread("Hybrid Thread3");
    hybridThread3->Fork((VoidFunctionPtr)HybridThread1, (void *)1);

    Thread *readThread4 = new Thread("Read Thread4");
    readThread4->Fork((VoidFunctionPtr)IOThread, (void *)1);

    Thread *writeThread4 = new Thread("Write Thread4");
    writeThread4->Fork((VoidFunctionPtr)IOThread1, (void *)1);

    Thread *cpuThread4 = new Thread("CPU Thread4");
    cpuThread4->Fork((VoidFunctionPtr)CPUThread, (void *)1);

    Thread *hybridThread4 = new Thread("Hybrid Thread4");
    hybridThread4->Fork((VoidFunctionPtr)HybridThread, (void *)1);

    Thread *writeThread5 = new Thread("Write Thread5");
    writeThread5->Fork((VoidFunctionPtr)IOThread1, (void *)1);

    Thread *hybridThread5 = new Thread("Hybrid Thread5");
    hybridThread5->Fork((VoidFunctionPtr)HybridThread1, (void *)1);

    kernel->currentThread->Yield();

    for (int i = 0; i < 50; i++)
    {
        kernel->interrupt->SetLevel(IntOff);
        kernel->interrupt->SetLevel(IntOn);
    }

    /*Thread *t = new Thread("forked thread");
    t->Fork((VoidFunctionPtr) SimpleThread, (void *) 1);
    
    SimpleThread(0);*/
}
