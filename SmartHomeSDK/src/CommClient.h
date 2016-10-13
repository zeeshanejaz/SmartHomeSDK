#pragma once

#ifndef __COMMCLIENTDEFINITION__

#define __COMMCLIENTDEFINITION__

#include "Socket.h"
#include "ProtocolPacket.h"

#include <iostream>
#include <string>
#include <tr1/functional>

#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define ServerAddress "127.0.0.1";
#define ServerPort 7878;


class CommClient
{
public:
	CommClient(void);
	~CommClient(void);

	//connection related
	bool Connect();
	bool IsConnected();
	void Disconnect();

	//communication related
	bool GetResponseAsync(ProtocolPacket* requestPacket);
	ProtocolPacket* GetResponse(ProtocolPacket* requestPacket);
		
	//packet recieve delegate
	tr1::function<void (const ProtocolPacket&)> OnPacketRecieved;

private:
	Socket* clientSocket;
	bool keepRunning;
	pthread_t readerThread;
	ProtocolPacket* lastResponse;
	
	pthread_mutex_t count_mutex;
	pthread_cond_t condition_var;

	void startReaderThread();
	void run();
	void stopReaderThread();

	static void* threadStart(void* arg) 
	{ 
		((CommClient*)arg)->run();
		return NULL;
	}
};

#endif