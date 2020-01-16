#ifndef SNMP_H_
#define SNMP_H_
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>

class SNMP
{
private:
    /* data */
    struct snmp_pdu *pdu;
    struct snmp_pdu *response;
    struct snmp_session session;
    struct snmp_session *session_handle;
public:
    SNMP();
    ~SNMP();
    int SNMPGet(const oid Oid[], size_t len);
    void SNMPGetNext();
    void SNMPSet();
    void SNMPBulkGet();
    void SNMPResponse();
    void SNMPTrap();
    void SNMPInform();
    void SNMPInit();
};




#endif