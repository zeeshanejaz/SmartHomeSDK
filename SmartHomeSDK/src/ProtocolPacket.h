#pragma once

#ifndef __PROTOCOLPACKETDEFINITION__

#define __PROTOCOLPACKETDEFINITION__

#include "enum_defines.h"
#include "Utility.h"
#include "EnumParser.h"

#include <string>
#include <vector>
#include <sstream>
#include <cstdarg>

using namespace::std;

#define UNUSED -1

class ProtocolPacket
{
public:
	ProtocolPacket(void);
	~ProtocolPacket(void);

	static ProtocolPacket* Parse(const string& strPacket);
	static ProtocolPacket* PreparePacket(enum PacketType PacketType, enum TargetType TargetType, enum RequestType RequestType, const string& TargetArticle, int nArgs, ...);
	static ProtocolPacket* PrepareRequest(enum TargetType TargetType, enum RequestType RequestType, const string& TargetArticle, int id1, int id2);
		
	vector<string> Parameters;
	enum PacketType PacketType;
	enum TargetType TargetType;
	enum RequestType RequestType;
	string TargetArticle;

	string ToString();
	string ExtractPayloadString();
	vector<int>* ExtractPayloadIntegerVector();
	vector<string>* ExtractPayloadStringVector();
};

#endif