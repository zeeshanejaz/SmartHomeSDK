#include "ProtocolManager.h"

#define EmptyString ""

ProtocolManager::ProtocolManager(void)
{
	client = new CommClient(); 
	client->Connect();		
}

ProtocolManager::~ProtocolManager(void)
{
	Dispose();
}

//explicit dispose to end communication and release resources
void ProtocolManager::Dispose()
{
	client->Disconnect();
}

//Enumeration requests
int ProtocolManager::GetGenericCount(TargetType targetType, int id1, int id2)
{
	//prepare request
	ProtocolPacket* request = ProtocolPacket::PrepareRequest(targetType, Enumeration, EmptyString, id1, id2);

	//get result synchronously
	string result = getResponeString(request);

	//cast to integer
	return Utility::StringToInteger(result);
}

//generic integer set
vector<int>* ProtocolManager::GetGenericIntegerSet(TargetType targetType, int id1, int id2, string attributeName)
{
	//prepare request
	ProtocolPacket* request = ProtocolPacket::PrepareRequest(targetType, Get, attributeName, id1, id2);

	//get result synchronously
	ProtocolPacket* response = client->GetResponse(request);

	//extract integer vector
	vector<int>* result = response->ExtractPayloadIntegerVector();
	return result;
}

//generic string set
vector<string>* ProtocolManager::GetGenericStringSet(TargetType targetType, int id1, int id2, string attributeName)
{
	//prepare request
	ProtocolPacket* request = ProtocolPacket::PrepareRequest(targetType, Enumeration, attributeName, id1, id2);

	//get result synchronously
	ProtocolPacket* response = client->GetResponse(request);

	//extract string vector
	vector<string>* result = response->ExtractPayloadStringVector();
	return result;
}

//attribute read
string ProtocolManager::GetGenericAttribute(TargetType targetType, int id1, int id2, string attributeName)
{
	//prepare request
	ProtocolPacket* request = ProtocolPacket::PrepareRequest(targetType, Get, attributeName, id1, id2);

	//get result synchronously
	string result = getResponeString(request);	
	return result;
}

//attribute write
bool ProtocolManager::SetGenericAttribute(TargetType targetType, int id1, int id2, string attributeName, string attributeValue)
{
	//prepare request
	ProtocolPacket* request = ProtocolPacket::PrepareRequest(targetType, Set, attributeName, id1, id2);
	request->Parameters.push_back(attributeValue);

	//get result synchronously
	string result = getResponeString(request);

	//cast to bool
	return Utility::StringToBool(result);
}

//invoke device command methods
string ProtocolManager::InvokeGenericCommand(int deviceId, string commandName, int commandId)
{
	//prepare request
	ProtocolPacket* request = ProtocolPacket::PrepareRequest(Device, Execute, commandName, deviceId, UNUSED);
	request->Parameters.push_back(Utility::IntegerToString(commandId));

	//get result synchronously
	string result = getResponeString(request);
	return result;
}

//perform synchronous request and returns payload.
string ProtocolManager::getResponeString(ProtocolPacket* request)
{
	//generate response from request
	ProtocolPacket* response = client->GetResponse(request);

	if(response == NULL)
		throw new string ("Request timed out! Check simulator logs.");
	
	//extract payload
	string payload = response->ExtractPayloadString();// response->Parameters first item
	return payload;
}

