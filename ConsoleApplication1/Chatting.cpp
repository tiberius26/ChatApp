#include "Chatting.h"

void Chatting::ChatLoop(TCPManager& ClientSide)
{
	m_ServerLocal = &ClientSide;
	m_SendingThread = std::thread(&Chatting::Send, this);
	m_ListeningThread = std::thread(&Chatting::Receive, this);
	m_SendingThread.detach();
	m_ListeningThread.join();
}

void Chatting::Receive()
{
	while (m_RecievedMessage != "end")
	{

		if (m_ServerLocal->Receive(m_RecievedMessage))
		{

			if (m_RecievedMessage != "") 
			{
				std::cout << std::endl << "Received: " << m_RecievedMessage << std::endl;
			}
		}
		else { m_Tools->Debug("Can't recieve message", RED); }
	}
}

void Chatting::Send()
{
	while (m_SentMessage != "end")
	{
		std::cout << "Say: ";
		std::getline(std::cin, m_SentMessage);

		if (!m_ServerLocal->Send(m_SentMessage))
		{
			m_Tools->Debug("Can't send message", RED);
		}
		if (m_SentMessage != "end") { m_SentMessage.clear(); }
	}
}

Chatting::Chatting()
{
	m_Tools = new TTools;
	m_ServerLocal = nullptr;
}

void Chatting::CloseChat()
{
	delete m_Tools;
	m_ServerLocal = nullptr;
}