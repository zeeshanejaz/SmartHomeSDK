#pragma once

#ifndef __SMARTHOMESDKDEFITNITIONS__

#define __SMARTHOMESDKDEFITNITIONS__

#include "ProtocolManager.h"

#include <vector>
#include <string>

using namespace std;

void SHAPI_Initialize();
void SHAPI_Dispose();

//Enumeration requests
int SHAPI_GetFloorCount();
int SHAPI_GetRoomCount(int floorNumber);
int SHAPI_GetDeviceCount(int floorNumber, int roomNumber);
int SHAPI_GetPairedDevicesCount(int deviceId);

//device search
vector<int>* SHAPI_GetDevices(int floorNumber, int roomNumber);
vector<int>* SHAPI_GetPairedDevices(int deviceId);

//attribute read
string SHAPI_GetBuildingStreetAddress();	
bool SHAPI_GetDevicePoweredOn(int deviceId);
bool SHAPI_GetDeviceOnlineStatus(int deviceId);

//Name functions
string SHAPI_GetBuildingName();
string SHAPI_GetFloorName(int floorNumber);
string SHAPI_GetRoomName(int floorNumber, int roomNumber);
string SHAPI_GetDeviceName(int deviceId);

//attribute write
bool SHAPI_SetDevicePoweredOn(int deviceId, bool newStatus);
bool SHAPI_SetDeviceOnlineStatus(int deviceId, bool newStatus);

//evaluate device capability
bool SHAPI_IsTextEnabled(int deviceId);
bool SHAPI_IsCommandEnabled(int deviceId);
bool SHAPI_IsSafetyRelated(int deviceId);

//invoke device methods
string SHAPI_GetTextStatus(int deviceId);
bool SHAPI_GetSafetyStatus(int deviceId);
bool SHAPI_ExecuteCommand(int deviceId, int commandId);
int SHAPI_GetMaxCommandId(int deviceId);

#endif