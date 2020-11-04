#include "TCPManager.h"

bool TCPManager::Initialize()
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
	if (SDLNet_ResolveHost(&M_IP, "127.0.0.1", C_PORT) == -1)//the port  //null because we are the server
	{
		Tools->Debug("Error creating a client", RED);
		return false;
	}
	return true;
}

bool TCPManager::OpenSocket()
{
	M_Socket = SDLNet_TCP_Open(&M_IP);//nullptr;

	if (!M_Socket) {
		Tools->Debug("Error opening socket for connection", RED);
		return false;
	}
	Tools->Log("Connected!");
	return true;
}

bool TCPManager::Send(const std::string& message)
{
	M_MessageLength = message.length() + 1;
	if (SDLNet_TCP_Send(M_Socket, message.c_str(), M_MessageLength) < M_MessageLength) //is the retun value is < length of message it failled/ there's an error
	{
		Tools->Debug("Error sending message to client", YELLOW);
		return false;
	}
	return true;
}

bool TCPManager::Receive(std::string& message)
{
	char RecievedMessage[2000] = { '\0' };
	if (SDLNet_TCP_Recv(M_Socket, RecievedMessage, C_BUFFER) <= 0) //is the retun value is < length of message it failled/ there's an error
	{
		Tools->Debug("Error recieveing message", YELLOW);
		return false;
	}
	else { message = RecievedMessage; }
	return true;
}

void TCPManager::CloseSocket()
{
	SDLNet_TCP_Close(M_Socket);
}

void TCPManager::ShutDown()
{
	SDLNet_Quit();
	SDL_Quit();
	delete Tools;
}

TCPManager::TCPManager()
{
	M_Socket = nullptr;
	M_MessageLength = 0;
	Tools = nullptr;
	M_IP = {0,0};
}

TCPManager::~TCPManager()
{
}

