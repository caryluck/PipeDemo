// PipeStream.cpp

#include "PipeStream.h"
#include <windows.h>

PipeStream::PipeStream(const std::string &name) :
    mPipeName(name),
    mPipe(NULL)
{
}

PipeStream::~PipeStream()
{
    if (mPipe && mPipe != INVALID_HANDLE_VALUE)
        CloseHandle(mPipe);
}


BOOL PipeStream::Accept()
{
    if (mPipe && mPipe != INVALID_HANDLE_VALUE)
        return TRUE;

    // Create a pipe to send data
    mPipe = CreateNamedPipeA(
        mPipeName.c_str(), // name of the pipe
        PIPE_ACCESS_DUPLEX, // 2-way pipe -- send and recive
        PIPE_TYPE_BYTE, // send data as a byte stream
        1, // only allow 1 instance of this pipe
        0, // no outbound buffer
        0, // no inbound buffer
        0, // use default wait time
        NULL // use default security attributes
    );

    if (mPipe == INVALID_HANDLE_VALUE)
        return FALSE;

    // This call blocks until a client process connects to the pipe
    if (!ConnectNamedPipe(mPipe, NULL)) {
        CloseHandle(mPipe); // close the pipe
        return FALSE;
    }

    return TRUE;
}

BOOL PipeStream::Connect()
{
    if (mPipe && mPipe != INVALID_HANDLE_VALUE)
        return TRUE;

    mPipe = CreateFileA(
        mPipeName.c_str(),
        GENERIC_READ | GENERIC_WRITE, // only need read access
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (mPipe == INVALID_HANDLE_VALUE)
        return FALSE;

    return TRUE;
}

unsigned int PipeStream::Write(const char *data, unsigned int size)
{
    unsigned int residue = size;
    while (residue > 0) {
        DWORD write = 0;
        if (!WriteFile(mPipe, data + (size - residue), residue, &write, NULL))
            return -1;

        residue -= write;
    }

    return size;
}
    
unsigned int PipeStream::Read(char *data, unsigned int size)
{
    unsigned int residue = size;

    while (residue > 0) {
        DWORD read = 0;
        if (!ReadFile(mPipe, data + (size - residue), size, &read, NULL))
            return -1;

        residue -= read;
    }

    return size;
}