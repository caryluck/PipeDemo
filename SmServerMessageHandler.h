// SmServerMessageHandler

#ifndef __SM_SERVER_MESSAGE_HANDLER__
#define __SM_SERVER_MESSAGE_HANDLER__

#include "MessageHandler.h"
#include <iostream>

class SmServerMessageHandler : public MessageHandler {
public:
    SmServerMessageHandler(const std::string &reciveName, const std::string &sendName) :
        MessageHandler(reciveName, sendName)
    {
    }

    ~SmServerMessageHandler()
    {
    }

public:
    void Handle(int type, void *data)
    {
        switch (type)
        {
        case 0:
        {
            std::cout << type << std::endl;

            Connect();
            int value = 1;
            Send(reinterpret_cast<void*>(&value), 4);
            break;
        }
        case 1:
        {
            std::cout << type << std::endl;
            int value = 2;
            Send(reinterpret_cast<void*>(&value), 4);
            break;
        }
        case 2:
        {
            std::cout << type << std::endl;
            int value = 3;
            Send(reinterpret_cast<void*>(&value), 4);
            break;
        }
        default:
            break;
        }
    }
};

#endif