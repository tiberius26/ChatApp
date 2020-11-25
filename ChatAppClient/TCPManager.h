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
	bool Send(const std::string& message);
	bool Receive(std::string& message);
	void CloseSocket();
	void ShutDown();
	TCPManager();
	~TCPManager();
private:
	IPaddress m_IP;

	TCPsocket m_Socket;

	std::string message;

	int m_MessageLength;

	const int C_BUFFER = 2000;

	TTools* Tools;

};

