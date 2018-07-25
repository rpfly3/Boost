#pragma once

class AVRMessage
{
public: 
    enum{header_length = 2048};
    enum{body_length = 2048};
    AVRMessage()
    {

    }
    std::size_t mHeaderLength = header_length;
    std::size_t mMaxBodyLength = body_length;
    char mData[header_length + body_length];

    char* GetHeader()
    {
        return mData;
    }

    char* GetBody()
    {
        return mData + mHeaderLength;
    }
};