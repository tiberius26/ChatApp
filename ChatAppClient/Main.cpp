#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_net.h>

//struct to store host adress(ip) and port number
IPaddress ip; //host and port number essentially

//sockets to transfer data to server
TCPsocket Socket = nullptr;

bool AmListening = true;
bool AmRunning = true;

const int PORT = 1234;
const int BUFFER = 2000;
int main(int argc, char* argv[])
{


	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "SDL could not initialize" << std::endl;
		system("Pause");
		return 0;
	}
	if (SDLNet_Init() == -1)
	{
		std::cout << "SDLNet could not initialize" << std::endl;
		system("Pause");
		return 0;
	}


	if (SDLNet_ResolveHost(&ip, "127.0.0.1", PORT) == -1)//the port  //null because we are the server //127.0.0.1 = own machine
	{
		std::cout << "Error creating a client" << std::endl;
		system("Pause");
		return 0;
	}

	Socket = SDLNet_TCP_Open(&ip);//nullptr;

	if (!Socket) {
		std::cout << "Error opening socket for connection" << std::endl;
		system("Pause");
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
			char message[BUFFER];

			if (SDLNet_TCP_Recv(Socket, message, BUFFER) <= 0) //is the retun value is < length of message it failled/ there's an error
			{
				std::cout << "Error recieveing message" << std::endl;
				system("Pause");
			}
			else
			{
				std::cout << std::endl << message << std::endl;
				system("Pause");
				AmListening = false;
			}
		}
		else 
		{
			std::cout << "Say:" ;
			std::string Message;
			std::cin >> Message;
			int MessageLength = Message.length();
			if (SDLNet_TCP_Send(Socket, Message.c_str(), MessageLength) < MessageLength) //is the retun value is < length of message it failled/ there's an error
			{
				std::cout << "Error sending message to server" << std::endl;
				system("Pause");
			}
			else
			{
				std::cout << "Message sent" << std::endl;
				system("Pause");
				AmListening = true;
			}
		}
	}

	SDLNet_TCP_Close(Socket);


	//closing
	SDLNet_Quit();
	SDL_Quit();





	system("Pause");
	return 0;
}