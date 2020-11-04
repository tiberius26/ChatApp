#include "Chatting.h"

void Chatting::ChatLoop(TCPManager& ServerSide)
{

	while (M_SentMessage != "end" && M_RecievedMessage != "end")
	{
		if (M_AmReceiving)
		{
			if (ServerSide.Receive(M_RecievedMessage))
			{
				std::cout << std::endl << "Received: " << M_RecievedMessage << std::endl;
				system("pause");
				M_AmReceiving = false;
			}
			else { M_Tools->Debug("Can't recieve message", RED); }

		}
		else
		{
			std::cout << "Say: ";
			std::getline(std::cin, M_SentMessage);

			if (ServerSide.Send(M_SentMessage))
			{
				M_Tools->Log("Message sent");
				M_AmReceiving = true;
			}
			if (M_SentMessage != "end") { M_SentMessage.clear();}
		}
	}
}

Chatting::Chatting()
{
	M_Tools = new TTools;
	M_AmReceiving = true;

}

void Chatting::CloseChat()
{
	delete M_Tools;
}
