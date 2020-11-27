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
	std::string IP = Tools->GetOptions("Ip");
	std::string Port = Tools->GetOptions("Port");
	std::cout << "The connection will be made using the IP:" << IP << std::endl;
	std::cout << "If you want to use another IP, go to Data/Options.ini, then restart the application" << std::endl;
	system("pause");
	//std::string IP = "127.0.0.1";
	ClientSide.Initialize(IP.c_str(), std::stoi(Port));
	ClientSide.OpenSocket();
	system("cls");
	std::cout << "========================================" << std::endl;
	std::cout << "=     BSF Communications department    =" << std::endl;
	std::cout << "========================================" << std::endl;
	std::string Username;
	std::cout << "Please type a username:";
	std::cin >> Username;

	Chat->ChatLoop(ClientSide, Username);

	ClientSide.CloseSocket();
	ClientSide.ShutDown();
	Chat->CloseChat();
	delete Tools;
	delete Chat;
	system("cls");
	std::cout << "The chat has been closed" << std::endl;
	system("Pause");
	return 0;
}