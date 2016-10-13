#include "CommClient.h"

CommClient::CommClient(void)
{
	clientSocket = NULL;
	OnPacketRecieved = NULL;
	keepRunning = false;
	lastResponse = NULL;

	count_mutex = PTHREAD_MUTEX_INITIALIZER;
	condition_var = PTHREAD_COND_INITIALIZER;
}

CommClient::~CommClient(void)
{
}

bool CommClient::Connect()
{
	if(CommClient::clientSocket != NULL)
		Disconnect();

	string serverAddress = ServerAddress;
	int serverPort = ServerPort;

	CommClient::clientSocket = new Socket();
	if(!clientSocket->create())
		return false;

	bool connected = clientSocket->connect(serverAddress, serverPort);

	//clientSocket remains valid for retries if one wishes for it.
	//explicitly close it to for invalidated.
	if(!connected)
	{	
		clientSocket->closeSocket();
		throw new string("Unable to connect to the Smart Home Simulator.\nMake sure that the simulator is running.");
	}

	startReaderThread();

	return connected;
}

bool CommClient::IsConnected()
{
	return clientSocket->is_valid();
}

void CommClient::Disconnect()
{	
	clientSocket->closeSocket();
	stopReaderThread();
}

bool CommClient::GetResponseAsync(ProtocolPacket* requestPacket)
{
	if(!IsConnected())
		return NULL;

	string strPacket = requestPacket->ToString();
	return clientSocket->send(strPacket);
}

ProtocolPacket* CommClient::GetResponse(ProtocolPacket* requestPacket)
{
	if(!IsConnected())
		return NULL;
	
	struct timespec   ts;
	struct timeval    tp;
    
	/* Convert from timeval to timespec */
	gettimeofday(&tp, NULL);	
    ts.tv_sec  = tp.tv_sec;
    ts.tv_nsec = tp.tv_usec * 1000;
    ts.tv_sec += 5; // 5 second wait
	
	//lock mutex and place request
	pthread_mutex_lock( &count_mutex );

	lastResponse = NULL;

	string strPacket = requestPacket->ToString();
	if(!clientSocket->send(strPacket))
		throw new string("Unexpected error while communicating with the Smart Home simulator.");

	//create wait condition and allow the reader thread to read response
	pthread_cond_timedwait( &condition_var, &count_mutex, &ts );
	
	//reply must have arrived
	ProtocolPacket* response = lastResponse;
	
	//unlock mutex
	pthread_mutex_unlock( &count_mutex );

	return response;
}

void CommClient::startReaderThread()
{
	keepRunning = true;
	
	int rc = pthread_create(&readerThread, NULL, threadStart, (void *)this);
	if(rc)
		throw new string("Error running reader thread for the commuincation client.");
}

void CommClient::run()
{
	string strPacket;
	int read = 0;

	while(keepRunning)
	{
		//sleep(100);

		read = clientSocket->recv(strPacket);
		if(read <= 0)
			break;
		
		ProtocolPacket* packet = ProtocolPacket::Parse(strPacket);

		if(packet != NULL)
		{
			if(OnPacketRecieved!=NULL)
				OnPacketRecieved(*packet);

			//lock mutex and publish response
			pthread_mutex_lock( &count_mutex );

			lastResponse = packet;

			//signal any waiter
			pthread_cond_signal( &condition_var );

			//unlock mutex
			pthread_mutex_unlock( &count_mutex );

		}		
	}

	//pthread_exit(NULL);
}

void CommClient::stopReaderThread()
{
	keepRunning = false;

	pthread_exit(NULL);
}
