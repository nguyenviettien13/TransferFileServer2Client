#pragma once
#include "FileTransferData.h"
#include <string>

using namespace std;
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib") //Required for WinSock
#include <WinSock2.h> //For win sockets
#include <string> //For std::string
#include <iostream> //For std::cout, std::endl, std::cin.getline

enum Packet
{
	P_ChatMessage,
	P_FileTransferRequestFile, //Sent to request a file
	P_FileTransfer_EndOfFile, //Sent for when file transfer is complete
	P_FileTransferByteBuffer, //Sent before sending a byte buffer for file transfer
	P_FileTransferRequestNextBuffer //Sent to request the next buffer for file
};

class Client
{
/*Private Attribute*/
private:
	FileTransferData file; //Object that contains information about our file that is being received from the server.
	SOCKET Connection;//This client's connection to the server
	SOCKADDR_IN addr; //Address to be binded to our Connection socket
	int sizeofaddr = sizeof(addr); //Need sizeofaddr for the connect function

/*Public Attribute*/
public:

/*Private Method*/
private:
	static void ClientThread();//why we need set it is static! because it was pass to CreateThread
	bool ProcessPacket(Packet _packettype);
	bool CloseConnection();
	//Send Function
	bool Sendint32_t(int32_t _int32_t);
	bool sendall(char * data, int totalbytes);
	bool SendPacketType(Packet _packettype);

	//Receive Function
	bool recvall(char * data, int totalbytes);
	bool Getint32_t(int32_t & _int32_t);
	bool GetPacketType(Packet & _packettype);
	bool GetString(std::string & _string);


/*Public Method*/
public:
	Client(std::string IP, int PORT);
	bool Connect();		
	bool SendString(std::string & _string, bool IncludePacketType = true);
	bool RequestFile(std::string FileName);
	~Client();
};

static Client * clientptr; //This client ptr is necessary so that the ClientThread method can access the Client instance/methods. Since the ClientThread method is static, this is the simplest workaround I could think of since there will only be one instance of the client.