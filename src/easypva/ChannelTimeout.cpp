#include "epicsStdio.h"
#include "ChannelTimeout.h"


namespace epics { namespace pvaPy {

ChannelTimeout::ChannelTimeout(const std::string& message) :
    PvaException(message)
{
}

ChannelTimeout::ChannelTimeout(const char* message, ...) :
    PvaException()
{
    va_list messageArgs;
    va_start(messageArgs, message);
    char messageBuffer[MaxMessageLength];
    epicsVsnprintf(messageBuffer, MaxMessageLength, message, messageArgs);
    setMessage(std::string(messageBuffer));
    va_end(messageArgs);
}

}}
