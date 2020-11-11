#pragma once
#include "TTools.h"
#include "TCPManager.h"
#include <thread>
class Chatting
{
public:
	void ChatLoop(TCPManager& ServerSide);
	Chatting();
	void CloseChat();
	//void Receive(TCPManager& ServerSide);
	//void Send(TCPManager& ServerSide);

private:
	std::string M_SentMessage;
	std::string M_RecievedMessage;
	TTools* M_Tools;
	std::thread M_ListeningThread;
	std::thread M_SendingThread;
	void Receive();
	void Send();
	TCPManager* M_ServerLocal;
};

