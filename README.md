#Smart Home SDK
```See Also``` [SmartHomeSimulator repo](https://github.com/zeeshanejaz/SmartHomeSimulator)

This repo contains the source code for SDK for the SmartHomeSimulator which is built as a simple Client-Server application. The system architecture is presented in the following diagram. This SDK connects with the server (simulator) and interfaces the various features. The SDK is implemented as a shared object (SO) on Linux and as dynamic linked library (DLL) on windows. 

![System Architecture](https://github.com/zeeshanejaz/SmartHomeSimulator/raw/master/architecture.png)

## The Basics
SmartHome simulator communicates with the SDK using custom application layer protocol built on TCP/IP. A smart home can be described using the following relationship between its entities.

### SmartHome Building
A Smart Home is a building with a name and an address. There can be many floors in the Smart Home.

### Floor
A floor is uniquely identified by it floor number, which is unique in the building. A floor has a name e.g., *Ground Floor* and it can have many rooms.

### Room
A room is also a named entity e.g., it can have a name *Living Room*. A room must be accessed by it number, which is only unique on its floor. Therefore, a room must be identified using both its floor number and its room number.

### Device
A room can have many devices. A device has a type e.g., bulb, air conditioner, window, CD player, and is uniquely identified by its integer Device ID. A device can have many capabilities like ```CommandEnabled``` ```TextEnabled``` and ```SafetyRelated```. All devices can be powered on or off if they are currently online. A ```CommandEnabled``` device is capable of accepting numerical commands e.g., 0-n where each command is mapped to a certain functionality of the device. For example, a window is a command enabled device and accepts 2 commands for opening and closing respectively. A ```TextEnabled``` command is capable of returning human readable status messages e.g., the CD player can return the name of the current track being played. A ```SafetyRelated``` device has an added feature that it can tell when it is safet to operate the device. For example, a window many only open or close when it is safe to do so. In unsafe state, if the window is tried to close using the SDK, an exception is generated which must be handeled by the user. Capabilities of a device can be queried using the capability functions (see below).

### Paired Devices
A device can have a set of associated devices such that, when we turn a device on or off, all associated devices are also turned on or off. This feature is useful in rooms like conference rooms or theaters where a user might want to turn off all lights together.

## Compilation
The SmartHomeSDK can be compiled both on Linux and Windows as 32-bit and 64-bit libraries. The provided Makefiles are tested on Ubuntu as well as on Windows 10 Ubuntu Bash Shell. Run the following commands.

First lets ensure that we have necessary development tools installed.

```bash
sudo apt-get install make gcc g++
```

Next, we shall compile the shared object (SO) and package it with headers for release. The first command below cleans up any old build attempts. The second command performs the compilation of the library SDK as a shared object. The third command copies the required header files and creates the release package in the release folder.

```bash
make clean
make
make headers
```

Now we can test using the test program provided. First, make sure that the SmartHome Simulator is running. Then execute the following commands.

```bash
cd test
make clean
make
./release/SmartHomeSDKTest.o
```

![Simulator Test](/build.png)

The first of the above command changes the current directory to enter the test sub-directory. Then, we perform a clean operation to remove temporary files. After that, the ```make``` command compiles and links the test program into an executable. The output is created in the release folder, where the SO file is also copied for runtime loading. The last command executes the test program, which connects to the simulator and issues a few commands to power up a few devices as shown below.

![Simulator Test](/simtest.png)

## The C Style API
The SDK can be used as a C Style API built on top of the OO code. For this, include the ```SmartHomeSDK.h``` header file available in the release. Once included, you can be invoke the functions exposed. The list and functionality of these functions is presented in the following text.

### Initialization and Dispose
Initialization of the SDK essentially allocates the necessary resources for the current session e.g., a TCP/IP connection with the simulator. The session must be closed e.g., on program exit by disposing the resources. The methods for initialization and dispose are presented as follows.

```c++
/* initializes the required resource e.g., connection with the simulator */
void SHAPI_Initialize();

/* free up the resources e.g., by disconnecting from the simulator */
void SHAPI_Dispose();
```

### Enumeration Requests
The dynamic layout and hierarchical nature of the SmartHome requires a method for enumeration of various entities. For example, we might need to find out how many devices are in a particular room of a particular floor. Also, the dynamic layout of the simulator allows changing the number of floors and number of room on each floor. We can use the following method to perform enumeration requests.

```c++
/* get how many floors are in the SmartHome */
int SHAPI_GetFloorCount();

/* get how many room are in the given floor number */
int SHAPI_GetRoomCount(int floorNumber);

/* get how many devices are there in the given room of the given floor number */
int SHAPI_GetDeviceCount(int floorNumber, int roomNumber);

/* get how many devices are paired with the device identified by device id */
int SHAPI_GetPairedDevicesCount(int deviceId);
```

### Device Search
All operations on devices are performed using their Device ID. These IDs can be retrieved using the device search methods. The result of the functions is a vector of IDs.

```c++
/* get device ids for all devices in the given room number and floor number */
vector<int>* SHAPI_GetDevices(int floorNumber, int roomNumber);

/* get ids of all paired devices against the given device id */
vector<int>* SHAPI_GetPairedDevices(int deviceId);
```

### Name functions
As mentioned before, building, floors, rooms and devices are all named entities. Their names can be retrieved using the following methods.

```c++
/* get the name of the smart home building e.g., Cool Mansion */
string SHAPI_GetBuildingName();

/* get the name of a given floor number e.g., Second Floor */
string SHAPI_GetFloorName(int floorNumber);

/* get the name of a given room on a given floor e.g., Living Room */
string SHAPI_GetRoomName(int floorNumber, int roomNumber);

/* get name of the device with the given device id e.g., CD Player */
string SHAPI_GetDeviceName(int deviceId);
```

### Reading and Writing Attributes
Read and write the various attributes of entities in the smart home.

```c++
/* get the street address of the smart home building */
string SHAPI_GetBuildingStreetAddress();	

/* check if a device is powered on or off, return value represents the powered on status */
bool SHAPI_GetDevicePoweredOn(int deviceId);

/* check if a device is online or offline, return value represents the online status */
bool SHAPI_GetDeviceOnlineStatus(int deviceId);

/* powered a device on or off, return value represents the new powered on status  */
bool SHAPI_SetDevicePoweredOn(int deviceId, bool newStatus);

/* set a device online or offline, return value represents the new online on status  */
bool SHAPI_SetDeviceOnlineStatus(int deviceId, bool newStatus);

```

### Evaluate Device Capability
As mentioned previously, various devices have additional capabilities which can dynamically queried using the following functions.

```c++
/* check if the given device return text messages */
bool SHAPI_IsTextEnabled(int deviceId);

/* check if the given device accepts commands */
bool SHAPI_IsCommandEnabled(int deviceId);

/* check if the given device is safety related */
bool SHAPI_IsSafetyRelated(int deviceId);

/* get the current text status from the given text enabled device */
string SHAPI_GetTextStatus(int deviceId);

/* get the current safety state of the given safety related device */
bool SHAPI_GetSafetyStatus(int deviceId);

/* get the max command id from the command enabled device, min command id is always 0 */
int SHAPI_GetMaxCommandId(int deviceId);

/* execute a command between 0 and max command id on the given command enabled device */
bool SHAPI_ExecuteCommand(int deviceId, int commandId);
````

## Sample Program
Using the functions presented above, we can write programs to control the Smart Home. For example the following program connects the simulator, displays its name and performs various actions on the devices before exiting the program.

```c++
#include <iostream>
#include "SmartHomeSDK.h"

using namespace std;

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
	cout << "\nPress ENTER to continue...";	
	cin.get();

	//Smart Home API must be shutdown at the end of the execution
	SHAPI_Dispose();
}
```