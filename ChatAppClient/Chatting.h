#pragma once
#include "TTools.h"
#include "TCPManager.h"
class Chatting
{
public:
	void ChatLoop(TCPManager& ServerSide);
	Chatting();
	void CloseChat();
private:
	std::string M_SentMessage;
	std::string M_RecievedMessage;
	TTools* M_Tools;
	bool M_AmReceiving;
};

