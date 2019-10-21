class IORequest
{
private:
    int waitTime;
    int completeTime;
    string content;
    string opType;
    Thread *threadPtr;

public:
    IORequest(string msg, bool type, Thread *ptr);
    void setWaitTime(int time);
    int getWaitTime();
    void setCompleteTime(int time);
    int getCompleteTime();
    void setReqThread(Thread *reqThreadPtr);
    Thread *getReqThread();
    void setOpType(string opType);
    string getOpType();
    void setContent(string msg);
    string getContent();
};
