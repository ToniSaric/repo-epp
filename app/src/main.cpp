#include <iostream>
//#include "SNMP.h"
#include "OID.h"
#include <libsnmp.h>
#include <snmp_pp/snmp_pp.h>

void callback(int reason, Snmp_pp::Snmp *snmp, Snmp_pp::Pdu &pdu, Snmp_pp::SnmpTarget &target, void *cd)
{
  Snmp_pp::Vb nextVb;
  int pdu_error;
  Snmp_pp::GenAddress addr;
  std::cout << cd << std::endl;
  target.get_address(addr);
  Snmp_pp::UdpAddress from(addr);

  std::cout << "reason: " << reason << std::endl
       << "msg: " << snmp->error_msg(reason) << std::endl
       << "from: " << from.get_printable() << std::endl;

  pdu_error = pdu.get_error_status();
  if (pdu_error){
    std::cout << "Response contains error: " 
	 << snmp->error_msg(pdu_error)<< std::endl;
  }
  Snmp_pp::Oid id;
  pdu.get_notify_id(id);
  std::cout << "ID:  " << id.get_printable() << std::endl;
  std::cout << "Type:" << pdu.get_type() << std::endl;

  for (int i=0; i<pdu.get_vb_count(); i++)
  {
    pdu.get_vb(nextVb, i);

    std::cout << "Oid: " << nextVb.get_printable_oid() << std::endl
	 << "Val: " <<  nextVb.get_printable_value() << std::endl;
  }
  if (pdu.get_type() == sNMP_PDU_INFORM) {
      std::cout << "pdu type: " << pdu.get_type() << std::endl;
      std::cout << "sending response to inform: " << std::endl;
      nextVb.set_value("This is the response.");
      pdu.set_vb(nextVb, 0);
      snmp->response(pdu, target);
  }
  std::cout << std::endl;
}

int
main()
{
  Snmp_pp::Snmp::socket_startup();
  Snmp_pp::UdpAddress address("192.168.100.100");
  if (!address.valid())
  {
    std::cout << "Invalid address" << std::endl;
  }

  Snmp_pp::snmp_version version = Snmp_pp::version1;
  int retries = 1;
  int timeout = 100;
  u_short port = 161;
  Snmp_pp::OctetStr community("public");

  int status;
  Snmp_pp::Snmp snmp(status, 0, (address.get_ip_version() == Snmp_pp::Address::version_ipv6));

   if (status != SNMP_CLASS_SUCCESS) {
      std::cout << "SNMP++ Session Create Fail, " << snmp.error_msg(status) << "\n";
      return 1;
   }

   Snmp_pp::Pdu pdu;
   Snmp_pp::Vb vb;

   Snmp_pp::Oid oid("1.3.6.1.4.1.6302.2.1.1.3.0");
    if (!oid.valid())
    {
      std::cout << "Invalid Oid, " << std::endl;
      return 1;
    }
    vb.set_oid(oid);
    pdu += vb;
    address.set_port(port);
    Snmp_pp::CTarget ctarget(address);
    ctarget.set_retry(retries);
    ctarget.set_timeout(timeout);
    ctarget.set_version(version);
    ctarget.set_readcommunity(community);
    Snmp_pp::snmp_callback async_callback = callback;
    Snmp_pp::SnmpTarget *target;
    snmp.start_poll_thread(100);
    target = &ctarget;
    status = snmp.get(pdu,*target, async_callback);
    while(1);
//   Snmp_pp::Snmp::socket_cleanup();
}