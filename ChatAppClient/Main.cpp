#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_net.h>
#include "TTools.h"
#include "TCPManager.h"

//struct to store host adress(ip) and port number


bool AmReceiving = true;
bool AmRunning = true;

const int C_PORT = 1234;
const int C_BUFFER = 2000;
int main(int argc, char* argv[])
{
	TTools* Tools = new TTools;
	TCPManager ClientSide;
	ClientSide.Initialize();
	ClientSide.OpenSocket();
	system("cls");
	std::cout << "========================================" << std::endl;
	std::cout << "=     BSF Communications department    =" << std::endl;
	std::cout << "========================================" << std::endl;

	std::string SentMessage;
	std::string RecievedMessage;
	int MessageLength = 0;
	while (SentMessage != "end" && RecievedMessage != "end")
	{
		if (AmReceiving)
		{
			if (ClientSide.Receive(RecievedMessage))
			{
				std::cout << std::endl << RecievedMessage << std::endl;
				system("pause");
				AmReceiving = false;
			}
			else { Tools->Debug("Can't recieve message", RED); }

		}
		else 
		{
			std::cout << "Say: ";
			std::getline(std::cin, SentMessage);
			MessageLength = SentMessage.length() + 1;

			if (ClientSide.Send(SentMessage))
			{
				Tools->Log("Message sent");
				AmReceiving = true;
			}
			SentMessage.clear();
		}
	}

	ClientSide.CloseSocket();
	ClientSide.ShutDown();
	delete Tools;

	system("Pause");
	return 0;
}