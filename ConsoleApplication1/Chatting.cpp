#include "Chatting.h"

void Chatting::ChatLoop(TCPManager& ClientSide)
{
	M_ServerLocal = &ClientSide;
	M_SendingThread = std::thread(&Chatting::Send, this);
	M_ListeningThread = std::thread(&Chatting::Receive, this);
	M_SendingThread.detach();
	M_ListeningThread.join();
}

void Chatting::Receive()
{
	while (M_RecievedMessage != "end")
	{
		if (M_ServerLocal->Receive(M_RecievedMessage))
		{
			std::cout << std::endl << "Received: " << M_RecievedMessage << std::endl;
			//system("pause");
		}
		else { M_Tools->Debug("Can't recieve message", RED); }
	}
}

void Chatting::Send()
{
	while (M_SentMessage != "end")
	{
		std::cout << "Say: ";
		std::getline(std::cin, M_SentMessage);

		if (!M_ServerLocal->Send(M_SentMessage))
		{
			M_Tools->Debug("Can't send message", RED);
		}
		if (M_SentMessage != "end") { M_SentMessage.clear(); }
	}
}

Chatting::Chatting()
{
	M_Tools = new TTools;
	M_ServerLocal = nullptr;
}

void Chatting::CloseChat()
{
	delete M_Tools;
	M_ServerLocal = nullptr;
}