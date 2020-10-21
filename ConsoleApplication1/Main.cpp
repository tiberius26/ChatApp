#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_net.h>

int main(int argc, char* argv[])
{

	std::cout << "========================================" <<std::endl;
	std::cout << "=     BSF Communications department    =" << std::endl;
	std::cout << "========================================" << std::endl;
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

	IPaddress ip; //host and port number essentially

	if (SDLNet_ResolveHost(&ip, "www.youtube.com", 80) == -1)//the port
	{
		std::cout << "Error establishing connection with website: youtube" << std::endl;
		system("Pause");
		return 0;
	}

	TCPsocket socket = SDLNet_TCP_Open(&ip);//nullptr;

	if (!socket) {
		std::cout << "Error opening socket for connection" << std::endl;
		system("Pause");
		return 0;
	}
	else 
	{
		//special request to get HTML code from website
		std::string message = "GET /HTTPS/1.0\r\n\r\n";
		//we need length of message in order to send data
		int MessageLength = message.length() + 1; //+1 because C adds a null at the end of strings +1 terminates null aka '\0'
		//send message via open sockets which are opened above
		if (SDLNet_TCP_Send(socket, message.c_str(), MessageLength) < MessageLength) //is the retun value is < length of message it failled/ there's an error
		{
			std::cout << "Error sending request to website" << std::endl;
			system("Pause");
		}
		else 
		{
			const int BUFFER_SIZE = 2000;
			char response[BUFFER_SIZE];
			if (SDLNet_TCP_Recv(socket, response, BUFFER_SIZE) <= 0) 
			{
				std::cout << "Error recieving message form website" << std::endl;
				system("Pause");
			}
			else 
			{
				std::cout << response<<std::endl;
				std::cout << "No error" << std::endl;
			}
		}

		SDLNet_TCP_Close(socket);
	}

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