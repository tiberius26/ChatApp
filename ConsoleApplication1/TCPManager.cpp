#include "TCPManager.h"

bool TCPManager::Initialize(const char* IP, int port)
{

	m_Tools = new TTools;
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		m_Tools->Debug("SDL could not initialize", RED);
		return false;
	}
	if (SDLNet_Init() == -1)
	{
		m_Tools->Debug("SDLNet could not initialize", RED);
		return false;
	}
	if (SDLNet_ResolveHost(&m_IP, IP, port) == -1)//the port  //null because we are the server
	{
		m_Tools->Debug("Error creating a server", RED);
		return false;
	}
	return true;
}

bool TCPManager::OpenSocket()
{
	m_ListenSocket = SDLNet_TCP_Open(&m_IP);//nullptr;

	if (!m_ListenSocket) {
		m_Tools->Debug("Error opening socket for connection", RED);
		return false;
	}
	return true;
}

void TCPManager::ListenSocket()
{
	std::cout << "Server waiting for connection from clients" << std::endl;
	while (1)
	{
		while (!m_ClientSocket)
		{
			m_UserID = "User" + std::to_string(m_UserCount);
			//sprintf_s(m_UserID, "User%d", m_UserCount);
			m_ClientSocket = SDLNet_TCP_Accept(m_ListenSocket);
			m_ClientList[m_UserID] = m_ClientSocket;
		}
		m_Tools->LogNoPause("Client connected!");
		m_UserCount++;
		m_ClientSocket = nullptr;
	}
	//SDLNet_TCP_Close(m_ListenSocket); //Keep it open for multiple clients
}

bool TCPManager::Send(const std::string& message)
{
	if (m_ClientList.empty())
	{
		return false;
	}
	else 
	{
		for (int i=0; i <m_UserCount; i++ )
		{
			m_SendingLoopID = "User" + std::to_string(i);
			m_MessageLength = message.length() + 1;
			if (SDLNet_TCP_Send(m_ClientList[m_SendingLoopID], message.c_str(), m_MessageLength) < m_MessageLength) //is the retun value is < length of message it failled/ there's an error
			{
				m_Tools->Debug("Error sending message to client", YELLOW);
				return false;
			}
		}
	}
	//return true;
}

bool TCPManager::Receive(std::string& message)
{
	if (m_ClientList.size() == 0)
	{
		return false;
	}
	else
	{
		char RecievedMessage[2000] = { '\0' };
		for (int i = 0; i < m_UserCount; i++)
		{
			m_RecievingLoopID = "User" + std::to_string(i);
			if (SDLNet_TCP_Recv(m_ClientList[m_RecievingLoopID], RecievedMessage, C_BUFFER) <= 0) //is the retun value is < length of message it failled/ there's an error
			{
				m_Tools->Debug("Error recieveing message", YELLOW);
				return false;
			}
			else { message = RecievedMessage;}
		}
		//return true;
	}
	//return false;
}

void TCPManager::CloseSocket()
{
	SDLNet_TCP_Close(m_ClientSocket);
	for (int i = 0; i < m_UserCount; i++)
	{
		m_ClosingSocketID = "User" + std::to_string(i);
		//sprintf_s(m_ClosingSocketID, "User%d", i);
		SDLNet_TCP_Close(m_ClientList[m_ClosingSocketID]);
	}
}

void TCPManager::ShutDown()
{
	SDLNet_Quit();
	SDL_Quit();
	delete m_Tools;
}

TCPManager::TCPManager()
{
	m_MessageLength = 0;
	m_ListenSocket = nullptr;
	m_ClientSocket = nullptr;
	m_Tools = nullptr;
	m_IP = { 0,0 };
	m_UserCount = 0;
}

TCPManager::~TCPManager()
{
}

