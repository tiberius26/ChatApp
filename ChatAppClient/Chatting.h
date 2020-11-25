#pragma once
#include "TTools.h"
#include "TCPManager.h"
#include <thread>
class Chatting
{
public:
	void ChatLoop(TCPManager& ClientSide, std::string UserName);
	Chatting();
	void CloseChat();
	//void Receive(TCPManager& ServerSide);
	//void Send(TCPManager& ServerSide);

private:
	std::string m_SentMessage;
	std::string m_RecievedMessage;
	TTools* m_Tools;
	std::thread m_ListeningThread;
	std::thread m_SendingThread;
	void Receive();
	void Send();
	TCPManager* m_ClientLocal;
	std::string m_UserName;
};

