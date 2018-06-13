// MessageHandler.cpp

#include "MessageHandler.h"
#include "PipeStream.h"
#include <thread>

MessageHandler::MessageHandler(const std::string &reciveName, const std::string &sendName) :
    mReciver(reciveName),
    mSender(sendName),
    mRunning(TRUE)
{
    mListenThread = std::move(std::thread(std::bind(&MessageHandler::Listen, this)));
    mReciveThread = std::move(std::thread(std::bind(&MessageHandler::Recive, this)));
}

MessageHandler::~MessageHandler()
{
    mRunning = false;
    mListenThread.detach();
    mReciveThread.detach();
}

void MessageHandler::Send(void *data, unsigned int size)
{
    if (size <= 0)
        return;

    int intSize = sizeof(unsigned int);
    int totalSize = intSize + size;

    std::shared_ptr<char> ptr(new char[totalSize], std::default_delete<char[]>());
    char *buffer = ptr.get();
    memcpy(buffer, &size, intSize);
    memcpy(buffer + intSize, data, size);
    mSender.Write(buffer, totalSize);
}

void MessageHandler::Connect()
{
    int tryCount = 5;
    while (tryCount--) {
        if (mSender.Connect())
            break;

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void MessageHandler::Handle(int type, void *data)
{
}

void MessageHandler::Listen()
{
    while (mRunning) {
        if (mReciver.Accept())
            break;

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

void MessageHandler::Recive()
{
    while (mRunning) {
        // read size
        unsigned int size = 0;
        if (sizeof(int) != mReciver.Read(reinterpret_cast<char*>(&size), sizeof(unsigned int)))
            continue;
        
        // read content
        std::shared_ptr<char> ptr(new char[size], std::default_delete<char[]>());
        char *buffer = ptr.get();
        memset(buffer, 0, size);
        if (size == mReciver.Read(buffer, size)){
            int *data = reinterpret_cast<int *>(buffer);
            int type = *data++;
            Handle(type, reinterpret_cast<void*>(data));
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}