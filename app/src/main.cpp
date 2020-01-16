#include <iostream>
#include "SNMP.h"
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>

static const u_long identManufacturer_oid [] = {1,3,6,1,4,1,6302,2,1,1,1};
static const u_long identCtrlFWVersion_oid[] = { 1,3,6,1,4,1,6302,2,1,1,3,0};
static const u_long identModel_oid[]  = {1,3,6,1,4,1,6302,2,1,1,1};
static const u_long identControllerFirmwareVersion_oid[]  =  {1,3,6,1,4,1,6302,2,1,1,1};
static const u_long identName_oid[]  = {1,3,6,1,4,1,6302,2,1,1,4};
static const u_long identSNMPCfgVer_oid[]  = {1,3,6,1,4,1,6302,2,1,1,5};
static const u_long identControllerSerialNumber_oid[]  = {1,3,6,1,4,1,6302,2,1,1,6};
static const u_long systemStatus_oid[]  = {1,3,6,1,4,1,6302,2,1,2,1};
static const u_long systemVoltage_oid[]  = {1,3,6,1,4,1,6302,2,1,2,2};
static const u_long systemCurrent_oid[]  = {1,3,6,1,4,1,6302,2,1,2,3};
static const u_long systemUsedCapacity_oid[]  = {1,3,6,1,4,1,6302,2,1,2,4};
static const u_long psBatteryVoltage_oid[]  = {1,3,6,1,4,1,6302,2,1,2,5,1};
static const u_long psTotalBatteryCurrent_oid[]  = {1,3,6,1,4,1,6302,2,1,2,5,2};
static const u_long psBatteryCapacity_oid[]  = {1,3,6,1,4,1,6302,2,1,2,5,3};
static const u_long psBatteryIndex_oid[] = {1,3,6,1,4,1,6302,2,1,2,5,5,1,1};
static const u_long psBatteryName_oid[]  = {1,3,6,1,4,1,6302,2,1,2,5,5,1,3};
static const u_long psBatteryCurrent_oid[]  = {1,3,6,1,4,1,6302,2,1,2,5,5,1,2};
static const u_long psBatteryNominalCapacity_oid[]  = {1,3,6,1,4,1,6302,2,1,2,5,4};
static const u_long psInputLineAVoltage_oid[]  = {1,3,6,1,4,1,6302,2,1,2,6,1,0};
static const u_long psInputLineBVoltage_oid[]  = {1,3,6,1,4,1,6302,2,1,2,6,2};
static const u_long psInputLineCVoltage_oid[]  = {1,3,6,1,4,1,6302,2,1,2,6,3};
static const u_long psTemperature1_oid[]  = {1,3,6,1,4,1,6302,2,1,2,7,1};
static const u_long psTemperature2_oid[]  = {1,3,6,1,4,1,6302,2,1,2,7,2};
static const u_long psTemperatureIndex_oid[]  = {1,3,6,1,4,1,6302,2,1,2,7,3,1,1};
static const u_long psTemperatureMeasurement_oid[]  = {1,3,6,1,4,1,6302,2,1,2,7,3,1,2};
static const u_long psTemperatureName_oid[]  = {1,3,6,1,4,1,6302,2,1,2,7,3,1,3};
static const u_long psTemperatureType_oid[]  = {1,3,6,1,4,1,6302,2,1,2,7,3,1,4};
static const u_long psTemperatureAlarmStatus_oid[]  = {1,3,6,1,4,1,6302,2,1,2,7,3,1,5};
static const u_long psStatusCommunication_oid[]  = {1,3,6,1,4,1,6302,2,1,2,8};
static const u_long psStatusBatteryMode_oid[]  = {1,3,6,1,4,1,6302,2,1,2,9};
static const u_long numberOfInstalledRectifiers_oid[]  = {1,3,6,1,4,1,6302,2,1,2,11,2};
static const u_long numberOfRectifiersCommunicating_oid[]  = {1,3,6,1,4,1,6302,2,1,2,11,3};
static const u_long rectifiersUsedCapacity_oid[]  = {1,3,6,1,4,1,6302,2,1,2,5,2};
static const u_long psRectifierIndex_oid[]  = {1,3,6,1,4,1,6302,2,1,2,11,4,1,1};
static const u_long psRectifierProductNumber_oid[]  = {1,3,6,1,4,1,6302,2,1,2,11,4,1,2};
static const u_long psRectifierHWVersion_oid[]  = {1,3,6,1,4,1,6302,2,1,2,11,4,1,3};
static const u_long psRectifierSWVersion_oid[]  = {1,3,6,1,4,1,6302,2,1,2,11,4,1,4};
static const u_long psRectifierSerialNumber_oid[]  = {1,3,6,1,4,1,6302,2,1,2,11,4,1,5};
static const u_long psRectifierCurrent_oid[]  = {1,3,6,1,4,1,6302,2,1,2,11,4,1,6};
static const u_long psRectifierIdent_oid[]  = {1,3,6,1,4,1,6302,2,1,2,11,4,1,7};
static const u_long psRectifierFail_oid[]  = {1,3,6,1,4,1,6302,2,1,2,11,4,1,8};
static const u_long psTotalLoadCurrent[] = {1,3,6,1,4,1,6302,2,1,2,12,1};
static const u_long psDistributionLoadIndex_oid[]  = {1,3,6,1,4,1,6302,2,1,2,12,2,1,1};
static const u_long psDistributionLoadCurrent_oid[]  = {1,3,6,1,4,1,6302,2,1,2,12,2,1,2};
static const u_long psDistributionLoadName_oid[]  = {1,3,6,1,4,1,6302,2,1,2,12,2,1,3};
static const u_long psDistributionGeneralIndex_oid[]  = {1,3,6,1,4,1,6302,2,1,2,12,3,1,1};
static const u_long psDistributionGeneralCurrent_oid[]  = {1,3,6,1,4,1,6302,2,1,2,12,3,1,2};
static const u_long psDistributionGeneralNameoid[]  = {1,3,6,1,4,1,6302,2,1,2,12,3,1,3};
static const u_long alarmIndex_oid[]  = {1,3,6,1,4,1,6302,2,1,4,1,1};
static const u_long alarmTime_oid[]  = {1,3,6,1,4,1,6302,2,1,4,1,2};
static const u_long alarmStatusChange_oid[]  = {1,3,6,1,4,1,6302,2,1,4,1,3};
static const u_long alarmSeverity_oid[]  = {1,3,6,1,4,1,6302,2,1,4,1,4};
static const u_long alarmDescription_oid[]  = {1,3,6,1,4,1,6302,2,1,4,1,5};
static const u_long alarmType_oid[]  = {1,3,6,1,4,1,6302,2,1,4,1,6};

