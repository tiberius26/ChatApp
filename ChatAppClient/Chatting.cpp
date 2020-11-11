#include "Chatting.h"

void Chatting::ChatLoop(TCPManager& ClientSide)
{
	M_ClientLocal = &ClientSide;
	while (M_SentMessage != "end" && M_RecievedMessage != "end")
	{
		M_SendingThread = std::thread(&Chatting::Send, this);
		M_ListeningThread = std::thread(&Chatting::Receive, this);
		M_SendingThread.join();
		M_ListeningThread.join();
	}
}

Chatting::Chatting()
{
	M_Tools = new TTools;
	M_ClientLocal = nullptr;
}

void Chatting::CloseChat()
{
	delete M_Tools;
	M_ClientLocal = nullptr;
}

void Chatting::Receive()
{
	if (M_ClientLocal->Receive(M_RecievedMessage))
	{
		std::cout << std::endl << "Received: " << M_RecievedMessage << std::endl;
		//system("pause");
	}
	else { M_Tools->Debug("Can't recieve message", RED); }
}

void Chatting::Send()
{
	std::cout << "Say: ";
	std::getline(std::cin, M_SentMessage);

	if (!M_ClientLocal->Send(M_SentMessage))
	{
		M_Tools->Debug("Can't send message", RED);
	}
	if (M_SentMessage != "end") { M_SentMessage.clear(); }
}
