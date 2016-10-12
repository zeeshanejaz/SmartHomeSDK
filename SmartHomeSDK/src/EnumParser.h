#pragma once

#ifndef __ENUMPARSERDEFINITION__

#define __ENUMPARSERDEFINITION__

#include "enum_defines.h"
#include "Utility.h"

#include <string>

using namespace::std;

class EnumParser
{
public:
	EnumParser(void);
	~EnumParser(void);

	static PacketType ParsePacketType(const string& strPacketType);
	static TargetType ParseTargetType(const string& strTargetType);
	static RequestType ParseRequestType(const string& strRequestType);
};

#endif