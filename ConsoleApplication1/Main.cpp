#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_net.h>

//struct to store host adress(ip) and port number
IPaddress ip; //host and port number essentially

//sockets to listen in on incoming connections
TCPsocket ListenSocket = nullptr;
//sockets to transfer data to client
TCPsocket ClientSocket = nullptr;

//Message to be sent to client(s)
std::string message;

const int PORT = 1234;
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
	std::cout << "========================================" << std::endl;
	std::cout << "=     BSF Communications department    =" << std::endl;
	std::cout << "========================================" << std::endl;

	if (SDLNet_ResolveHost(&ip, nullptr, PORT) == -1)//the port  //null because we are the server
	{
		std::cout << "Error creating a server" << std::endl;
		system("Pause");
		return 0;
	}

	ListenSocket = SDLNet_TCP_Open(&ip);//nullptr;

	if (!ListenSocket) {
		std::cout << "Error opening socket for connection" << std::endl;
		system("Pause");
		return 0;
	}
	std::cout << "Server waiting for connection from client" << std::endl;
	while (!ClientSocket) //waits for client to connect
	{
		ClientSocket = SDLNet_TCP_Accept(ListenSocket);
		std::cout << ".........." << std::endl;
		SDL_Delay(500);
	}

	SDLNet_TCP_Close(ListenSocket); //Keep it open for multiple clients
	std::cout << "Client connected!" << std::endl;
	system("Pause");
	system("cls");
	std::cout << "========================================" << std::endl;
	std::cout << "=     BSF Communications department    =" << std::endl;
	std::cout << "========================================" << std::endl;
	//create a friendly message for the client

	message = "Welcome to the chat";



	//we need length of message in order to send data
	int MessageLength = message.length() + 1; //+1 because C adds a null at the end of strings +1 terminates null aka '\0'
	//send message via open sockets which are opened above
	if (SDLNet_TCP_Send(ClientSocket, message.c_str(), MessageLength) < MessageLength) //is the retun value is < length of message it failled/ there's an error
	{
		std::cout << "Error sending message to client" << std::endl;
		system("Pause");
	}
	else 
	{
		std::cout << "Everything is fine" << std::endl;
		system("Pause");
	}

	SDLNet_TCP_Close(ClientSocket);
	

	//closing
	SDLNet_Quit();
	SDL_Quit();


	/*while (1)
	{
		std::cout << ".........." << std::endl;
		SDL_Delay(500);
	}*/


	system("Pause");
	return 0;
}