#include "SmartHomeSDK.h"

////////////////////////////////////////////////////////////////////////////////////////////////

#define _PoweredOn		"PoweredOn"
#define _OnlineStatus	"OnlineStatus"
#define _StreetAddress	"StreetAddress"

#define _Devices		"Devices"
#define _PairedDevices	"PairedDevices"

#define _TrueValue		"true"
#define _FalseValue		"false"
#define _Name			"Name"

#define _IsTextEnabled		"IsTextEnabled"
#define _IsCommandEnabled	"IsCommandEnabled"
#define _IsSafetyRelated	"IsSafetyRelated"

#define _GetTextStatus		"GetTextStatus"
#define _GetSafetyStatus	"GetSafetyStatus"
#define _ExecuteCommand		"ExecuteCommand"
#define _GetMaxCommandId	"GetMaxCommandId"

ProtocolManager* protocolManager = NULL;

void validate()
{
	if(protocolManager == NULL)
		throw new string("Cannot use this object without initialization.");
}

////////////////////////////////////////////////////////////////////////////////////////////////

void SHAPI_Initialize()
{
	protocolManager = new ProtocolManager();
}

void SHAPI_Dispose()
{
	if(protocolManager != NULL)
		protocolManager->Dispose();
}

////////////////////////////////////Enumeration Methods//////////////////////////////////////////

int SHAPI_GetFloorCount()
{
	validate();
	return protocolManager->GetGenericCount(Floor, UNUSED, UNUSED);
}

int SHAPI_GetRoomCount(int floorNumber)
{
	validate();
	return protocolManager->GetGenericCount(Room, floorNumber, UNUSED);
}

int SHAPI_GetDeviceCount(int floorNumber, int roomNumber)
{
	validate();
	return protocolManager->GetGenericCount(Device, floorNumber, roomNumber);
}

int SHAPI_GetPairedDevicesCount(int deviceId)
{
	validate();
	return protocolManager->GetGenericCount(Device, deviceId, UNUSED);
}

////////////////////////////////////Device Search Methods///////////////////////////////////////

vector<int>* SHAPI_GetDevices(int floorNumber, int roomNumber)
{
	validate();
	return protocolManager->GetGenericIntegerSet(Room, floorNumber, roomNumber, _Devices);
}

vector<int>* SHAPI_GetPairedDevices(int deviceId)
{
	validate();
	return protocolManager->GetGenericIntegerSet(Device, deviceId, UNUSED, _PairedDevices);
}

////////////////////////////////////////Read Attributes/////////////////////////////////////////

string SHAPI_GetBuildingStreetAddress()
{
	validate();
	return protocolManager->GetGenericAttribute(Building, UNUSED, UNUSED, _StreetAddress);
}

bool SHAPI_GetDevicePoweredOn(int deviceId)
{
	validate();
	string status = protocolManager->GetGenericAttribute(Device, deviceId, UNUSED, _PoweredOn);
	return Utility::StringToBool(status);
}

bool SHAPI_GetDeviceOnlineStatus(int deviceId)
{
	validate();
	string status = protocolManager->GetGenericAttribute(Device, deviceId, UNUSED, _OnlineStatus);
	return Utility::StringToBool(status);
}

////////////////////////////////////////Name Methods///////////////////////////////////////////

string SHAPI_GetBuildingName()
{
	validate();
	return protocolManager->GetGenericAttribute(Building, UNUSED, UNUSED, _Name);
}


string SHAPI_GetFloorName(int floorNumber)
{
	validate();
	return protocolManager->GetGenericAttribute(Floor, floorNumber, UNUSED, _Name);
}


string SHAPI_GetRoomName(int floorNumber, int roomNumber)
{
	validate();
	return protocolManager->GetGenericAttribute(Room, floorNumber, roomNumber, _Name);
}

string SHAPI_GetDeviceName(int deviceId)
{
	validate();
	return protocolManager->GetGenericAttribute(Device, deviceId, UNUSED, _Name);
}

////////////////////////////////////////Write Attributes//////////////////////////////////////

bool SHAPI_SetDevicePoweredOn(int deviceId, bool newStatus)
{
	validate();
	string status = (newStatus) ? _TrueValue : _FalseValue;
	return protocolManager->SetGenericAttribute(Device, deviceId, UNUSED, _PoweredOn, status);
}

bool SHAPI_SetDeviceOnlineStatus(int deviceId, bool newStatus)
{
	validate();
	string status = (newStatus) ? _TrueValue : _FalseValue;
	return protocolManager->SetGenericAttribute(Device, deviceId, UNUSED, _OnlineStatus, status);
}

//////////////////////////////////Evalute Device Capability///////////////////////////////////

bool SHAPI_IsTextEnabled(int deviceId)
{
	validate();
	string result = protocolManager->InvokeGenericCommand(deviceId, _IsTextEnabled, UNUSED);
	return Utility::StringToBool(result);
}

bool SHAPI_IsCommandEnabled(int deviceId)
{
	validate();
	string result = protocolManager->InvokeGenericCommand(deviceId, _IsCommandEnabled, UNUSED);
	return Utility::StringToBool(result);
}

bool SHAPI_IsSafetyRelated(int deviceId)
{
	validate();
	string result = protocolManager->InvokeGenericCommand(deviceId, _IsSafetyRelated, UNUSED);
	return Utility::StringToBool(result);
}

////////////////////////////////////Invoke Device Methods/////////////////////////////////////

string SHAPI_GetTextStatus(int deviceId)
{
	validate();
	string result = protocolManager->InvokeGenericCommand(deviceId, _GetTextStatus, UNUSED);
	return result;
}

bool SHAPI_GetSafetyStatus(int deviceId)
{
	validate();
	string result = protocolManager->InvokeGenericCommand(deviceId, _GetSafetyStatus, UNUSED);
	return Utility::StringToBool(result);
}

bool SHAPI_ExecuteCommand(int deviceId, int commandId)
{
	validate();
	string result = protocolManager->InvokeGenericCommand(deviceId, _ExecuteCommand, commandId);
	return Utility::StringToBool(result);
}

int SHAPI_GetMaxCommandId(int deviceId)
{
	validate();
	string result = protocolManager->InvokeGenericCommand(deviceId, _GetMaxCommandId, UNUSED);
	return Utility::StringToInteger(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////