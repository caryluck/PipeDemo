// PipeServer.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "..\MessageHandler.h"
#include "..\PipeStream.h"
#include <iostream>
#include "../SmServerMessageHandler.h"

using namespace std;

int main(int argc, const char **argv)
{
    SmServerMessageHandler handler("\\\\.\\pipe\\a_pipe", "\\\\.\\pipe\\b_pipe");

    Sleep(1000000000);
    return 0;
}