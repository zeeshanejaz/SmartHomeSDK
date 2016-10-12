#include "ModelController.h"

ModelController::ModelController(void)
{
	protocolManager = NULL;
}

ModelController::~ModelController(void)
{
	Dispose();
}

////////////////////////////////////////////////////////////////////////////////////////////////

void ModelController::Initialize()
{
	protocolManager = new ProtocolManager();
}

void ModelController::Dispose()
{
	if(protocolManager != NULL)
		protocolManager->Dispose();
}

void ModelController::validate()
{
	if(protocolManager == NULL)
		throw new string("Cannot use this object without initialization.");
}

////////////////////////////////////Enumeration Methods//////////////////////////////////////////

int ModelController::GetFloorCount()
{
	validate();
	return protocolManager->GetGenericCount(Floor, UNUSED, UNUSED);
}

int ModelController::GetRoomCount(int floorNumber)
{
	validate();
	return protocolManager->GetGenericCount(Room, floorNumber, UNUSED);
}

int ModelController::GetDeviceCount(int floorNumber, int roomNumber)
{
	validate();
	return protocolManager->GetGenericCount(Device, floorNumber, roomNumber);
}

int ModelController::GetPairedDevicesCount(int deviceId)
{
	validate();
	return protocolManager->GetGenericCount(Device, deviceId, UNUSED);
}

////////////////////////////////////Device Search Methods///////////////////////////////////////

vector<int>* ModelController::GetDevices(int floorNumber, int roomNumber)
{
	validate();
	return protocolManager->GetGenericIntegerSet(Room, floorNumber, roomNumber, _Devices);
}

vector<int>* ModelController::GetPairedDevices(int deviceId)
{
	validate();
	return protocolManager->GetGenericIntegerSet(Device, deviceId, UNUSED, _PairedDevices);
}

////////////////////////////////////////Read Attributes/////////////////////////////////////////

string ModelController::GetBuildingStreetAddress()
{
	validate();
	return protocolManager->GetGenericAttribute(Building, UNUSED, UNUSED, _StreetAddress);
}

bool ModelController::GetDevicePoweredOn(int deviceId)
{
	validate();
	string status = protocolManager->GetGenericAttribute(Device, deviceId, UNUSED, _PoweredOn);
	return Utility::StringToBool(status);
}

bool ModelController::GetDeviceOnlineStatus(int deviceId)
{
	validate();
	string status = protocolManager->GetGenericAttribute(Device, deviceId, UNUSED, _OnlineStatus);
	return Utility::StringToBool(status);
}

////////////////////////////////////////Name Methods///////////////////////////////////////////

string ModelController::GetBuildingName()
{
	validate();
	return protocolManager->GetGenericAttribute(Building, UNUSED, UNUSED, _Name);
}


string ModelController::GetFloorName(int floorNumber)
{
	validate();
	return protocolManager->GetGenericAttribute(Floor, floorNumber, UNUSED, _Name);
}


string ModelController::GetRoomName(int floorNumber, int roomNumber)
{
	validate();
	return protocolManager->GetGenericAttribute(Room, floorNumber, roomNumber, _Name);
}

string ModelController::GetDeviceName(int deviceId)
{
	validate();
	return protocolManager->GetGenericAttribute(Device, deviceId, UNUSED, _Name);
}

////////////////////////////////////////Write Attributes//////////////////////////////////////

bool ModelController::SetDevicePoweredOn(int deviceId, bool newStatus)
{
	validate();
	string status = (newStatus) ? _TrueValue : _FalseValue;
	return protocolManager->SetGenericAttribute(Device, deviceId, UNUSED, _PoweredOn, status);
}

bool ModelController::SetDeviceOnlineStatus(int deviceId, bool newStatus)
{
	validate();
	string status = (newStatus) ? _TrueValue : _FalseValue;
	return protocolManager->SetGenericAttribute(Device, deviceId, UNUSED, _OnlineStatus, status);
}

//////////////////////////////////Evalute Device Capability///////////////////////////////////

bool ModelController::IsTextEnabled(int deviceId)
{
	validate();
	string result = protocolManager->InvokeGenericCommand(deviceId, _IsTextEnabled, UNUSED);
	return Utility::StringToBool(result);
}

bool ModelController::IsCommandEnabled(int deviceId)
{
	validate();
	string result = protocolManager->InvokeGenericCommand(deviceId, _IsCommandEnabled, UNUSED);
	return Utility::StringToBool(result);
}

bool ModelController::IsSafetyRelated(int deviceId)
{
	validate();
	string result = protocolManager->InvokeGenericCommand(deviceId, _IsSafetyRelated, UNUSED);
	return Utility::StringToBool(result);
}

////////////////////////////////////Invoke Device Methods/////////////////////////////////////

string ModelController::GetTextStatus(int deviceId)
{
	validate();
	string result = protocolManager->InvokeGenericCommand(deviceId, _GetTextStatus, UNUSED);
	return result;
}

bool ModelController::GetSafetyStatus(int deviceId)
{
	validate();
	string result = protocolManager->InvokeGenericCommand(deviceId, _GetSafetyStatus, UNUSED);
	return Utility::StringToBool(result);
}

bool ModelController::ExecuteCommand(int deviceId, int commandId)
{
	validate();
	string result = protocolManager->InvokeGenericCommand(deviceId, _ExecuteCommand, commandId);
	return Utility::StringToBool(result);
}

int ModelController::GetMaxCommandId(int deviceId)
{
	validate();
	string result = protocolManager->InvokeGenericCommand(deviceId, _GetMaxCommandId, UNUSED);
	return Utility::StringToInteger(result);
}
///////////////////////////////////////////////////////////////////////////////////////////////