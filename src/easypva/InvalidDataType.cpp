#include "epicsStdio.h"
#include "InvalidDataType.h"


namespace epics { namespace pvaPy {

InvalidDataType::InvalidDataType(const std::string& message) :
    PvaException(message)
{
}

InvalidDataType::InvalidDataType(const char* message, ...) :
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
