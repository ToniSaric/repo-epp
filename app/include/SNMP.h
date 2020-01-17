#ifndef SNMP_H_
#define SNMP_H_

#include <libsnmp.h>
#include "snmp_pp/snmp_pp.h"

class SNMP
{
private:
    /* data */

public:
    SNMP();
    ~SNMP();
    int SNMPGet();
    void SNMPGetNext();
    void SNMPSet();
    void SNMPBulkGet();
    void SNMPResponse();
    void SNMPTrap();
    void SNMPInform();
    void SNMPOpen();
    void SNMPClose();
};




#endif