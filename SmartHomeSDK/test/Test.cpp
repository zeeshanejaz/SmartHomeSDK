#include <iostream>
#include "SmartHomeSDK.h"

using namespace std;

void wait()
{
	cout << "\nPress ENTER to continue...";	
	cin.get();
}

int main()
{	
	//Smart Home API must be initialized before any calls
	SHAPI_Initialize();

	string name = SHAPI_GetBuildingName();
	cout << name << "\n";

	string status = SHAPI_GetTextStatus(19);
	cout << status << "\n";
	
	vector<int>* ids = SHAPI_GetDevices(1,1);
	cout << ids->size() << "\n";
		
	vector<int>* paired = SHAPI_GetPairedDevices(1);
	cout << paired->size() << "\n";

	bool onStatus = SHAPI_GetDevicePoweredOn(1);
	if(onStatus)
		cout << "True \n";
	else
		cout << "False \n";
		
	bool result = SHAPI_SetDevicePoweredOn(1, true);
	if(result)
		cout << "True \n";
	else
		cout << "False \n";
		
	//ask user to press enter before exiting
	wait();

	//Smart Home API must be shutdown at the end of the execution
	SHAPI_Dispose();
}