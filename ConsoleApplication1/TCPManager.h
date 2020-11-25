#pragma once
#include <string>
#include <SDL.h>
#include <SDL_net.h>
#include "TTools.h"
#include <map>

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
	int GetUserCount() { return m_UserCount; }
private:
	IPaddress m_IP;

	TCPsocket m_ListenSocket;
	TCPsocket m_ClientSocket;

	std::string message;

	int m_MessageLength;

	const int C_PORT = 1234;
	const int C_BUFFER = 2000;

	TTools* m_Tools;
	int m_UserCount;
	std::map<std::string, TCPsocket> m_ClientList;
	char m_UserID[10] = { '\0' };
	char m_SendingLoopID[10] = { '\0' };
	char m_RecievingLoopID[10] = { '\0' };
	char m_ClosingSocketID[10] = { '\0' };

};

