// PipeClient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "../MessageHandler.h"
#include "../PipeStream.h"
#include "../SmClientMessageHandler.h"

#include <iostream>
#include <windows.h>
using namespace std;

int main(int argc, const char **argv)
{
    SmClientMessageHandler handler("\\\\.\\pipe\\b_pipe", "\\\\.\\pipe\\a_pipe");
    int value = 0;
    handler.Send(reinterpret_cast<void*>(&value), 4);

    Sleep(1000000000);

    return 0;
}