#include "ProtocolPacket.h"

using namespace::std;

ProtocolPacket::ProtocolPacket(void)
{
}

ProtocolPacket::~ProtocolPacket(void)
{
}

ProtocolPacket* ProtocolPacket::Parse(const string& strPacket)
{
	vector<string> tokens = Utility::Split(strPacket, '|');
	int length = tokens.size();

	if (length < 3)
		throw new string("Invalid packet format. Expected mandatory segment tokens.");

	ProtocolPacket* packet = new ProtocolPacket();
	packet->PacketType = EnumParser::ParsePacketType(tokens[0]);
	packet->TargetType = EnumParser::ParseTargetType(tokens[1]);
	packet->RequestType = EnumParser::ParseRequestType(tokens[2]);
	
	if (length >= 4)
    {
        packet->TargetArticle.assign(tokens[3]);

        for (int i = 4; i < length; i++)
            packet->Parameters.push_back(tokens[i]);
    }
	
    return packet;
}

ProtocolPacket* ProtocolPacket::PreparePacket (enum PacketType PacketType,
											   enum TargetType TargetType, 
											   enum RequestType RequestType,
											   const string& TargetArticle,
											   int nArgs, ...)
{
	ProtocolPacket* packet = new ProtocolPacket();
	packet->PacketType = PacketType;
	packet->TargetType = TargetType;
	packet->RequestType = RequestType;

	if(TargetArticle.empty())
		packet->TargetArticle.assign("");
	else
		packet->TargetArticle.assign(TargetArticle);
	
	//access ellipsis
	va_list list;
	va_start(list, nArgs);

	for(int i = 0; i < nArgs; i++)
	{
		int arg = va_arg(list, int);
		stringstream st;
		st << arg;
		packet->Parameters.push_back(st.str());
	}

	va_end(list);

	return packet;
}

ProtocolPacket* ProtocolPacket::PrepareRequest(enum TargetType targetType, 
											   enum RequestType requestType,
											   const string& targetArticle,
											   int id1, int id2)
{
	ProtocolPacket* request = NULL;
	
	if(id1 == UNUSED)
	{
		//id1 is invalid, no need to check id2
		request = PreparePacket(Request, targetType, requestType, targetArticle , 0);
	}
	else if (id2 == UNUSED)
	{
		//id1 is valid, but id2 is invalid
		request = PreparePacket(Request, targetType, requestType, targetArticle , 1, id1);
	}
	else
	{
		//id1 and id2 both are valid
		request = PreparePacket(Request, targetType, requestType, targetArticle , 2, id1, id2);
	}

	return request;
}


string ProtocolPacket::ToString()
{
	stringstream stringBuilder;

	//mandatory packets
    stringBuilder << "|" << PacketType << "|" << TargetType << "|" << RequestType << "|";
            
            
    if (TargetArticle.length() > 0)
        stringBuilder << TargetArticle << "|";
	else
		stringBuilder << " |";
		
    if (Parameters.size() > 0)
    {
		vector<string>::iterator itr;
        for ( itr = Parameters.begin(); itr != Parameters.end(); ++itr )
        {
            stringBuilder << *itr << "|";
        }
    }

    return stringBuilder.str();
}


string ProtocolPacket::ExtractPayloadString()
{
	return Parameters.front();
}

vector<int>* ProtocolPacket::ExtractPayloadIntegerVector()
{
	vector<int>* data = new vector<int>();
		
	vector<string>::iterator itr;
    for ( itr = Parameters.begin(); itr != Parameters.end(); ++itr )
    {
        data->push_back(Utility::StringToInteger(*itr));
    }
	
	return data;
}

vector<string>* ProtocolPacket::ExtractPayloadStringVector()
{
	vector<string>* data = new vector<string>();
		
	vector<string>::iterator itr;
    for ( itr = Parameters.begin(); itr != Parameters.end(); ++itr )
    {
        data->push_back(string(*itr));
    }
	
	return data;
}