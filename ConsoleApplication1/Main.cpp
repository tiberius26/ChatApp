#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_net.h>
#include "TTools.h"
#include "TCPManager.h"

//struct to store host adress(ip) and port number
IPaddress ip; //host and port number essentially

//sockets to listen in on incoming connections
TCPsocket ListenSocket = nullptr;
//sockets to transfer data to client
TCPsocket ClientSocket = nullptr;

//Message to be sent to client(s)
std::string message;

bool AmReceiving = true;
bool AmRunning = true;

const int C_PORT = 1234;
const int C_BUFFER = 2000;
int main(int argc, char* argv[])
{
	TTools* Tools = new TTools;
	TCPManager ServerSide;
	ServerSide.Initialize();

	std::cout << "========================================" << std::endl;
	std::cout << "=     BSF Communications department    =" << std::endl;
	std::cout << "========================================" << std::endl;

	ServerSide.OpenSocket();
	ServerSide.ListenSocket();

	system("cls");
	std::cout << "========================================" << std::endl;
	std::cout << "=     BSF Communications department    =" << std::endl;
	std::cout << "========================================" << std::endl;
	//create a friendly message for the client

	message = "Welcome to the chat";

	//we need length of message in order to send data
	int MessageLength = message.length() + 1; //+1 because C adds a null at the end of strings +1 terminates null aka '\0'
	//send message via open sockets which are opened above
	if (ServerSide.Send(message) < MessageLength)
	{
		Tools->Log("Everything is fine"); 
	}
	
	std::string SentMessage;
	std::string RecievedMessage;

	while (SentMessage != "end" && RecievedMessage != "end")
	{
		if (AmReceiving)
		{
			if (ServerSide.Receive(RecievedMessage)) 
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

			if (ServerSide.Send(SentMessage))
			{
				Tools->Log("Message sent");
				AmReceiving = true;
			}
			SentMessage.clear();
		}
	}

	ServerSide.CloseSocket();
	ServerSide.ShutDown();
	delete Tools;
	system("Pause");
	return 0;
}