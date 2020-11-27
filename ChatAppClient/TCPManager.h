#pragma once
#include <string>
#include <SDL.h>
#include <SDL_net.h>
#include "TTools.h"

class TCPManager
{
public:
	TCPManager();
	~TCPManager();

	void CloseSocket();
	void ShutDown();

	bool Initialize(const char* IP, int port);
	bool OpenSocket();
	bool Send(const std::string& message);
	bool Receive(std::string& message);

private:
	//IP
	IPaddress m_IP;

	//Sockets:
	TCPsocket m_Socket;

	//Ints:
	int m_MessageLength;
	const int C_BUFFER = 2000;

	//Pointers:
	TTools* Tools;

};

