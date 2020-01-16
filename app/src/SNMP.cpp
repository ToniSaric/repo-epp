#include <iostream>
#include "SNMP.h"
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <vector>

 
static const oid identManufacturer_oid[] = {1,3,6,1,4,1,6302,2,1,1,1};
static const oid identModel_oid[] = {1,3,6,1,4,1,6302,2,1,1,1};
static const oid identControllerFirmwareVersion_oid[] = { 1,3,6,1,4,1,6302,2,1,1,3,0};
static const oid identName_oid[] = {1,3,6,1,4,1,6302,2,1,1,4};
static const oid identSNMPCfgVer_oid[] = {1,3,6,1,4,1,6302,2,1,1,5};
static const oid identControllerSerialNumber_oid[] = {1,3,6,1,4,1,6302,2,1,1,6};
static const oid systemStatus_oid[] = {1,3,6,1,4,1,6302,2,1,2,1};
static const oid systemVoltage_oid[] = {1,3,6,1,4,1,6302,2,1,2,2};
static const oid systemCurrent_oid[] = {1,3,6,1,4,1,6302,2,1,2,3};
static const oid systemUsedCapacity_oid[] = {1,3,6,1,4,1,6302,2,1,2,4};
static const oid psBatteryVoltage_oid[] = {1,3,6,1,4,1,6302,2,1,2,5,1};
static const oid psTotalBatteryCurrent_oid[] = {1,3,6,1,4,1,6302,2,1,2,5,2};
static const oid psBatteryCapacity_oid[] = {1,3,6,1,4,1,6302,2,1,2,5,3};
static const oid psBatteryIndex_oid[]= {1,3,6,1,4,1,6302,2,1,2,5,5,1,1};
static const oid psBatteryName_oid[] = {1,3,6,1,4,1,6302,2,1,2,5,5,1,3};
static const oid psBatteryCurrent_oid[] = {1,3,6,1,4,1,6302,2,1,2,5,5,1,2};
static const oid psBatteryNominalCapacity_oid[] = {1,3,6,1,4,1,6302,2,1,2,5,4};
static const oid psInputLineAVoltage_oid[] = {1,3,6,1,4,1,6302,2,1,2,6,1};
static const oid psInputLineBVoltage_oid[] = {1,3,6,1,4,1,6302,2,1,2,6,2};
static const oid psInputLineCVoltage_oid[] = {1,3,6,1,4,1,6302,2,1,2,6,3};
static const oid psTemperature1_oid[] = {1,3,6,1,4,1,6302,2,1,2,7,1};
static const oid psTemperature2_oid[] = {1,3,6,1,4,1,6302,2,1,2,7,2};
static const oid psTemperatureIndex_oid[] = {1,3,6,1,4,1,6302,2,1,2,7,3,1,1};
static const oid psTemperatureMeasurement_oid[] = {1,3,6,1,4,1,6302,2,1,2,7,3,1,2};
static const oid psTemperatureName_oid[] = {1,3,6,1,4,1,6302,2,1,2,7,3,1,3};
static const oid psTemperatureType_oid[] = {1,3,6,1,4,1,6302,2,1,2,7,3,1,4};
static const oid psTemperatureAlarmStatus_oid[] = {1,3,6,1,4,1,6302,2,1,2,7,3,1,5};
static const oid psStatusCommunication_oid[] = {1,3,6,1,4,1,6302,2,1,2,8};
static const oid psStatusBatteryMode_oid[] = {1,3,6,1,4,1,6302,2,1,2,9};
static const oid numberOfInstalledRectifiers_oid[] = {1,3,6,1,4,1,6302,2,1,2,11,2};
static const oid numberOfRectifiersCommunicating_oid[] = {1,3,6,1,4,1,6302,2,1,2,11,3};
static const oid rectifiersUsedCapacity_oid[] = {1,3,6,1,4,1,6302,2,1,2,5,2};
static const oid psRectifierIndex_oid[] = {1,3,6,1,4,1,6302,2,1,2,11,4,1,1};
static const oid psRectifierProductNumber_oid[] = {1,3,6,1,4,1,6302,2,1,2,11,4,1,2};
static const oid psRectifierHWVersion_oid[] = {1,3,6,1,4,1,6302,2,1,2,11,4,1,3};
static const oid psRectifierSWVersion_oid[] = {1,3,6,1,4,1,6302,2,1,2,11,4,1,4};
static const oid psRectifierSerialNumber_oid[] = {1,3,6,1,4,1,6302,2,1,2,11,4,1,5};
static const oid psRectifierCurrent_oid[] = {1,3,6,1,4,1,6302,2,1,2,11,4,1,6};
static const oid psRectifierIdent_oid[] = {1,3,6,1,4,1,6302,2,1,2,11,4,1,7};
static const oid psRectifierFail_oid[] = {1,3,6,1,4,1,6302,2,1,2,11,4,1,8};
static const oid psTotalLoadCurrent[]= {1,3,6,1,4,1,6302,2,1,2,12,1};
static const oid psDistributionLoadIndex_oid[] = {1,3,6,1,4,1,6302,2,1,2,12,2,1,1};
static const oid psDistributionLoadCurrent_oid[] = {1,3,6,1,4,1,6302,2,1,2,12,2,1,2};
static const oid psDistributionLoadName_oid[] = {1,3,6,1,4,1,6302,2,1,2,12,2,1,3};
static const oid psDistributionGeneralIndex_oid[] = {1,3,6,1,4,1,6302,2,1,2,12,3,1,1};
static const oid psDistributionGeneralCurrent_oid[] = {1,3,6,1,4,1,6302,2,1,2,12,3,1,2};
static const oid psDistributionGeneralNameoid[] = {1,3,6,1,4,1,6302,2,1,2,12,3,1,3};
static const oid alarmIndex_oid[] = {1,3,6,1,4,1,6302,2,1,4,1,1};
static const oid alarmTime_oid[] = {1,3,6,1,4,1,6302,2,1,4,1,2};
static const oid alarmStatusChange_oid[] = {1,3,6,1,4,1,6302,2,1,4,1,3};
static const oid alarmSeverity_oid[] = {1,3,6,1,4,1,6302,2,1,4,1,4};
static const oid alarmDescription_oid[] = {1,3,6,1,4,1,6302,2,1,4,1,5};
static const oid alarmType_oid[] = {1,3,6,1,4,1,6302,2,1,4,1,6};