/*
static const u_long identName_oid[] =          { 1,3,6,1,4,1,6302,2,1,1,4,0 };
static const u_long identSerialNum_oid[] =     { 1,3,6,1,4,1,6302,2,1,1,6,0 };
static const u_long rectIndex_oid[] =          { 1,3,6,1,4,1,6302,2,1,2,11,4,1,1 };
static const u_long rectProdNum_oid[] =        { 1,3,6,1,4,1,6302,2,1,2,11,4,1,2,0 };
static const u_long rectHWVersion_oid[] =      { 1,3,6,1,4,1,6302,2,1,2,11,4,1,3,0 };
static const u_long rectSWVersion_oid[] =      { 1,3,6,1,4,1,6302,2,1,2,11,4,1,4,0 };
static const u_long rectSerialNum_oid[] =      { 1,3,6,1,4,1,6302,2,1,2,11,4,1,5,0 };
static const u_long rectIdent_oid[] =          { 1,3,6,1,4,1,6302,2,1,2,11,4,1,7,0 };
static u_long rectNumInstalled_oid[] =         { 1,3,6,1,4,1,6302,2,1,2,11,1,0 };
static u_long rectKeyI_oid[] =                 { 1,3,6,1,4,1,6302,2,1,2,11,4,1,1,0 };
*/

int
main()
{
    SNMP NCU;
    NCU.SNMPInit();
    NCU.SNMPGet(psInputLineAVoltage_oid, sizeof(psInputLineAVoltage_oid)/sizeof(psInputLineAVoltage_oid[0]));
    return 0;
}
