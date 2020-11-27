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
	bool Send(const std::string& message, std::string ToWho);
	bool Receive(std::string& message, std::string ToWho);
	void CloseSocket();
	void ShutDown();
	TCPManager();
	~TCPManager();
	int GetUserCount() { return m_UserCount; }
	void TurnListeningOff() { m_AmListeningForUsers = false;}
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
	std::string m_UserID;
	std::string m_SendingLoopID;
	std::string m_RecievingLoopID;
	std::string m_ClosingSocketID;
	std::string CheckEnd() { return m_CheckMessage; };
	bool m_AmListeningForUsers;
	std::string m_CheckMessage;

};

