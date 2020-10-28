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
private:
	IPaddress M_IP;

	TCPsocket M_Socket = nullptr;

	std::string message;

	int M_MessageLength = 0;

	bool AmReceiving = true;
	bool AmRunning = true;

	const int C_PORT = 1234;
	const int C_BUFFER = 2000;

	TTools* Tools = nullptr;

};

