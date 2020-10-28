#include "TTools.h"

TTools::TTools()
{
	Initialize();
}

void TTools::Debug(std::string Message, ErrorRank Colour)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Colour);

	std::cout << "Error: " << Message << std::endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DEFAULT);
	system("Pause");
}

void TTools::Log(std::string Message)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);

	std::cout << "Log Message: " << Message << std::endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DEFAULT);
	system("Pause");
}

void TTools::Log(std::string Message, int X)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);

	std::cout << "Log Message: " << Message << "\n Value: " << X << std::endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DEFAULT);
	system("Pause");
}

void TTools::Log(std::string Message, int X, int Y)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);

	std::cout << "Log Message: " << Message << "\n Values: " << X << "," << Y << std::endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DEFAULT);
	system("Pause");
}

void TTools::Log(std::string Message, int X, int Y, int Z)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);

	std::cout << "Log Message: " << Message << "\n Values: " << X << "," << Y << "," << Z << std::endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DEFAULT);
	system("Pause");
}

void TTools::Initialize()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DEFAULT);
}

void TTools::LogNoPause(std::string Message)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);

	std::cout << "Log Message: " << Message << std::endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DEFAULT);
}
