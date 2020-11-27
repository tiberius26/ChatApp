#include <string>
#include <iostream>
#include "TTools.h"
#include "TCPManager.h"
#include "Chatting.h"
#include <thread>
//Any warnings left are not caused by this app, SDL

int main(int argc, char* argv[])
{
	//Creating pointers to classes
	TTools* Tools = new TTools;
	Chatting* Chat = new Chatting;
	TCPManager* ServerSide = new TCPManager;

	//Reading options
	Tools->ReadFile("Data/ServerOptions.ini");

	//Initializing server
	ServerSide->Initialize(nullptr, std::stoi(Tools->GetOptions("Port")));
	
	//Siaplay
	std::cout << "========================================" << std::endl;
	std::cout << "=     BSF Communications department    =" << std::endl;
	std::cout << "========================================" << std::endl;

	//Opening sockets
	ServerSide->OpenSocket();

	//Attaching listening to a socker for milti-client
	std::thread ListeningThread(&TCPManager::ListenSocket, ServerSide);
	ListeningThread.detach(); //running it in the background

	std::cout << "Waiting for connection" << std::endl;//message

	while (ServerSide->GetUserCount() < 1) //loop to prevent the app from starting without users
	{
		//std::cout << "......" << std::endl; //uncomment to see working
	}

	//New display
	system("cls");
	std::cout << "========================================" << std::endl;
	std::cout << "=     BSF Communications department    =" << std::endl;
	std::cout << "========================================" << std::endl;

	//Chat loop
	while (!Chat->GetIsChatOver()) 
	{
		Chat->ChatLoop(*ServerSide);
	}

	//Closing everything
	ListeningThread.~thread();
	ServerSide->TurnListeningOff();
	ServerSide->CloseSocket();
	ServerSide->ShutDown();
	Chat->CloseChat();

	//Saving conversation Log
	Chat->SaveLog(std::stoi(Tools->GetOptions("LogCount")));

	//Deleting pointers
	delete Tools;
	delete Chat;
	delete ServerSide;

	//Last display
	system("cls");
	std::cout << "========================================" << std::endl;
	std::cout << "=     BSF Communications department    =" << std::endl;
	std::cout << "========================================" << std::endl;
	std::cout << "The chat has been closed and a copy of the conversation has been made in Data/Logs" << std::endl;
	system("Pause");
	return 0;
}