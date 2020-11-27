#pragma once
#include "TTools.h"
#include "TCPManager.h"
#include <thread>
#include <map>
class Chatting
{
public:
	Chatting();

	void ChatLoop(TCPManager& ServerSide);
	void CloseChat();
	void Delay(int DelayBy) { SDL_Delay(500); }
	void SaveLog(int LogCount);

	bool GetIsChatOver() { return m_IsChatOver; }
private:

	//Strings:
	std::string m_SentMessage;
	std::string m_RecievedMessage;
	std::string m_SendMessage;
	std::string m_ChatLog;

	//Pointers:
	TTools* m_Tools;
	TCPManager* m_ServerLocal;

	//Threads:
	std::thread m_ListeningThread;
	std::thread m_SendingThread;

	//Booleans
	bool m_IsChatOver;
	
	//Maps:
	std::map<std::string, std::thread>m_ListeningThreads;
	std::map<std::string, std::thread>m_SendingThreads;

	//Private methods
	void Receive(std::string Client);
	void Send(std::string Client);
};

