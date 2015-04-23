#ifndef RPC_TIMEOUT_H
#define RPC_TIMEOUT_H

#include <string>
#include "PvaException.h"

namespace epics { namespace pvaPy {

/**
 * Rpc timeout error.
 */
class RpcTimeout : public PvaException
{
public:
    RpcTimeout(const std::string& message=""); 
    RpcTimeout(const char* message, ...);
};

}}
#endif 
