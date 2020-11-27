#pragma once
#include "TTools.h"
#include "TCPManager.h"
#include <thread>
#include <map>
class Chatting
{
public:
	void ChatLoop(TCPManager& ServerSide);
	Chatting();
	void CloseChat();
	bool GetIsChatOver() { return m_IsChatOver; }
	//void Receive(TCPManager& ServerSide);
	//void Send(TCPManager& ServerSide);
	void Delay(int DelayBy) { SDL_Delay(500); }
	void SaveLog(int LogCount);
private:
	std::string m_SentMessage;
	std::string m_RecievedMessage;
	TTools* m_Tools;
	std::thread m_ListeningThread;
	std::thread m_SendingThread;
	void Receive(std::string Client);
	void Send(std::string Client);
	TCPManager* m_ServerLocal;
	std::string m_SendMessage;
	
	bool m_IsChatOver;
	/*void test();*/
	std::map<std::string, std::thread>m_ListeningThreads;
	std::map<std::string, std::thread>m_SendingThreads;

	std::string m_ChatLog;
};

