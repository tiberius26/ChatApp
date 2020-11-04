#include "TCPMain.h"
bool TCPMain::Initialize()
{
	Tools = new TTools;
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		Tools->Debug("SDL could not initialize", RED);
		return false;
	}
	if (SDLNet_Init() == -1)
	{
		Tools->Debug("SDLNet could not initialize", RED);
		return false;
	}
	if (SDLNet_ResolveHost(&M_IP, nullptr, C_PORT) == -1)//the port  //null because we are the server
	{
		Tools->Debug("Error creating a server", RED);
		return false;
	}
	return true;
}

bool TCPMain::OpenSocket()
{
	M_ListenSocket = SDLNet_TCP_Open(&M_IP);//nullptr;

	if (!M_ListenSocket) {
		Tools->Debug("Error opening socket for connection", RED);
		return false;
	}
	return true;
}

void TCPMain::ListenSocket()
{
	std::cout << "Server waiting for connection from client" << std::endl;
	while (!M_ClientSocket) //waits for client to connect
	{
		M_ClientSocket = SDLNet_TCP_Accept(M_ListenSocket);
		std::cout << "......" << std::endl;
		SDL_Delay(500);
	}
	SDLNet_TCP_Close(M_ListenSocket); //Keep it open for multiple clients
	Tools->Log("Client connected!");
}

bool TCPMain::Send(const std::string& message)
{
	M_MessageLength = message.length() + 1;
	if (SDLNet_TCP_Send(M_ClientSocket, message.c_str(), M_MessageLength) < M_MessageLength) //is the retun value is < length of message it failled/ there's an error
	{
		Tools->Debug("Error sending message to client", YELLOW);
		return false;
	}
	return true;
}

bool TCPMain::Receive(std::string& message)
{
	char RecievedMessage[2000] = { '\0' };
	if (SDLNet_TCP_Recv(M_ClientSocket, RecievedMessage, C_BUFFER) <= 0) //is the retun value is < length of message it failled/ there's an error
	{
		Tools->Debug("Error recieveing message", YELLOW);
		return false;
	}
	else { message = RecievedMessage; }
	return true;
}

void TCPMain::CloseSocket()
{
	SDLNet_TCP_Close(M_ClientSocket);
}

void TCPMain::ShutDown()
{
	SDLNet_Quit();
	SDL_Quit();
	delete Tools;
}
