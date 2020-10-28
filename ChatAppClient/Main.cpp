#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_net.h>
#include "TTools.h"

//struct to store host adress(ip) and port number
IPaddress ip; //host and port number essentially

//sockets to transfer data to server
TCPsocket Socket = nullptr;

bool AmListening = true;
bool AmRunning = true;

const int C_PORT = 1234;
const int C_BUFFER = 2000;
int main(int argc, char* argv[])
{
	TTools* Tools = new TTools;

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		Tools->Debug("SDL could not initialize", RED);
		return 0;
	}
	if (SDLNet_Init() == -1)
	{
		Tools->Debug("SDLNet could not initialize", RED);
		return 0;
	}


	if (SDLNet_ResolveHost(&ip, "127.0.0.1", C_PORT) == -1)//the port  //null because we are the server //127.0.0.1 = own machine
	{
		Tools->Debug("Error creating a client", RED);
		return 0;
	}

	Socket = SDLNet_TCP_Open(&ip);//nullptr;

	if (!Socket) 
	{
		Tools->Debug("Error opening socket for connection", RED);
		return 0;
	}

	std::cout << "Connected!" << std::endl;
	system("Pause");
	system("cls");
	std::cout << "========================================" << std::endl;
	std::cout << "=     BSF Communications department    =" << std::endl;
	std::cout << "========================================" << std::endl;
	//Place to store message;
	while (AmRunning)
	{
		if (AmListening) 
		{
			char RevievedMessage[C_BUFFER] = {'\0'};

			if (SDLNet_TCP_Recv(Socket, RevievedMessage, C_BUFFER) <= 0) //is the retun value is < length of message it failled/ there's an error
			{
				Tools->Debug("Error recieveing message", YELLOW);
			}
			else
			{
				std::cout << std::endl << RevievedMessage << std::endl;
				system("Pause");
				AmListening = false;
			}
		}
		else 
		{
			std::cout << "Say:" ;
			std::string Message;
			std::getline(std::cin, Message);
			int MessageLength = Message.length() + 1;
			if (SDLNet_TCP_Send(Socket, Message.c_str(), MessageLength) < MessageLength) //is the retun value is < length of message it failled/ there's an error
			{
				Tools->Debug("Error sending message to server", YELLOW);
			}
			else
			{
				Tools->Log("Message sent");
				Message.clear();
				AmListening = true;
			}
		}
	}

	SDLNet_TCP_Close(Socket);


	//closing
	SDLNet_Quit();
	SDL_Quit();
	delete Tools;

	system("Pause");
	return 0;
}