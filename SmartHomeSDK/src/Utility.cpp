#include "Utility.h"

using namespace::std;

Utility::Utility(void)
{
}


Utility::~Utility(void)
{
}

vector<string> Utility::split(const string &s, 
							  char delim, 
							  vector<string> &elems) 
{
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) 
	{
		if(item.length() > 0)
			elems.push_back(item);
    }
    return elems;
}

vector<string> Utility::Split(const string &s,
							  char delim)
{
    vector<string> elems;
    return split(s, delim, elems);
}

int Utility::StringToInteger(const string &s)
{	
	return atoi(s.c_str());
}

bool Utility::StringToBool(const string &s)
{
	string temp = ToLower(s);
	
	if(temp.compare("true") == 0)
		return true;		
	
	else if(temp.compare("false") == 0)
		return false;
	
	else if(temp.compare("0") == 0)
		return false;		
	
	else
		return true;
}

string Utility::IntegerToString(const int i)
{
	stringstream ss;
	ss << i;
	return ss.str();
}

string Utility::ToLower(const string& s)
{
	string data = string(s);
	transform(data.begin(), data.end(), data.begin(), ::tolower);
	return data;
}