/*
static const oid identName_oid[]=          { 1,3,6,1,4,1,6302,2,1,1,4,0 };
static const oid identSerialNum_oid[]=     { 1,3,6,1,4,1,6302,2,1,1,6,0 };
static const oid rectIndex_oid[]=          { 1,3,6,1,4,1,6302,2,1,2,11,4,1,1 };
static const oid rectProdNum_oid[]=        { 1,3,6,1,4,1,6302,2,1,2,11,4,1,2,0 };
static const oid rectHWVersion_oid[]=      { 1,3,6,1,4,1,6302,2,1,2,11,4,1,3,0 };
static const oid rectSWVersion_oid[]=      { 1,3,6,1,4,1,6302,2,1,2,11,4,1,4,0 };
static const oid rectSerialNum_oid[]=      { 1,3,6,1,4,1,6302,2,1,2,11,4,1,5,0 };
static const oid rectIdent_oid[]=          { 1,3,6,1,4,1,6302,2,1,2,11,4,1,7,0 };
static oid rectNumInstalled_oid[]=         { 1,3,6,1,4,1,6302,2,1,2,11,1,0 };
static oid rectKeyI_oid[]=                 { 1,3,6,1,4,1,6302,2,1,2,11,4,1,1,0 };
*/

int print_result (int status, struct snmp_session *sp, struct snmp_pdu *pdu)
{
  char buf[1024];
  struct variable_list *vp;
  int ix;

  switch (status) {
  case STAT_SUCCESS:
    vp= pdu->variables;
    if (pdu->errstat== SNMP_ERR_NOERROR) {
      while (vp) {
        snprint_variable(buf, sizeof(buf), vp->name, vp->name_length, vp);
        fprintf(stdout, "%s: %s\n", sp->peername, buf);
	vp= vp->next_variable;
      }
    }
    else {
      for (ix= 1; vp && ix != pdu->errindex; vp= vp->next_variable, ix++)
        ;
      if (vp) snprint_objid(buf, sizeof(buf), vp->name, vp->name_length);
      else strcpy(buf, "(none)");
      fprintf(stdout, "%s: %s: %s\n",
      	sp->peername, buf, snmp_errstring(pdu->errstat));
    }
    return 1;
  case STAT_TIMEOUT:
    fprintf(stdout, "%s: Timeout\n", sp->peername);
    return 0;
  case STAT_ERROR:
    snmp_perror(sp->peername);
    return 0;
  }
  return 0;
}

void
SNMP::SNMPInit(void)
{
    //oid anOID[MAX_OID_LEN];
    //size_t anOID_len= MAX_OID_LEN;
    //init_snmp("NCU");
    snmp_sess_init(&session);
    session.version= SNMP_VERSION_1;
    session.peername= strdup("192.168.100.100");
    //session.localname= strdup();
    session.community= (u_char *) strdup("public");
    session.community_len= strlen((const char*)session.community);
    if (!(session_handle= snmp_open(&session))) {
      snmp_perror("snmp_open");
      exit(1);
    }
}

int SNMP::SNMPGet(const oid Oid[], size_t len)
{
  if (!session_handle) {
    return -1;
  }
  int status;
  pdu = snmp_pdu_create(SNMP_MSG_GET);
  snmp_add_null_var(pdu, Oid, len);
  status = snmp_synch_response(session_handle, pdu, &response);
  snmp_free_pdu(response);
  print_result(status, session_handle, response);
  return status;
}


SNMP::SNMP()
{
}

SNMP::~SNMP()
{
  snmp_close(session_handle);
}
