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
	}
	if (SDLNet_Init() == -1)
	{
		std::cout << "SDLNet could not initialize" << std::endl;
		
	}

	while (1)
	{
		std::cout << ".........." << std::endl;
		SDL_Delay(500);
	}
	system("Pause");
	return 0;
}