// PipeStream.h

#ifndef __PIPE_STREAM_H__
#define __PIPE_STREAM_H__

#include <windows.h>
#include <string>


class PipeStream {
public:
    PipeStream(const std::string &name);
    ~PipeStream();

public:
    BOOL Accept();
    BOOL Connect();
    unsigned int Write(const char *data, unsigned int size);    
    unsigned int Read(char *data, unsigned int size);

public:
    std::string                 mPipeName;
    HANDLE                      mPipe;
};

#endif // !__PIPE_STREAM_H__