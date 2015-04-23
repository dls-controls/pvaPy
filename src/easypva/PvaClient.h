#ifndef PVA_CLIENT_H
#define PVA_CLIENT_H

namespace epics { namespace pvaPy {

/**
 * PV access client.
 */
class PvaClient 
{
public:
    PvaClient();
    virtual ~PvaClient();
private:
    // Use this class to make sure client factory is always
    // properly started/stopped.
    class ClientFactoryController {
    public:
        ClientFactoryController();
        ~ClientFactoryController();
    };
    static ClientFactoryController clientFactoryController;
};

}}
#endif
