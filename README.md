#Smart Home SDK
```See Also``` [SmartHomeSimulator repo](https://github.com/zeeshanejaz/SmartHomeSimulator)

This repo contains the source code for SDK for the SmartHomeSimulator which is built as a simple Client-Server application. The system architecture is presented in the following diagram. This SDK connects with the server (simulator) and interfaces the various features. The SDK is implemented as a shared object (SO) on Linux and as dynamic linked library (DLL) on windows. 

![System Architecture](https://github.com/zeeshanejaz/SmartHomeSimulator/raw/master/architecture.png)

##The C Style API
The SDK can be used as a C Style API built on top of the OO code. For this, include the ```SmartHomeSDK.h``` header file available in the release. Once included, you can be invoke the functions exposed. The list and functionality of these functions is presented in the following text.

###Initialization and Uninitialization
Initialization of the SDK essentially allocates the necessary resources for the current session e.g., a TCP/IP connection with the simualtor. The session must be closed e.g., on program exist by uninitializing the SDK. The methods for initialization and uninitialization are presented as follows.

```c++
\* initializes the required resource e.g., connection with the simulator *\
void SHAPI_Initialize();

\* free up the resources e.g., by disconnecting from the simulator *\
void SHAPI_Dispose();
```

###Enumeration Requests
The dynamic layout and hierarchical nature of the SmartHome requires a method for enumeration of various entities. For example, we might need to find out how many devices are in a particular room of a particular floor. Also, the dynamic layout of the simulator allows changing the number of floors and number of room on each floor. We can use the following method to perform enumeration requests.

```c++
\* get how many floors are in the SmartHome *\
int SHAPI_GetFloorCount();

\* get how many room are in the given floor number *\
int SHAPI_GetRoomCount(int floorNumber);

\* get how many devices are there in the given room of the given floor number *\
int SHAPI_GetDeviceCount(int floorNumber, int roomNumber);

\* get how many devices are paired with the device identified by device id *\
int SHAPI_GetPairedDevicesCount(int deviceId);
```

