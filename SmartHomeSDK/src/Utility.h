#pragma once

#ifndef __UTILITYDEFINITION__

#define __UTILITYDEFINITION__

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#include <stdlib.h>

using namespace::std;

class Utility
{
public:
	Utility(void);
	~Utility(void);

	static vector<string> Split(const string &s, char delim);

	static int StringToInteger(const string &s);

	static bool StringToBool(const string &s);

	static string IntegerToString(const int i);

	static string ToLower(const string& s);

private:
	static vector<string> split(const string &s, char delim, vector<string> &elems);
};

#endif