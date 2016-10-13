#pragma once

#ifndef __SMARTHOMESDKDEFITNITIONS__

#define __SMARTHOMESDKDEFITNITIONS__

#include "ProtocolManager.h"

#include <vector>
#include <string>

using namespace std;

//Basic concepts:
//--------------
//1) The following relationships exist in the simulator
//A Building has Floors
//	A Floor has Rooms
//		A Room has Devices
//Device have paired Devices
//
//2) Floors have zero based indexes called floor numbers. Floor numbers are unique e.g., there can be 
//only one floor 0. Also, floors numbers are consecutive i.e., if a building has 3 floor, the indexes
//will be {0, 1, 2}.
//
//3) Room numbers are also zero based indexes. Room numbers are not unique e.g., Room 0 may exist on 
//every floor. Room number are consecutive i.e., if a floor has 3 rooms, the indexes will be {0, 1, 2}
//
//4) Device ids are unique, but not consecutive. A building may only have one device with a given
//device id. Device ids can be any integers e.g., {1, 23, 16}
//
//5) Devices have paired devices. When a device is turned off, all paired devices are automatically 
//turned off. This pairing is not reflexsive i.e., BulbA--paired-with-->BulbB means that when BulbA is
//turned off, BulbB will turn off automatically, but not vice versa.
//
//6) Some device are more capable than others. Such as, a CD-Player can tell you the current track as
//well as accept commands for next track, play-pause, stop stc. This is discussed further in the later
//text/comments.

//---------------------------API management routines------------------------------//

//Initializes the SmartHome API.
//This method must be called before making calls to any other API methods.
void SHAPI_Initialize();

//This method must be called before exiting the application.
//After calling this method, no more calls can be made to any API method.
void SHAPI_Dispose();


//---------------------------Enumeration requests routines------------------------------//

//This method retrieves the total number of floors in the SmartHome.
int SHAPI_GetFloorCount();

//This method retrieves the total number of rooms on a given floor number in the SmartHome.
//Floor numbers are zero-based indexed i.e., the ground floor is floor 0, first floor is floor 1 etc.
int SHAPI_GetRoomCount(int floorNumber);

//This method retrieves the total number of devices on a given floor and a given room.
//Room numbers are not unique in the building, so they must be used in conjunction with floor number
//to uniquely identify hte room.
int SHAPI_GetDeviceCount(int floorNumber, int roomNumber);

//This method retrieves the total number of paired device, with a given device id.
//Device Ids are unique throught the SmartHome. Each device may be paired with a number of other devices.
//Paired devices turn off and turn on together. Refer to earlier text for further information.
int SHAPI_GetPairedDevicesCount(int deviceId);


//---------------------------Device search reoutines---------------------------//

//This method retrieves a pointer to a vector containing device ids of all devices, which are contained
//in the specified room. Since the room numbers are not unique, we also provide floor to uniquely 
//identify which room we are concerened with. This method is useful if one wishes to iterate over all 
//devices in a given room and perform a required operation.
vector<int>* SHAPI_GetDevices(int floorNumber, int roomNumber);

//Recall the concept of paired device as explained in earlier text. This method retrieves a points to a
//vector containing devices ids, of all devices that are paired with the given device id.
vector<int>* SHAPI_GetPairedDevices(int deviceId);


//---------------------------Attribute read reoutines---------------------------//

//This method reads the street address of the building from the simulator. This feature might come handy
//to show user friendly welcome messages.
string SHAPI_GetBuildingStreetAddress();

//This method reads the current "power status" of a given device id. The returned boolean is true if the
//device is powered on and vice versa.	
bool SHAPI_GetDevicePoweredOn(int deviceId);

//This method reads the "online status" of a given device id. The simulator implements offline/online 
//mode to mimic the locking feature as desired by a user. He may turn the device offline in order prevent 
//a remote client from modifying its status. When offline, all commands from remote clients are rejected.
bool SHAPI_GetDeviceOnlineStatus(int deviceId);


//---------------------------Name retrieval reoutines---------------------------//

//Read the building name. The simulators returns its version information as the building name. This
//method is useful for showing friendly welcome messages to the users.
string SHAPI_GetBuildingName();

//Each floor has a name e.g., ground floor, first floor. This name can be read using this method. It
//can be used for showing a more understandable view to the user e.g., a map view.
string SHAPI_GetFloorName(int floorNumber);

//Similar to floors, rooms also have names e.g., dining room, lobby , garage. This method reads the 
//name of a room, provided the floor and room numbers are known.
string SHAPI_GetRoomName(int floorNumber, int roomNumber);

//Each device has a name, e.g., bulb, cd-player, powered-window. Names of devices can be read if the 
//device id is known. Since the device ids are unique, therefore floor and room numbers are not required.
//Device ids can be retrieved using SHAPI_GetDevices method.
string SHAPI_GetDeviceName(int deviceId);


//---------------------------Setting status reoutines---------------------------//

//A device can be powered off or on using this method. The deivce is must be known in order to set its
//power status. The parameter newStatus should be true if powering on a device is desired and vice versa.
bool SHAPI_SetDevicePoweredOn(int deviceId, bool newStatus);

//Recall the offline/online mode feature from earlier text. A device can be set to offline or online using 
//this method. The deivce is must be known in order to set its online status. The parameter newStatus 
//should be true if setting a device online is desired and vice versa.
bool SHAPI_SetDeviceOnlineStatus(int deviceId, bool newStatus);


//---------------------------Device capability check reoutines---------------------------//

//Different devices have different capabilities. The most simple is a Bulb, which can be powered on and
//off. Other devices such as CD-Play can return the current track, and hence are called text enabled. 
//This method return true if the given device id is text enabled and false otherwise.
bool SHAPI_IsTextEnabled(int deviceId);

//Another capability of devices is to accept commands e.g., sending a temperature controller a command 
//to increase desired temperature. This method determines if the specified device is capable of 
//processing commands.
bool SHAPI_IsCommandEnabled(int deviceId);

//Some devices require safety consideration for their operation e.g., a window cannot be shut automatically
//if a person has his hands in the frame. For this purpose, some device are capable of returning safety
//status of the device. This method determines if the device is safety related or not.
bool SHAPI_IsSafetyRelated(int deviceId);


//---------------------------Device capability use routines---------------------------//

//Recall text-enabled devices from earlier text. A text enabled device can return a printable string for a
//friendly message for the user. This method can retrieve such messages. This mehtod must only be used for
//text enabled devices.
string SHAPI_GetTextStatus(int deviceId);

//Recall safety enabled devices from earlier text. This method return the safety status of such devices. 
//The boolean value true is returned if the device is currently safe. When unsafe, the device must not be
//operated from a remote client. This method must only be called for safety related devices.
bool SHAPI_GetSafetyStatus(int deviceId);

//The following two functions are related to command-enabled devices. Commands are integers that are 
//associated with certain functionality e.g., 0 is temperature up, 1 is for temperature down etc. Students
//are expected to experiment with these numbers to figure out what integer is associated with which command.
bool SHAPI_ExecuteCommand(int deviceId, int commandId);

//For a generic implementation of a command enabled device, different devices may have different number of 
//possible commands. This method return how many commands are supported by a certain command-enabled device.
//This method is useful for automatically generating a generic choice menu for command-enabled devices. E.g.,
//1) Run command 0
//2) Run command 1
//3) Run command 2
//4) Run command 3
//This method must only be called for command enabled devices.
int SHAPI_GetMaxCommandId(int deviceId);

#endif
