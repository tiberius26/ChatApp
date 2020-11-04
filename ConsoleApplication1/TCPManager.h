#pragma once
#include <string>
#include <SDL.h>
#include <SDL_net.h>
#include "TTools.h"

class TCPManager
{
public:
	bool Initialize(const char* IP, int port);
	bool OpenSocket();
	void ListenSocket();
	bool Send(const std::string& message);
	bool Receive(std::string& message);
	void CloseSocket();
	void ShutDown();
	TCPManager();
	~TCPManager();
private:
	IPaddress M_IP;

	TCPsocket M_ListenSocket;
	TCPsocket M_ClientSocket;

	std::string message;

	int M_MessageLength;

	const int C_PORT = 1234;
	const int C_BUFFER = 2000;

	TTools* Tools;

};

