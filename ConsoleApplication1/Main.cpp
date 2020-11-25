#include <string>
#include <iostream>
#include "TTools.h"
#include "TCPManager.h"
#include "Chatting.h"
#include <thread>
//Message to be sent to client(s)
std::string message;
int main(int argc, char* argv[])
{
	TTools* Tools = new TTools;
	Chatting* Chat = new Chatting;
	TCPManager* ServerSide = new TCPManager;
	//std::string IP = nullptr;
	ServerSide->Initialize(nullptr, 1234);
	
	std::cout << "========================================" << std::endl;
	std::cout << "=     BSF Communications department    =" << std::endl;
	std::cout << "========================================" << std::endl;

	ServerSide->OpenSocket();
	std::thread ListeningThread(&TCPManager::ListenSocket, ServerSide);
	ListeningThread.detach();
	//ServerSide.ListenSocket();

	std::cout << "Waiting for connection" << std::endl;
	while (ServerSide->GetUserCount() < 1)
	{
		//std::cout << "......" << std::endl;
	}

	system("cls");
	std::cout << "========================================" << std::endl;
	std::cout << "=     BSF Communications department    =" << std::endl;
	std::cout << "========================================" << std::endl;
	//create a friendly message for the client

	message = "Welcome to the chat";

	//we need length of message in order to send data
	int MessageLength = message.length() + 1; //+1 because C adds a null at the end of strings +1 terminates null aka '\0'
	//send message via open sockets which are opened above
	if (ServerSide->Send(message))
	{
		Tools->Log("Everything is fine"); 
	}
	
	Chat->ChatLoop(*ServerSide);


	ServerSide->CloseSocket();
	ServerSide->ShutDown();
	Chat->CloseChat();
	delete Tools;
	delete Chat;
	delete ServerSide;
	system("Pause");
	return 0;
}