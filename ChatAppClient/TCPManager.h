#pragma once
#include <string>
#include <SDL.h>
#include <SDL_net.h>
#include "TTools.h"

class TCPManager
{
public:
	bool Initialize();
	bool OpenSocket();
	bool Send(const std::string& message);
	bool Receive(std::string& message);
	void CloseSocket();
	void ShutDown();
	TCPManager();
	~TCPManager();
private:
	IPaddress M_IP;

	TCPsocket M_Socket;

	std::string message;

	int M_MessageLength;

	const int C_PORT = 1234;
	const int C_BUFFER = 2000;

	TTools* Tools;

};

