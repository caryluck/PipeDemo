// MessageHandler.h

#ifndef __MESSAGE_HANDLER__
#define __MESSAGE_HANDLER__

#include "PipeStream.h"
#include <thread>
#include <mutex>

class MessageHandler {
public:
    MessageHandler(const std::string &reciveName, const std::string &sendName);
    virtual ~MessageHandler();

public:
    void Send(void *data, unsigned int size);
    void Connect();

//private:
    virtual void Handle(int type, void *data);
    void Listen();
    void Recive();

private:
    PipeStream          mReciver;
    PipeStream          mSender;

    std::thread         mListenThread;
    std::thread         mReciveThread;

    BOOL                mRunning;
};

#endif