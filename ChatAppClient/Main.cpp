#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_net.h>
#include "TTools.h"
#include "TCPManager.h"
#include "Chatting.h"

//struct to store host adress(ip) and port number
int main(int argc, char* argv[])
{
	TTools* Tools = new TTools;
	Chatting* Chat = new Chatting;
	TCPManager ClientSide;
	ClientSide.Initialize();
	ClientSide.OpenSocket();
	system("cls");
	std::cout << "========================================" << std::endl;
	std::cout << "=     BSF Communications department    =" << std::endl;
	std::cout << "========================================" << std::endl;

	Chat->ChatLoop(ClientSide);

	ClientSide.CloseSocket();
	ClientSide.ShutDown();
	Chat->CloseChat();
	delete Tools;
	delete Chat;

	system("Pause");
	return 0;
}