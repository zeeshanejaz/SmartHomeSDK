#include "EnumParser.h"


EnumParser::EnumParser(void)
{
}

EnumParser::~EnumParser(void)
{
}

PacketType EnumParser::ParsePacketType(const string& paramPacketType)
{
	string strPacketType = Utility::ToLower(paramPacketType);

	if(strPacketType.compare("request"))
		return Request;
	
	else if(strPacketType.compare("response"))
		return Response;

	else
		return Push;
}

TargetType EnumParser::ParseTargetType(const string& paramTargetType)
{
	string strTargetType = Utility::ToLower(paramTargetType);

	if(strTargetType.compare("building"))
		return Building;
	
	else if(strTargetType.compare("floor"))
		return Floor;

	else if(strTargetType.compare("room"))
		return Room;

	else if(strTargetType.compare("device"))
		return Device;

	else
		return Paired;
}

RequestType EnumParser::ParseRequestType(const string& paramRequestType)
{
	string strRequestType = Utility::ToLower(paramRequestType);

	if(strRequestType.compare("enumeration"))
		return Enumeration;
	
	else if(strRequestType.compare("get"))
		return Get;

	else if(strRequestType.compare("set"))
		return Set;

	else
		return Execute;
}
