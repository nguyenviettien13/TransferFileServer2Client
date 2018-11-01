#pragma once
#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib") //Required for WinSock
#include <WinSock2.h> //For win sockets
#include <string> //For std::string
#include <iostream> //For std::cout, std::endl
#include "FFileTransferData.h"

using namespace std;

enum Packet
{
	P_ChatMessage,
	P_FileTransferRequestFile, //Sent to request a file
	P_FileTransfer_EndOfFile, //Sent for when file transfer is complete
	P_FileTransferByteBuffer, //Sent before sending a byte buffer for file transfer
	P_FileTransferRequestNextBuffer //Sent to request the next buffer for file
};


struct Connection
{
	SOCKET socket;
	//file transfer data
	FileTransferData file; //Object that contains information about our file that is being sent to the client from this server
};


class Server
{
//private attribute
private:
	Connection connections[100];
	int TotalConnections = 0;

	SOCKADDR_IN addr; //Address that we will bind our listening socket to
	int addrlen = sizeof(addr);
	SOCKET sListen;
//Public attribute
public:


//Private method
private:
	static void ClientHandlerThread(int ID);
	bool ProcessPacket(int ID, Packet _packettype);
	bool GetPacketType(int ID, Packet & _packettype);
	bool Getint32_t(int ID, int32_t & _int32_t);
	bool recvall(int ID, char * data, int totalbytes);
	bool GetString(int ID, std::string & _string);
	bool SendString(int ID, std::string & _string);
	bool Sendint32_t(int ID, int32_t _int32_t);
	bool sendall(int ID, char * data, int totalbytes);
	bool SendPacketType(int ID, Packet _packettype);
	bool HandleSendFile(int ID);
//public method
public:
	Server(int PORT, bool BroadcastPublically = false);
	bool ListenForNewConnection();
	~Server();
};

static Server * serverptr; //Serverptr is necessary so the static ClientHandler method can access the server instance/functions.