#pragma once

#ifndef __PROTOCOLMANAGERDEFINITION__

#define __PROTOCOLMANAGERDEFINITION__

#include "CommClient.h"
#include "Utility.h"

using namespace std;

class ProtocolManager
{
public:
	ProtocolManager(void);
	~ProtocolManager(void);
	
	void Dispose();

	//Enumeration requests
	int GetGenericCount(TargetType targetType, int id1, int id2);

	//generic integer set
	vector<int>* GetGenericIntegerSet(TargetType targetType, int id1, int id2, string attributeName);

	//generic string set
	vector<string>* GetGenericStringSet(TargetType targetType, int id1, int id2, string attributeName);

	//attribute read
	string GetGenericAttribute(TargetType targetType, int id1, int id2, string attributeName);

	//attribute write
	bool SetGenericAttribute(TargetType targetType, int id1, int id2, string attributeName, string attributeValue);
	
	//invoke device generic / capability methods
	string InvokeGenericCommand(int deviceId, string commandName, int commandId);

private:
	CommClient* client;

	//perform synchronous request and returns payload string.
	string getResponeString(ProtocolPacket* request);
};

#endif