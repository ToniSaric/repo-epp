#include <iostream>
#include "SNMP.h"
#include <vector>
#include "OID.h"



void
SNMP::SNMPOpen()
{

}

void SNMP::SNMPClose()
{
  
}

int SNMP::SNMPGet()
{
  
  return 0;
}



SNMP::SNMP()
{
}

SNMP::~SNMP()
{
  this->SNMPClose();
}
