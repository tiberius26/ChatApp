#include <string>
#include <iostream>
#include "TTools.h"
#include "TCPManager.h"
#include "Chatting.h"

//struct to store host adress(ip) and port number
int main(int argc, char* argv[])
{
	TTools* Tools = new TTools;
	Chatting* Chat = new Chatting;
	TCPManager ClientSide;

	Tools->ReadFile("Data/Options.ini");
	std::string IP = Tools->GetIp("Ip");
	//std::string IP = "127.0.0.1";
	ClientSide.Initialize(IP.c_str(), 1234);
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