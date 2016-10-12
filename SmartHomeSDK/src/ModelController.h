#pragma once

#ifndef __MODELCONTROLLERDEFITNITIONS__

#define __MODELCONTROLLERDEFITNITIONS__

#include "enum_defines.h"
#include "ProtocolPacket.h"
#include "ProtocolManager.h"

#include <vector>
#include <string>

using namespace std;

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

class ModelController
{
public:
	ModelController(void);
	~ModelController(void);

	void Initialize();
	void Dispose();

	//Enumeration requests
	int GetFloorCount();
	int GetRoomCount(int floorNumber);
	int GetDeviceCount(int floorNumber, int roomNumber);
	int GetPairedDevicesCount(int deviceId);

	//device search
	vector<int>* GetDevices(int floorNumber, int roomNumber);
	vector<int>* GetPairedDevices(int deviceId);

	//attribute read
	string GetBuildingStreetAddress();	
	bool GetDevicePoweredOn(int deviceId);
	bool GetDeviceOnlineStatus(int deviceId);

	//Name functions
	string GetBuildingName();
	string GetFloorName(int floorNumber);
	string GetRoomName(int floorNumber, int roomNumber);
	string GetDeviceName(int deviceId);

	//attribute write
	bool SetDevicePoweredOn(int deviceId, bool newStatus);
	bool SetDeviceOnlineStatus(int deviceId, bool newStatus);

	//evaluate device capability
	bool IsTextEnabled(int deviceId);
	bool IsCommandEnabled(int deviceId);
	bool IsSafetyRelated(int deviceId);

	//invoke device methods
	string GetTextStatus(int deviceId);
	bool GetSafetyStatus(int deviceId);
	bool ExecuteCommand(int deviceId, int commandId);
	int GetMaxCommandId(int deviceId);

private:
	ProtocolManager* protocolManager;
	void validate();
};

#endif

